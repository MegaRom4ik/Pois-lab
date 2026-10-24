#pragma once
#include "ExerciseError.hpp"
#include "Support.hpp"
namespace fitness {
/** A named exercise and its required equipment. */
class Exercise {
  public:
    Exercise(const std::string &name = "Squat", const std::string &muscle = "legs",
             const std::string &equipment = "bodyweight");
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read muscle. */
    const std::string &muscle() const { return muscle_; }
    /** Read equipment. */
    const std::string &equipment() const { return equipment_; }
    /** Match the primary muscle group. */
    bool trains(const std::string &group) const;
    /** Check equipment availability for an exercise. */
    bool possible_with(const std::vector<std::string> &available) const;

  private:
    std::string name_;
    std::string muscle_;
    std::string equipment_;
};
} // namespace fitness
