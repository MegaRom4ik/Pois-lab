#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid measurement data or operations. */
class MeasurementError : public FitnessError {
  public:
    explicit MeasurementError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
