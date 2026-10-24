#pragma once
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A chef's proficiency in cooking techniques. */
class SkillProfile {
  public:
    SkillProfile(std::string speciality = "выпечка", int level = 1, int practice_hours = 0);
    const std::string &speciality() const { return speciality_; }
    int level() const { return level_; }
    int practice_hours() const { return practice_hours_; }
    void practice(int hours);
    bool qualifies(const std::string &technique, int required_level) const;

  private:
    std::string speciality_;
    int level_;
    int practice_hours_;
};
} // namespace cooking
