#pragma once
#include "Exercise.hpp"
#include "ExerciseError.hpp"
#include "ExerciseSet.hpp"
#include "Support.hpp"
namespace fitness {
/** An exercise with an ordered list of sets. */
class StrengthExercise {
  public:
    StrengthExercise(const Exercise &exercise = {}, const std::vector<ExerciseSet> &sets = {},
                     bool unilateral = false);
    /** Read exercise. */
    const Exercise &exercise() const { return exercise_; }
    /** Read sets. */
    const std::vector<ExerciseSet> &sets() const { return sets_; }
    /** Read unilateral. */
    const bool &unilateral() const { return unilateral_; }
    /** Append a completed or planned set. */
    void add_set(const ExerciseSet &set);
    /** Sum lifted volume, including both sides for unilateral work. */
    double volume() const;
    /** Sum repetitions across sets and sides. */
    long long total_repetitions() const;

  private:
    Exercise exercise_;
    std::vector<ExerciseSet> sets_;
    bool unilateral_;
};
} // namespace fitness
