#pragma once
#include <stdexcept>
#include <string>
namespace fitness {
/** Base exception for fitness application errors. */
class FitnessError : public std::runtime_error {
  public:
    explicit FitnessError(const std::string &message) : std::runtime_error(message) {}
};
} // namespace fitness
