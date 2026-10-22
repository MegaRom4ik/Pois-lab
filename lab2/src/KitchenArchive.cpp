#include "KitchenArchive.hpp"
#include <iomanip>
#include <istream>
#include <limits>
#include <ostream>
namespace cooking {
namespace {
template <typename Value> Value read(std::istream &input) {
    Value value{};
    if (!(input >> value))
        throw SerializationError("Неполный архив");
    return value;
}
std::string read_text(std::istream &input) {
    std::string value;
    if (!(input >> std::quoted(value)))
        throw SerializationError("Неверный текст архива");
    return value;
}
int count(std::istream &input, int maximum) {
    const int value = read<int>(input);
    if (value < 0 || value > maximum)
        throw SerializationError("Недопустимый размер архива");
    return value;
}
void save_ingredient(const Ingredient &product, std::ostream &output) {
    const auto &nutrients = product.nutrition();
    output << std::quoted(product.name()) << ' ' << nutrients.calories() << ' ' << nutrients.protein() << ' '
           << nutrients.fat() << ' ' << nutrients.carbs() << ' ' << product.vegetarian() << ' '
           << product.allergens().size() << ' ';
    for (const auto &allergen : product.allergens())
        output << std::quoted(allergen) << ' ';
}
Ingredient load_ingredient(std::istream &input, int maximum) {
    const auto name = read_text(input);
    const double calories = read<double>(input), protein = read<double>(input);
    const double fat = read<double>(input), carbs = read<double>(input);
    const bool vegetarian = read<bool>(input);
    const int size = count(input, maximum);
    std::vector<std::string> allergens;
    for (int index = 0; index < size; ++index)
        allergens.push_back(read_text(input));
    return Ingredient(name, Nutrition(calories, protein, fat, carbs), allergens, vegetarian);
}
void save_recipe(const Recipe &recipe, std::ostream &output) {
    output << std::quoted(recipe.name()) << ' ' << recipe.servings() << ' ' << recipe.ingredients().size() << ' ';
    for (const auto &item : recipe.ingredients()) {
        save_ingredient(item.ingredient(), output);
        output << item.amount().grams() << ' ' << item.amount().yield() << ' ' << std::quoted(item.amount().label())
               << ' ' << item.optional() << ' ';
    }
    output << recipe.steps().size() << ' ';
    for (const auto &step : recipe.steps())
        output << std::quoted(step.instruction()) << ' ' << step.minutes() << ' ' << step.prerequisite() << ' ';
    output << '\n';
}
Recipe load_recipe(std::istream &input, int maximum) {
    const auto name = read_text(input);
    Recipe recipe(name, read<int>(input));
    const int ingredients = count(input, maximum);
    for (int index = 0; index < ingredients; ++index) {
        const auto product = load_ingredient(input, maximum);
        const double grams = read<double>(input), yield = read<double>(input);
        const auto unit = read_text(input);
        recipe.add_ingredient(IngredientAmount(product, Quantity(grams, yield, unit), read<bool>(input)));
    }
    const int steps = count(input, maximum);
    for (int index = 0; index < steps; ++index) {
        const auto instruction = read_text(input);
        const int minutes = read<int>(input), prerequisite = read<int>(input);
        recipe.add_step(RecipeStep(instruction, minutes, prerequisite));
    }
    return recipe;
}
Pantry load_pantry(std::istream &input, int maximum) {
    const auto name = read_text(input);
    Pantry pantry(name, {}, read<double>(input));
    const int batches = count(input, maximum);
    for (int index = 0; index < batches; ++index) {
        const auto product = load_ingredient(input, maximum);
        const double grams = read<double>(input);
        const int expires = read<int>(input);
        pantry.receive(InventoryBatch(product, grams, expires, read_text(input)));
    }
    return pantry;
}
} // namespace
KitchenArchive::KitchenArchive(int version, int max_recipes, int max_entries)
    : version_(version), max_recipes_(max_recipes), max_entries_(max_entries) {
    if (version_ != 1 || max_recipes_ <= 0 || max_entries_ <= 0)
        throw SerializationError("Неверные настройки архива");
}
void KitchenArchive::save(const Kitchen &kitchen, std::ostream &output) const {
    output << std::setprecision(std::numeric_limits<double>::max_digits10);
    output << "COOKING " << version_ << ' ' << kitchen.day() << ' ' << std::quoted(kitchen.book().title()) << ' '
           << kitchen.book().recipes().size() << '\n';
    for (const auto &recipe : kitchen.book().recipes())
        save_recipe(recipe, output);
    const auto &pantry = kitchen.pantry();
    output << std::quoted(pantry.name()) << ' ' << pantry.capacity() << ' ' << pantry.batches().size() << '\n';
    for (const auto &batch : pantry.batches()) {
        save_ingredient(batch.ingredient(), output);
        output << batch.grams() << ' ' << batch.expires_day() << ' ' << std::quoted(batch.lot()) << '\n';
    }
    if (!output)
        throw SerializationError("Запись не удалась");
}
Kitchen KitchenArchive::load(std::istream &input) const {
    try {
        if (read<std::string>(input) != "COOKING" || read<int>(input) != version_)
            throw SerializationError("Неизвестный формат");
        const int day = read<int>(input);
        RecipeBook book(read_text(input));
        const int recipes = count(input, max_recipes_);
        for (int index = 0; index < recipes; ++index)
            book.add(load_recipe(input, max_entries_));
        const auto pantry = load_pantry(input, max_entries_);
        input >> std::ws;
        if (!input.eof())
            throw SerializationError("Лишние данные архива");
        return Kitchen(book, pantry, {}, day);
    } catch (const CookingError &error) {
        throw SerializationError(error.what());
    }
}
} // namespace cooking
