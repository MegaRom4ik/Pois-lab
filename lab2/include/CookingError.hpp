#pragma once
#include <stdexcept>
namespace cooking {
/** Ошибка кулинарной модели: CookingError. */
class CookingError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};
} // namespace cooking
