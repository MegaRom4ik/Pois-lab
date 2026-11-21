#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid workout data or operations. */
class WorkoutError : public FitnessError {
  public:
    explicit WorkoutError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
