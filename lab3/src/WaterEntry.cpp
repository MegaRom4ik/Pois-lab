#include "WaterEntry.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
WaterEntry::WaterEntry(int day, double milliliters, const std::string &label)
    : day_(day), milliliters_(milliliters), label_(label) {
    valid(day_ >= 0 && milliliters_ > 0 && std::isfinite(milliliters_) && !label_.empty(),
          "Invalid water entry");
}
double WaterEntry::liters() const { return milliliters_ / 1000.0; }
double WaterEntry::cups(double cup_ml) const {
    valid(cup_ml > 0 && std::isfinite(cup_ml), "Invalid cup size");
    return std::floor(milliliters_ / cup_ml);
}
} // namespace fitness
