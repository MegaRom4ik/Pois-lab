#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid distance data or operations. */
class DistanceError : public FitnessError {
  public:
    explicit DistanceError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
