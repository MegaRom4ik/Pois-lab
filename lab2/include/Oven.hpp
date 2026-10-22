#pragma once
#include "EquipmentError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** An oven with heating, readiness checks, and cooling. */
class Oven {
  public:
    Oven(double temperature = 20, double maximum = 300, bool powered = false);
    double temperature() const { return temperature_; }
    double maximum() const { return maximum_; }
    bool powered() const { return powered_; }
    void preheat(double target);
    bool ready_for(double required) const;
    void cool(double room_temperature);

  private:
    double temperature_;
    double maximum_;
    bool powered_;
};
} // namespace cooking
