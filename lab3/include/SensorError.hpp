#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid sensor data or operations. */
class SensorError : public FitnessError {
  public:
    explicit SensorError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
