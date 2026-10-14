#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: EquipmentError. */
class EquipmentError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
