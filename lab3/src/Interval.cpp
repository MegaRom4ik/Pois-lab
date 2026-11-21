#include "Interval.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw PlanError(message);
}
} // namespace
Interval::Interval(const Duration &work, const Duration &recovery, int repetitions)
    : work_(work), recovery_(recovery), repetitions_(repetitions) {
    valid(work_.elapsed() > 0 && repetitions_ > 0, "Invalid interval");
}
double Interval::total_seconds() const { return (work_.elapsed() + recovery_.elapsed()) * repetitions_; }
double Interval::work_seconds() const { return work_.active() * repetitions_; }
} // namespace fitness
