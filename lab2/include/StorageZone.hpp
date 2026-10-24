#pragma once
#include "StorageError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A storage area with a temperature range. */
class StorageZone {
  public:
    StorageZone(std::string name = "Холодильник", double minimum = 0, double maximum = 5, double temperature = 4);
    const std::string &name() const { return name_; }
    double minimum() const { return minimum_; }
    double maximum() const { return maximum_; }
    double temperature() const { return temperature_; }
    bool suitable() const;
    void adjust(double delta);

  private:
    std::string name_;
    double minimum_;
    double maximum_;
    double temperature_;
};
} // namespace cooking
