#include "WeightEntry.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw MeasurementError(message);
}
} // namespace
WeightEntry::WeightEntry(int day, double kilograms, const std::string &note)
    : day_(day), kilograms_(kilograms), note_(note) {
    valid(day_ >= 0 && kilograms_ > 0 && std::isfinite(kilograms_), "Invalid weight");
}
double WeightEntry::change_from(const WeightEntry &previous) const {
    valid(day_ >= previous.day_, "Weight predates previous");
    return kilograms_ - previous.kilograms_;
}
bool WeightEntry::within(double target, double tolerance) const {
    valid(target > 0 && tolerance >= 0 && std::isfinite(target) && std::isfinite(tolerance),
          "Invalid target");
    return std::abs(kilograms_ - target) <= tolerance;
}
} // namespace fitness
