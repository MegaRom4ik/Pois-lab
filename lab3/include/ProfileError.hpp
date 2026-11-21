#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid profile data or operations. */
class ProfileError : public FitnessError {
  public:
    explicit ProfileError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
