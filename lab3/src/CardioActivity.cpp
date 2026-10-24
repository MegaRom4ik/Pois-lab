#include "CardioActivity.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw WorkoutError(message);
}
} // namespace
CardioActivity::CardioActivity(const std::string &name, const Distance &distance, const Duration &duration)
    : name_(name), distance_(distance), duration_(duration) {
    valid(!name_.empty() && duration_.active() > 0, "Invalid cardio activity");
}
double CardioActivity::speed_kmh() const { return distance_.kilometers() / duration_.active() * 3600.0; }
double CardioActivity::pace_minutes() const {
    valid(distance_.meters() > 0, "Pace needs positive distance");
    return duration_.active_minutes() / distance_.kilometers();
}
} // namespace fitness
