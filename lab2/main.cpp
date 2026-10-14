#include "../lab1/cli/Input.hpp"
#include "CostEstimate.hpp"
#include "KitchenArchive.hpp"
#include "PurchaseOrder.hpp"
#include <fstream>
#include <optional>
using namespace cooking;
namespace {
constexpr int max_input_entries = 100;
enum class Action {
    exit,
    recipes,
    add_recipe,
    preview,
    stock,
    inventory,
    purchase,
    begin,
    advance,
    next_day,
    diet,
    serve,
    cost,
    save,
    load
};
int read_count(const std::string &prompt) {
    const int result = cli::read<int>(prompt);
    if (result < 1 || result > max_input_entries) throw RecipeError("Количество должно быть 1..100");
    return result;
}
Recipe sample_recipe() {
    Recipe recipe("Каша", 2);
    recipe.add_ingredient(IngredientAmount(Ingredient("Овёс", Nutrition(340, 12, 5, 60), {"глютен"}), Quantity(100)));
    recipe.add_ingredient(IngredientAmount(Ingredient("Молоко", Nutrition(60, 3, 3, 5), {"молоко"}), Quantity(200)));
    recipe.add_step(RecipeStep("Смешать овёс с молоком", 2));
    recipe.add_step(RecipeStep("Варить, помешивая", 10, 0));
    return recipe;
}
Kitchen sample_kitchen() {
    Kitchen kitchen;
    kitchen.register_recipe(sample_recipe());
    kitchen.stock(InventoryBatch(Ingredient("Овёс"), 1000, 30, "Овёс-1"));
    kitchen.stock(InventoryBatch(Ingredient("Молоко"), 1000, 3, "Молоко-1"));
    return kitchen;
}
void list_recipes(const Kitchen &kitchen) {
    for (const auto &recipe : kitchen.book().recipes())
        std::cout << recipe.name() << ": " << recipe.servings() << " порц., " << recipe.duration() << " мин., "
                  << recipe.calories_per_serving() << " ккал/порц.\n";
}
IngredientAmount read_ingredient() {
    const auto name = cli::read_line("Продукт: ");
    const double grams = cli::read<double>("Граммы на рецепт: ");
    const double calories = cli::read<double>("Ккал на 100 г: ");
    const double protein = cli::read<double>("Белки на 100 г: ");
    const double fat = cli::read<double>("Жиры на 100 г: ");
    const double carbs = cli::read<double>("Углеводы на 100 г: ");
    const auto allergen = cli::read_line("Аллерген (пусто, если нет): ");
    std::vector<std::string> allergens;
    if (!allergen.empty()) allergens.push_back(allergen);
    const int vegetarian = cli::read<int>("Вегетарианский продукт? 1/0: ");
    if (vegetarian != 0 && vegetarian != 1) throw IngredientError("Введите 0 или 1");
    return IngredientAmount(Ingredient(name, Nutrition(calories, protein, fat, carbs), allergens, vegetarian == 1),
                            Quantity(grams));
}
void add_recipe(Kitchen &kitchen) {
    const auto name = cli::read_line("Название рецепта: ");
    Recipe recipe(name, read_count("Число порций: "));
    const int products = read_count("Число продуктов: ");
    for (int index = 0; index < products; ++index)
        recipe.add_ingredient(read_ingredient());
    const int steps = read_count("Число шагов: ");
    for (int index = 0; index < steps; ++index) {
        const auto instruction = cli::read_line("Описание шага: ");
        const int minutes = read_count("Длительность в минутах: ");
        recipe.add_step(RecipeStep(instruction, minutes, index - 1));
    }
    kitchen.register_recipe(recipe);
    std::cout << "Рецепт добавлен\n";
}
Recipe choose_recipe(const Kitchen &kitchen, const DietProfile &profile) {
    const auto name = cli::read_line("Название рецепта: ");
    const int portions = read_count("Порций: ");
    return kitchen.plan(name, portions, profile);
}
void preview(const Recipe &recipe) {
    for (const auto &item : recipe.ingredients())
        std::cout << item.ingredient().name() << ": " << item.amount().grams() << " г\n";
    for (const auto &step : recipe.steps())
        std::cout << step.instruction() << " — " << step.minutes() << " мин.\n";
    std::cout << "На порцию: " << recipe.calories_per_serving() << " ккал\n";
}
void stock(Kitchen &kitchen) {
    const auto name = cli::read_line("Название продукта (как в рецепте): ");
    const double grams = cli::read<double>("Масса, г: ");
    const int expires = cli::read<int>("Годен до дня включительно: ");
    const auto lot = cli::read_line("Уникальный номер партии: ");
    kitchen.stock(InventoryBatch(Ingredient(name), grams, expires, lot));
    std::cout << "Партия принята\n";
}
void show_stock(const Kitchen &kitchen) {
    for (const auto &batch : kitchen.pantry().batches())
        std::cout << batch.lot() << ": " << batch.ingredient().name() << ", " << batch.grams() << " г, годен до "
                  << batch.expires_day() << (batch.usable(kitchen.day()) ? " — доступен\n" : " — недоступен\n");
}
ShoppingList shopping_for(const Recipe &recipe, const Kitchen &kitchen, bool missing_only) {
    ShoppingList result;
    for (const auto &item : recipe.ingredients()) {
        double grams = item.amount().grams();
        if (missing_only) grams -= kitchen.pantry().available(item.ingredient().name(), kitchen.day());
        if (grams <= 0 || item.optional()) continue;
        std::cout << item.ingredient().name() << ": нужно " << grams << " г\n";
        const double price = cli::read<double>("Цена за кг: ");
        result.add(ShoppingItem(IngredientAmount(item.ingredient(), Quantity(grams)),
                                PriceQuote(item.ingredient().name(), price, kitchen.day()), kitchen.day()));
    }
    return result;
}
void accept_purchase(Kitchen &kitchen, Budget &budget, const ShoppingList &list, int expires) {
    std::vector<PriceQuote> offers;
    for (const auto &item : list.items())
        offers.push_back(item.quote());
    Budget next_budget = budget;
    PurchaseOrder order(Supplier("Магазин", offers, 0), list);
    order.submit(next_budget);
    Kitchen next = kitchen;
    for (const auto &item : list.items()) {
        const auto lot = "Закупка-" + std::to_string(next.pantry().batches().size());
        next.stock(InventoryBatch(item.item().ingredient(), item.item().amount().grams(), expires, lot));
    }
    kitchen = next;
    budget = next_budget;
    std::cout << "Закупка принята\n";
}
void purchase(Kitchen &kitchen, Budget &budget, const DietProfile &profile) {
    const auto list = shopping_for(choose_recipe(kitchen, profile), kitchen, true);
    if (list.items().empty()) {
        std::cout << "Продуктов достаточно\n";
        return;
    }
    std::cout << "Стоимость недостающего: " << list.total() << ", бюджет: " << budget.limit() - budget.spent() << '\n';
    if (cli::read<int>("Оплатить и принять? 1 — да: ") != 1) return;
    const int expires = cli::read<int>("Годен до дня: ");
    accept_purchase(kitchen, budget, list, expires);
}

void begin(Kitchen &kitchen, std::optional<CookingSession> &session, const DietProfile &profile) {
    if (session) throw WorkflowError("Сначала закончите текущую сессию");
    CookingSession next(choose_recipe(kitchen, profile), 0, false, kitchen.day());
    Pantry stock = kitchen.pantry();
    next.begin(stock);
    kitchen = Kitchen(kitchen.book(), stock, kitchen.dishes(), kitchen.day());
    session = next;
    std::cout << "Продукты списаны. Текущий шаг: " << session->recipe().steps()[0].instruction() << '\n';
}
void advance(Kitchen &kitchen, std::optional<CookingSession> &session) {
    if (!session) throw WorkflowError("Сначала начните приготовление");
    session->complete_step();
    if (session->next_step() < static_cast<int>(session->recipe().steps().size())) {
        std::cout << "Следующий шаг: " << session->recipe().steps()[session->next_step()].instruction() << '\n';
        return;
    }
    auto dishes = kitchen.dishes();
    dishes.push_back(session->finish());
    kitchen = Kitchen(kitchen.book(), kitchen.pantry(), dishes, kitchen.day());
    session.reset();
    std::cout << "Блюдо приготовлено\n";
}
DietProfile read_profile() {
    const auto person = cli::read_line("Имя: ");
    const auto allergen = cli::read_line("Запрещённый аллерген (пусто, если нет): ");
    std::vector<Allergen> allergens;
    if (!allergen.empty()) allergens.emplace_back(allergen);
    const double calories = cli::read<double>("Предел ккал одной порции: ");
    const int vegetarian = cli::read<int>("Только вегетарианское? 1/0: ");
    if (vegetarian != 0 && vegetarian != 1) throw IngredientError("Введите 0 или 1");
    return DietProfile(person, allergens, calories, vegetarian == 1);
}
void serve(Kitchen &kitchen) {
    auto dishes = kitchen.dishes();
    for (std::size_t index = 0; index < dishes.size(); ++index)
        std::cout << index + 1 << ": " << dishes[index].recipe().name() << ", осталось " << dishes[index].remaining()
                  << '\n';
    const int choice = read_count("Номер блюда: ");
    if (static_cast<std::size_t>(choice) > dishes.size()) throw OrderError("Блюдо не найдено");
    const int portions = read_count("Выдать порций: ");
    dishes[choice - 1].serve(portions);
    kitchen = Kitchen(kitchen.book(), kitchen.pantry(), dishes, kitchen.day());
    std::cout << "Порции выданы\n";
}
void archive(Kitchen &kitchen, bool save, const std::optional<CookingSession> &session) {
    if (session) throw WorkflowError("Архив доступен после завершения приготовления");
    const auto path = cli::read_line("Путь к файлу: ");
    KitchenArchive codec;
    if (save) {
        std::ofstream output(path);
        codec.save(kitchen, output);
    } else {
        std::ifstream input(path);
        kitchen = codec.load(input);
    }
    std::cout << "Рецепты и склад " << (save ? "сохранены" : "загружены") << "; готовые блюда в архив не входят\n";
}
void menu() {
    std::cout << "\n1 — рецепты, 2 — добавить рецепт, 3 — рассчитать порции, 4 — принять продукты,\n"
              << "5 — склад, 6 — купить недостающее, 7 — начать приготовление, 8 — завершить шаг,\n"
              << "9 — следующий день, 10 — ограничения питания, 11 — выдать блюдо,\n"
              << "12 — себестоимость, 13 — сохранить рецепты и склад, 14 — загрузить, 0 — выход\n";
}
void estimate(const Kitchen &kitchen, const DietProfile &profile) {
    const auto recipe = choose_recipe(kitchen, profile);
    const auto list = shopping_for(recipe, kitchen, false);
    std::cout << "Себестоимость порции с трудом и накладными: " << CostEstimate(list).per_serving(recipe) << '\n';
}
void next_day(Kitchen &kitchen, const std::optional<CookingSession> &session) {
    if (session) throw WorkflowError("Закончите приготовление");
    kitchen.next_day();
}
void operation(Action action, Kitchen &kitchen, Budget &budget, DietProfile &profile,
               std::optional<CookingSession> &session) {
    if (action == Action::recipes) return list_recipes(kitchen);
    if (action == Action::add_recipe) return add_recipe(kitchen);
    if (action == Action::preview) return preview(choose_recipe(kitchen, profile));
    if (action == Action::stock) return stock(kitchen);
    if (action == Action::inventory) return show_stock(kitchen);
    if (action == Action::purchase) return purchase(kitchen, budget, profile);
    if (action == Action::begin) return begin(kitchen, session, profile);
    if (action == Action::advance) return advance(kitchen, session);
    if (action == Action::next_day) return next_day(kitchen, session);
    if (action == Action::diet) {
        profile = read_profile();
        return;
    }
    if (action == Action::serve) return serve(kitchen);
    if (action == Action::cost) return estimate(kitchen, profile);
    if (action == Action::save || action == Action::load) return archive(kitchen, action == Action::save, session);
    throw WorkflowError("Нет такого пункта");
}
} // namespace
int main() {
    Kitchen kitchen = sample_kitchen();
    Budget budget;
    DietProfile profile;
    std::optional<CookingSession> session;
    while (std::cin) {
        std::cout << "\nКулинарная мастерская. День " << kitchen.day() << '\n';
        menu();
        try {
            const auto action = static_cast<Action>(cli::read<int>("> "));
            if (action == Action::exit) break;
            operation(action, kitchen, budget, profile, session);
        } catch (const std::exception &error) {
            std::cerr << "Ошибка: " << error.what() << '\n';
        }
    }
}
