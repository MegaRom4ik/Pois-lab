#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid goal data or operations. */
class GoalError : public FitnessError {
  public:
    explicit GoalError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
