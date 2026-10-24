#include "StepEntry.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
StepEntry::StepEntry(int day, int steps, const Distance &distance)
    : day_(day), steps_(steps), distance_(distance) {
    valid(day_ >= 0 && steps_ >= 0, "Invalid step record");
}
double StepEntry::stride_meters() const {
    valid(steps_ > 0, "No steps for stride estimate");
    return distance_.meters() / steps_;
}
int StepEntry::remaining(int target) const {
    valid(target >= 0, "Negative step target");
    return std::max(0, target - steps_);
}
} // namespace fitness
