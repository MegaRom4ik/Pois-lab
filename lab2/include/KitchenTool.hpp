#pragma once
#include "EquipmentError.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A kitchen tool with a capacity limit and cleaning requirements. */
class KitchenTool {
  public:
    KitchenTool(std::string name = "Миска", double capacity = 2000, bool clean = true);
    const std::string &name() const { return name_; }
    double capacity() const { return capacity_; }
    bool clean() const { return clean_; }
    void use(const Quantity &amount);
    void wash();

  private:
    std::string name_;
    double capacity_;
    bool clean_;
};
} // namespace cooking
