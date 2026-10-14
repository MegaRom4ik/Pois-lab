#pragma once
#include "EquipmentError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Журнал замеров температуры оборудования. */
class TemperatureLog {
  public:
    TemperatureLog(std::string equipment = "Духовка", std::vector<double> readings = {}, double maximum = 300);
    const std::string &equipment() const { return equipment_; }
    const std::vector<double> &readings() const { return readings_; }
    double maximum() const { return maximum_; }
    void record(double value);
    double average() const;

  private:
    std::string equipment_;
    std::vector<double> readings_;
    double maximum_;
};
} // namespace cooking
