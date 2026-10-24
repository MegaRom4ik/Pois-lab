#include "Duration.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw DurationError(message);
}
} // namespace
Duration::Duration(double active, double rest, double paused)
    : active_(active), rest_(rest), paused_(paused) {
    valid(std::isfinite(active_) && std::isfinite(rest_) && std::isfinite(paused_) && active_ >= 0 &&
              rest_ >= 0 && paused_ >= 0,
          "Invalid duration");
}
double Duration::elapsed() const { return active_ + rest_ + paused_; }
double Duration::active_minutes() const { return active_ / 60.0; }
double Duration::active_share() const { return elapsed() == 0 ? 0 : active_ / elapsed(); }
} // namespace fitness
