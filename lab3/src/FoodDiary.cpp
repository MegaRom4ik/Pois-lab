#include "FoodDiary.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
FoodDiary::FoodDiary(const std::vector<Meal> &meals, double target_kcal, const std::string &owner)
    : meals_(meals), target_kcal_(target_kcal), owner_(owner) {
    valid(target_kcal_ > 0 && std::isfinite(target_kcal_) && !owner_.empty(), "Invalid food diary");
}
void FoodDiary::record(const Meal &meal) { meals_.push_back(meal); }
double FoodDiary::calories_on(int day) const {
    valid(day >= 0, "Invalid day");
    double total = 0;
    for (const auto &meal : meals_)
        if (meal.day() == day) total += meal.total_nutrients().calories();
    return total;
}
double FoodDiary::budget_balance(int day) const { return target_kcal_ - calories_on(day); }
} // namespace fitness
