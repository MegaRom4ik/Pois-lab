#pragma once
#include "Distance.hpp"
#include "Duration.hpp"
#include "Support.hpp"
#include "WorkoutError.hpp"
namespace fitness {
/** An activity with distance and timing. */
class CardioActivity {
  public:
    CardioActivity(const std::string &name = "Run", const Distance &distance = {},
                   const Duration &duration = Duration(300));
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read distance. */
    const Distance &distance() const { return distance_; }
    /** Read duration. */
    const Duration &duration() const { return duration_; }
    /** Calculate moving speed in kilometres per hour. */
    double speed_kmh() const;
    /** Calculate minutes per kilometre. */
    double pace_minutes() const;

  private:
    std::string name_;
    Distance distance_;
    Duration duration_;
};
} // namespace fitness
