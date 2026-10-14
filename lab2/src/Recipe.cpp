#include "Recipe.hpp"
namespace cooking {
Recipe::Recipe(std::string name, int servings, std::vector<IngredientAmount> ingredients, std::vector<RecipeStep> steps)
    : name_(std::move(name)), servings_(std::move(servings)), ingredients_(std::move(ingredients)),
      steps_(std::move(steps)) {
    text(name_);
    if (servings_ <= 0)
        throw RecipeError("Неверное число порций");
}
void Recipe::add_ingredient(const IngredientAmount &item) {
    for (const auto &existing : ingredients_)
        if (existing.ingredient().name() == item.ingredient().name())
            throw RecipeError("Продукт уже есть");
    ingredients_.push_back(item);
}
void Recipe::add_step(const RecipeStep &step) {
    if (!step.ready(static_cast<int>(steps_.size())))
        throw RecipeError("Зависимость шага ещё не определена");
    steps_.push_back(step);
}
Recipe Recipe::scaled_to(int portions) const {
    if (portions <= 0)
        throw RecipeError("Порции должны быть положительными");
    Recipe result(name_, portions, {}, steps_);
    for (const auto &item : ingredients_)
        result.add_ingredient(item.scaled(static_cast<double>(portions) / servings_));
    return result;
}
double Recipe::calories_per_serving() const {
    double total = 0;
    for (const auto &item : ingredients_)
        total += item.calories();
    return total / servings_;
}
int Recipe::duration() const {
    int total = 0;
    for (const auto &step : steps_)
        total += step.minutes();
    return total;
}
} // namespace cooking
