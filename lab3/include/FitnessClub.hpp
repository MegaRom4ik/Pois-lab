#pragma once
#include "EquipmentInventory.hpp"
#include "Membership.hpp"
#include "MembershipError.hpp"
#include "Support.hpp"
namespace fitness {
/** Membership and equipment booking coordinated atomically. */
class FitnessClub {
  public:
    FitnessClub(const std::string &name = "Club", const EquipmentInventory &inventory = {},
                const std::vector<Membership> &memberships = {});
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read inventory. */
    const EquipmentInventory &inventory() const { return inventory_; }
    /** Read memberships. */
    const std::vector<Membership> &memberships() const { return memberships_; }
    /** Register a unique membership. */
    void enroll(const Membership &membership);
    /** Reserve equipment and spend a visit credit only if both operations succeed. */
    void book(const std::string &member, int day, const std::string &equipment, double load);

  private:
    std::string name_;
    EquipmentInventory inventory_;
    std::vector<Membership> memberships_;
};
} // namespace fitness
