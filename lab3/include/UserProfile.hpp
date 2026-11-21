#pragma once
#include "ProfileError.hpp"
#include "Support.hpp"
namespace fitness {
/** Identity and basic user settings. */
class UserProfile {
  public:
    UserProfile(const std::string &name = "User", int age = 20, double height_cm = 170);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read age. */
    const int &age() const { return age_; }
    /** Read height cm. */
    const double &height_cm() const { return height_cm_; }
    /** Find a user by part of their name. */
    bool matches(const std::string &query) const;
    /** Convert the recorded height to metres. */
    double height_meters() const;

  private:
    std::string name_;
    int age_;
    double height_cm_;
};
} // namespace fitness
