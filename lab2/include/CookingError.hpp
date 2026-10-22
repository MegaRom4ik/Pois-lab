#pragma once
#include <stdexcept>
namespace cooking {
/** Exception raised by the cooking model: CookingError. */
class CookingError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};
} // namespace cooking
