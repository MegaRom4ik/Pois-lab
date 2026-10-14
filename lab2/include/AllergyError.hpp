#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: AllergyError. */
class AllergyError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
