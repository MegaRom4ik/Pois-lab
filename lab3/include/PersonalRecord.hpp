#pragma once
#include "Exercise.hpp"
#include "GoalError.hpp"
#include "Support.hpp"
namespace fitness {
/** Best recorded load for a given exercise and repetition count. */
class PersonalRecord {
  public:
    PersonalRecord(const Exercise &exercise = {}, double load_kg = 20, int repetitions = 10, int day = 0);
    /** Read exercise. */
    const Exercise &exercise() const { return exercise_; }
    /** Read load kg. */
    const double &load_kg() const { return load_kg_; }
    /** Read repetitions. */
    const int &repetitions() const { return repetitions_; }
    /** Read day. */
    const int &day() const { return day_; }
    /** Compare loads for the same exercise and repetition count. */
    bool beats(const PersonalRecord &previous) const;
    /** Calculate load improvement for comparable records. */
    double improvement(const PersonalRecord &previous) const;

  private:
    Exercise exercise_;
    double load_kg_;
    int repetitions_;
    int day_;
};
} // namespace fitness
