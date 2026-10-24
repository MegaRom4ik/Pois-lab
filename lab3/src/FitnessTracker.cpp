#include "FitnessTracker.hpp"
namespace fitness {
namespace {}
FitnessTracker::FitnessTracker(const UserProfile &profile, const WorkoutLog &workouts,
                               const StepHistory &steps, const WeightHistory &weights,
                               const HydrationLog &water, const FoodDiary &food, const SleepDiary &sleep,
                               const TrainingCalendar &calendar)
    : profile_(profile), workouts_(workouts), steps_(steps), weights_(weights), water_(water), food_(food),
      sleep_(sleep), calendar_(calendar) {}
void FitnessTracker::record_workout(const WorkoutSession &session) { workouts_.append(session); }
void FitnessTracker::record_steps(const StepEntry &entry) { steps_.record(entry); }
void FitnessTracker::record_weight(const WeightEntry &entry) { weights_.add(entry); }
void FitnessTracker::record_water(const WaterEntry &entry) { water_.drink(entry); }
void FitnessTracker::record_meal(const Meal &meal) { food_.record(meal); }
void FitnessTracker::record_sleep(const SleepEntry &entry) { sleep_.record(entry); }
void FitnessTracker::schedule(const ScheduleSlot &slot) { calendar_.book(slot); }
std::string FitnessTracker::report(int first, int last) const {
    return ProgressReport(workouts_, steps_, weights_).render(first, last);
}
} // namespace fitness
