#include "WorkoutSession.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw WorkoutError(message);
}
} // namespace
WorkoutSession::WorkoutSession(int id, const Workout &workout, int day, bool completed)
    : id_(id), workout_(workout), day_(day), completed_(completed) {
    valid(id_ > 0 && day_ >= 0, "Invalid session identity");
    valid(!completed_ || !workout_.strength().empty() || !workout_.cardio().empty(),
          "Empty completed session");
}
void WorkoutSession::finish() {
    valid(!completed_, "Session already finished");
    valid(!workout_.strength().empty() || !workout_.cardio().empty(), "Empty session");
    completed_ = true;
}
bool WorkoutSession::in_period(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid period");
    return completed_ && day_ >= first && day_ <= last;
}
} // namespace fitness
