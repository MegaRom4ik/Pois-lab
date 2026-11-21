#include "FitnessClub.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw MembershipError(message);
}
} // namespace
FitnessClub::FitnessClub(const std::string &name, const EquipmentInventory &inventory,
                         const std::vector<Membership> &memberships)
    : name_(name), inventory_(inventory), memberships_(memberships) {
    valid(!name_.empty(), "Empty club name");
    auto initial = memberships_;
    memberships_.clear();
    for (const auto &membership : initial)
        enroll(membership);
}
void FitnessClub::enroll(const Membership &membership) {
    for (const auto &stored : memberships_)
        valid(stored.member() != membership.member(), "Duplicate club member");
    memberships_.push_back(membership);
}
void FitnessClub::book(const std::string &member, int day, const std::string &equipment, double load) {
    for (auto &membership : memberships_) {
        if (membership.member() != member) continue;
        Membership next = membership;
        next.consume_visit(day);
        EquipmentInventory reserved = inventory_;
        reserved.reserve(equipment, load);
        inventory_ = reserved;
        membership = next;
        return;
    }
    throw MembershipError("Member not found");
}
} // namespace fitness
