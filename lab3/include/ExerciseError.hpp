#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid exercise data or operations. */
class ExerciseError : public FitnessError {
  public:
    explicit ExerciseError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
