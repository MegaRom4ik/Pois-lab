#pragma once
#include "MembershipError.hpp"
#include "Support.hpp"
namespace fitness {
/** A dated club membership with remaining visit credits. */
class Membership {
  public:
    Membership(const std::string &member = "User", int first_day = 0, int last_day = 30, int credits = 10);
    /** Read member. */
    const std::string &member() const { return member_; }
    /** Read first day. */
    const int &first_day() const { return first_day_; }
    /** Read last day. */
    const int &last_day() const { return last_day_; }
    /** Read credits. */
    const int &credits() const { return credits_; }
    /** Check validity dates and remaining visit credits. */
    bool valid_on(int day) const;
    /** Consume one visit credit during the validity period. */
    void consume_visit(int day);

  private:
    std::string member_;
    int first_day_;
    int last_day_;
    int credits_;
};
} // namespace fitness
