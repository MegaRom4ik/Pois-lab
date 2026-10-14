#include "MealPlan.hpp"
namespace cooking {
MealPlan::MealPlan(DietProfile profile, std::vector<Recipe> meals, double daily_limit)
    : profile_(std::move(profile)), meals_(std::move(meals)), daily_limit_(std::move(daily_limit)) {
    positive(daily_limit_);
}
double MealPlan::calories() const {
    double total = 0;
    for (const auto &recipe : meals_)
        total += recipe.calories_per_serving();
    return total;
}
void MealPlan::add(const Recipe &recipe) {
    if (!profile_.accepts(recipe))
        throw AllergyError("Рецепт не подходит рациону");
    if (calories() + recipe.calories_per_serving() > daily_limit_)
        throw RecipeError("Превышение калорий");
    meals_.push_back(recipe);
}
} // namespace cooking
