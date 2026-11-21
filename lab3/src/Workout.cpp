#include "Workout.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw WorkoutError(message);
}
} // namespace
Workout::Workout(const std::string &name, const std::vector<StrengthExercise> &strength,
                 const std::vector<CardioActivity> &cardio)
    : name_(name), strength_(strength), cardio_(cardio) {
    valid(!name_.empty(), "Empty workout name");
}
void Workout::add_strength(const StrengthExercise &exercise) { strength_.push_back(exercise); }
void Workout::add_cardio(const CardioActivity &activity) { cardio_.push_back(activity); }
double Workout::lifted_volume() const {
    double total = 0;
    for (const auto &exercise : strength_)
        total += exercise.volume();
    return total;
}
double Workout::cardio_minutes() const {
    double total = 0;
    for (const auto &activity : cardio_)
        total += activity.duration().active_minutes();
    return total;
}
} // namespace fitness
