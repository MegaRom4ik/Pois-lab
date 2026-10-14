#pragma once
#include "EquipmentError.hpp"
#include "KitchenTool.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Рабочее место и занятость. */
class Workstation {
  public:
    Workstation(std::string name = "Стол", KitchenTool tool = KitchenTool{}, bool occupied = false);
    const std::string &name() const { return name_; }
    const KitchenTool &tool() const { return tool_; }
    bool occupied() const { return occupied_; }
    void reserve(const Quantity &quantity);
    void release();

  private:
    std::string name_;
    KitchenTool tool_;
    bool occupied_;
};
} // namespace cooking
