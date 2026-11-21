#include "Meal.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
Meal::Meal(const std::string &name, int day, const std::vector<Food> &foods)
    : name_(name), day_(day), foods_(foods) {
    valid(!name_.empty() && day_ >= 0, "Invalid meal");
}
void Meal::add(const Food &food) { foods_.push_back(food); }
Nutrients Meal::total_nutrients() const {
    Nutrients total;
    for (const auto &food : foods_)
        total = total.combined(food.portion_nutrients());
    return total;
}
double Meal::total_grams() const {
    double total = 0;
    for (const auto &food : foods_)
        total += food.grams();
    return total;
}
} // namespace fitness
