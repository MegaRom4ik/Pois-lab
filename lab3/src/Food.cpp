#include "Food.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
Food::Food(const std::string &name, const Nutrients &per_100g, double grams)
    : name_(name), per_100g_(per_100g), grams_(grams) {
    valid(!name_.empty() && grams_ > 0 && std::isfinite(grams_), "Invalid food portion");
}
Nutrients Food::portion_nutrients() const { return per_100g_.scaled(grams_ / reference_grams); }
Food Food::resized(double grams) const { return Food(name_, per_100g_, grams); }
} // namespace fitness
