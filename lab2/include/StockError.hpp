#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: StockError. */
class StockError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
