#pragma once
#include "Recipe.hpp"
#include "SkillProfile.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A chef with skills and available working time. */
class Chef {
  public:
    Chef(std::string name = "Повар", SkillProfile skills = SkillProfile{}, int available_minutes = 480);
    const std::string &name() const { return name_; }
    const SkillProfile &skills() const { return skills_; }
    int available_minutes() const { return available_minutes_; }
    void assign(const Recipe &recipe);
    bool can_cook(const std::string &technique, int level) const;

  private:
    std::string name_;
    SkillProfile skills_;
    int available_minutes_;
};
} // namespace cooking
