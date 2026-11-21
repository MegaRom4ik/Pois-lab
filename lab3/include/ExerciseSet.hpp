#pragma once
#include "ExerciseError.hpp"
#include "Support.hpp"
namespace fitness {
/** One strength set with repetitions, load and rest. */
class ExerciseSet {
  public:
    ExerciseSet(int repetitions = 10, double load_kg = 20, int rest_seconds = 60);
    /** Read repetitions. */
    const int &repetitions() const { return repetitions_; }
    /** Read load kg. */
    const double &load_kg() const { return load_kg_; }
    /** Read rest seconds. */
    const int &rest_seconds() const { return rest_seconds_; }
    /** Calculate lifted kilogram repetitions. */
    double volume() const;
    /** Create a lighter set while retaining repetitions and rest. */
    ExerciseSet deloaded(double fraction) const;

  private:
    int repetitions_;
    double load_kg_;
    int rest_seconds_;
};
} // namespace fitness
