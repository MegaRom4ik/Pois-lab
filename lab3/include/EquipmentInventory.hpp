#pragma once
#include "Equipment.hpp"
#include "EquipmentError.hpp"
#include "Support.hpp"
namespace fitness {
/** An inventory of uniquely named equipment. */
class EquipmentInventory {
  public:
    EquipmentInventory(const std::string &name = "Gym", const std::vector<Equipment> &items = {},
                       int capacity = 100);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read items. */
    const std::vector<Equipment> &items() const { return items_; }
    /** Read capacity. */
    const int &capacity() const { return capacity_; }
    /** Add equipment after capacity and identity checks. */
    void add(const Equipment &item);
    /** Find and reserve equipment by its name. */
    void reserve(const std::string &name, double load);
    /** Find and release equipment by its name. */
    void release(const std::string &name);

  private:
    std::string name_;
    std::vector<Equipment> items_;
    int capacity_;
};
} // namespace fitness
