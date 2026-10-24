#include "Membership.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw MembershipError(message);
}
} // namespace
Membership::Membership(const std::string &member, int first_day, int last_day, int credits)
    : member_(member), first_day_(first_day), last_day_(last_day), credits_(credits) {
    valid(!member_.empty() && first_day_ >= 0 && last_day_ >= first_day_ && credits_ >= 0,
          "Invalid membership");
}
bool Membership::valid_on(int day) const { return day >= first_day_ && day <= last_day_ && credits_ > 0; }
void Membership::consume_visit(int day) {
    valid(valid_on(day), "No valid visit credit");
    --credits_;
}
} // namespace fitness
