#pragma once
#include "Distance.hpp"
#include "DistanceError.hpp"
#include "Support.hpp"
namespace fitness {
/** A named route assembled from distance segments. */
class WalkingRoute {
  public:
    WalkingRoute(const std::string &name = "Route", const std::vector<Distance> &segments = {},
                 bool loop = false);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read segments. */
    const std::vector<Distance> &segments() const { return segments_; }
    /** Read loop. */
    const bool &loop() const { return loop_; }
    /** Append a route segment. */
    void extend(const Distance &segment);
    /** Sum distance and ascent over the route. */
    Distance total_distance() const;
    /** Calculate the distance needed to return to the starting point. */
    double round_trip_meters() const;

  private:
    std::string name_;
    std::vector<Distance> segments_;
    bool loop_;
};
} // namespace fitness
