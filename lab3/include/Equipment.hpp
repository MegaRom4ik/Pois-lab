#pragma once
#include "EquipmentError.hpp"
#include "Support.hpp"
namespace fitness {
/** A reservable piece of exercise equipment. */
class Equipment {
  public:
    Equipment(const std::string &name = "Barbell", double capacity_kg = 200, bool available = true);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read capacity kg. */
    const double &capacity_kg() const { return capacity_kg_; }
    /** Read available. */
    const bool &available() const { return available_; }
    /** Reserve available equipment within its load capacity. */
    void reserve(double load);
    /** Release a currently reserved item. */
    void release();

  private:
    std::string name_;
    double capacity_kg_;
    bool available_;
};
} // namespace fitness
