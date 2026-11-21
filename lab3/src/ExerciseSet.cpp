#include "ExerciseSet.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ExerciseError(message);
}
} // namespace
ExerciseSet::ExerciseSet(int repetitions, double load_kg, int rest_seconds)
    : repetitions_(repetitions), load_kg_(load_kg), rest_seconds_(rest_seconds) {
    valid(repetitions_ > 0 && load_kg_ >= 0 && std::isfinite(load_kg_) && rest_seconds_ >= 0, "Invalid set");
}
double ExerciseSet::volume() const { return repetitions_ * load_kg_; }
ExerciseSet ExerciseSet::deloaded(double fraction) const {
    valid(std::isfinite(fraction) && fraction > 0 && fraction <= 1, "Invalid deload fraction");
    return ExerciseSet(repetitions_, load_kg_ * fraction, rest_seconds_);
}
} // namespace fitness
