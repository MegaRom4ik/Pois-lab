#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid membership data or operations. */
class MembershipError : public FitnessError {
  public:
    explicit MembershipError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
