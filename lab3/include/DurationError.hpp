#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid duration data or operations. */
class DurationError : public FitnessError {
  public:
    explicit DurationError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
