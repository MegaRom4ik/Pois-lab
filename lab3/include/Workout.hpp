#pragma once
#include "CardioActivity.hpp"
#include "StrengthExercise.hpp"
#include "Support.hpp"
#include "WorkoutError.hpp"
namespace fitness {
/** A collection of strength and cardio exercises. */
class Workout {
  public:
    Workout(const std::string &name = "Workout", const std::vector<StrengthExercise> &strength = {},
            const std::vector<CardioActivity> &cardio = {});
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read strength. */
    const std::vector<StrengthExercise> &strength() const { return strength_; }
    /** Read cardio. */
    const std::vector<CardioActivity> &cardio() const { return cardio_; }
    /** Include a strength exercise in the workout. */
    void add_strength(const StrengthExercise &exercise);
    /** Include a cardio activity in the workout. */
    void add_cardio(const CardioActivity &activity);
    /** Sum strength volume across exercises. */
    double lifted_volume() const;
    /** Sum active cardio minutes. */
    double cardio_minutes() const;

  private:
    std::string name_;
    std::vector<StrengthExercise> strength_;
    std::vector<CardioActivity> cardio_;
};
} // namespace fitness
