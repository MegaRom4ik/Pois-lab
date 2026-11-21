#pragma once
#include "FitnessError.hpp"
namespace fitness {
/** Reports invalid nutrition data or operations. */
class NutritionError : public FitnessError {
  public:
    explicit NutritionError(const std::string &message) : FitnessError(message) {}
};
} // namespace fitness
