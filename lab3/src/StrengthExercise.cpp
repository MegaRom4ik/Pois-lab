#include "StrengthExercise.hpp"
namespace fitness {
namespace {}
StrengthExercise::StrengthExercise(const Exercise &exercise, const std::vector<ExerciseSet> &sets,
                                   bool unilateral)
    : exercise_(exercise), sets_(sets), unilateral_(unilateral) {}
void StrengthExercise::add_set(const ExerciseSet &set) { sets_.push_back(set); }
double StrengthExercise::volume() const {
    double total = 0;
    for (const auto &set : sets_)
        total += set.volume();
    return total * (unilateral_ ? 2 : 1);
}
long long StrengthExercise::total_repetitions() const {
    long long total = 0;
    for (const auto &set : sets_)
        total += set.repetitions();
    return total * (unilateral_ ? 2 : 1);
}
} // namespace fitness
