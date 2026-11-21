#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid equipment data or operations. */
class EquipmentError : public FitnessError {
  public:
    explicit EquipmentError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
