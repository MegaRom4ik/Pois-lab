#include "ProgressReport.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
ProgressReport::ProgressReport(const WorkoutLog &workouts, const StepHistory &steps,
                               const WeightHistory &weights)
    : workouts_(workouts), steps_(steps), weights_(weights) {}
std::string ProgressReport::render(int first, int last) const {
    std::ostringstream out;
    out << "Sessions: " << workouts_.count_between(first, last)
        << "\nSteps: " << steps_.total_steps(first, last)
        << "\nVolume: " << workouts_.volume_between(first, last) << "\n";
    if (!weights_.entries().empty())
        out << "Weight change (all records): " << weights_.total_change() << "\n";
    return out.str();
}
double ProgressReport::sessions_per_week(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid report period");
    return workouts_.count_between(first, last) * static_cast<double>(days_per_week) /
           (static_cast<double>(last) - first + 1);
}
} // namespace fitness
