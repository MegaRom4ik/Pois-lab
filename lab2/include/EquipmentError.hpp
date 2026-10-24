#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: EquipmentError. */
class EquipmentError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
