#pragma once
#include "DistanceError.hpp"
#include "Support.hpp"
namespace fitness {
/** A route segment measured in metres. */
class Distance {
  public:
    Distance(double meters = 1000, double ascent = 0, const std::string &surface = "road");
    /** Read meters. */
    const double &meters() const { return meters_; }
    /** Read ascent. */
    const double &ascent() const { return ascent_; }
    /** Read surface. */
    const std::string &surface() const { return surface_; }
    /** Convert metres to kilometres. */
    double kilometers() const;
    /** Calculate the ascent to distance ratio. */
    double grade() const;
    /** Join two route segments. */
    Distance joined(const Distance &other) const;

  private:
    double meters_;
    double ascent_;
    std::string surface_;
};
} // namespace fitness
