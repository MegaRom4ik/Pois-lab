#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid plan data or operations. */
class PlanError : public FitnessError {
  public:
    explicit PlanError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
