#include "EnergyBalance.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
EnergyBalance::EnergyBalance(double intake, double activity, double baseline)
    : intake_(intake), activity_(activity), baseline_(baseline) {
    valid(intake_ >= 0 && activity_ >= 0 && baseline_ >= 0 && std::isfinite(intake_) &&
              std::isfinite(activity_) && std::isfinite(baseline_),
          "Invalid energy estimate");
}
double EnergyBalance::net() const { return intake_ - activity_ - baseline_; }
double EnergyBalance::activity_share() const {
    const double total = activity_ + baseline_;
    return total == 0 ? 0 : activity_ / total;
}
} // namespace fitness
