#include "WorkoutSession.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw WorkoutError(message);
}
bool has_work(const Workout &workout) {
    if (!workout.cardio().empty()) return true;
    return std::any_of(workout.strength().begin(), workout.strength().end(),
                       [](const StrengthExercise &exercise) { return !exercise.sets().empty(); });
}
} // namespace
WorkoutSession::WorkoutSession(int id, const Workout &workout, int day, bool completed)
    : id_(id), workout_(workout), day_(day), completed_(completed) {
    valid(id_ > 0 && day_ >= 0, "Invalid session identity");
    valid(!completed_ || has_work(workout), "Empty completed session");
}
void WorkoutSession::finish() {
    valid(!completed_, "Session already finished");
    valid(has_work(workout_), "Empty session");
    completed_ = true;
}
bool WorkoutSession::in_period(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid period");
    return completed_ && day_ >= first && day_ <= last;
}
} // namespace fitness
