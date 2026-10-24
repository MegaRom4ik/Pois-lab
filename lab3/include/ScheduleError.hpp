#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid schedule data or operations. */
class ScheduleError : public FitnessError {
  public:
    explicit ScheduleError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
