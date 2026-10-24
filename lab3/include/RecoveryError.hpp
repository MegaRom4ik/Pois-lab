#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid recovery data or operations. */
class RecoveryError : public FitnessError {
  public:
    explicit RecoveryError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
