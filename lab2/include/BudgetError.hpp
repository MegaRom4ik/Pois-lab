#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: BudgetError. */
class BudgetError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
