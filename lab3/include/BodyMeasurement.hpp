#pragma once
#include "MeasurementError.hpp"
#include "Support.hpp"
namespace fitness {
/** Body dimensions recorded on a day. */
class BodyMeasurement {
  public:
    BodyMeasurement(int day = 0, double waist_cm = 80, double chest_cm = 100);
    /** Read day. */
    const int &day() const { return day_; }
    /** Read waist cm. */
    const double &waist_cm() const { return waist_cm_; }
    /** Read chest cm. */
    const double &chest_cm() const { return chest_cm_; }
    /** Compare waist measurements chronologically. */
    double waist_change(const BodyMeasurement &previous) const;
    /** Calculate the difference between two dimensions. */
    double chest_waist_difference() const;

  private:
    int day_;
    double waist_cm_;
    double chest_cm_;
};
} // namespace fitness
