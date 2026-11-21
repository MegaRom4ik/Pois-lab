#pragma once
#include "FoodDiary.hpp"
#include "GoalError.hpp"
#include "HydrationLog.hpp"
#include "Meal.hpp"
#include "ProgressReport.hpp"
#include "ScheduleSlot.hpp"
#include "SleepDiary.hpp"
#include "SleepEntry.hpp"
#include "StepEntry.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
#include "TrainingCalendar.hpp"
#include "UserProfile.hpp"
#include "WaterEntry.hpp"
#include "WeightEntry.hpp"
#include "WeightHistory.hpp"
#include "WorkoutLog.hpp"
#include "WorkoutSession.hpp"
namespace fitness {
/** Application state coordinating activity and daily records. */
class FitnessTracker {
  public:
    FitnessTracker(const UserProfile &profile = {}, const WorkoutLog &workouts = {},
                   const StepHistory &steps = {}, const WeightHistory &weights = {},
                   const HydrationLog &water = {}, const FoodDiary &food = {}, const SleepDiary &sleep = {},
                   const TrainingCalendar &calendar = {});
    /** Read profile. */
    const UserProfile &profile() const { return profile_; }
    /** Read workouts. */
    const WorkoutLog &workouts() const { return workouts_; }
    /** Read steps. */
    const StepHistory &steps() const { return steps_; }
    /** Read weights. */
    const WeightHistory &weights() const { return weights_; }
    /** Read water. */
    const HydrationLog &water() const { return water_; }
    /** Read food. */
    const FoodDiary &food() const { return food_; }
    /** Read sleep. */
    const SleepDiary &sleep() const { return sleep_; }
    /** Read calendar. */
    const TrainingCalendar &calendar() const { return calendar_; }
    /** Store a finished workout in the application log. */
    void record_workout(const WorkoutSession &session);
    /** Store a new daily step total. */
    void record_steps(const StepEntry &entry);
    /** Store a chronological weight measurement. */
    void record_weight(const WeightEntry &entry);
    /** Record water consumption. */
    void record_water(const WaterEntry &entry);
    /** Record a consumed meal. */
    void record_meal(const Meal &meal);
    /** Store one sleep interval. */
    void record_sleep(const SleepEntry &entry);
    /** Book a planned workout. */
    void schedule(const ScheduleSlot &slot);
    /** Build a progress report from the current application state. */
    std::string report(int first, int last) const;

  private:
    UserProfile profile_;
    WorkoutLog workouts_;
    StepHistory steps_;
    WeightHistory weights_;
    HydrationLog water_;
    FoodDiary food_;
    SleepDiary sleep_;
    TrainingCalendar calendar_;
};
} // namespace fitness
