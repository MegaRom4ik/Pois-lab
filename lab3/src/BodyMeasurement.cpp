#include "BodyMeasurement.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw MeasurementError(message);
}
} // namespace
BodyMeasurement::BodyMeasurement(int day, double waist_cm, double chest_cm)
    : day_(day), waist_cm_(waist_cm), chest_cm_(chest_cm) {
    valid(day_ >= 0 && waist_cm_ > 0 && chest_cm_ > 0 && std::isfinite(waist_cm_) && std::isfinite(chest_cm_),
          "Invalid measurement");
}
double BodyMeasurement::waist_change(const BodyMeasurement &previous) const {
    valid(day_ >= previous.day_, "Measurement predates previous");
    return waist_cm_ - previous.waist_cm_;
}
double BodyMeasurement::chest_waist_difference() const { return chest_cm_ - waist_cm_; }
} // namespace fitness
