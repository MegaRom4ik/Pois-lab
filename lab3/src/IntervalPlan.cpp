#include "IntervalPlan.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw PlanError(message);
}
} // namespace
IntervalPlan::IntervalPlan(const std::string &name, const Duration &warmup,
                           const std::vector<Interval> &blocks)
    : name_(name), warmup_(warmup), blocks_(blocks) {
    valid(!name_.empty(), "Empty interval plan name");
}
void IntervalPlan::append(const Interval &block) { blocks_.push_back(block); }
double IntervalPlan::elapsed_minutes() const {
    double seconds = warmup_.elapsed();
    for (const auto &block : blocks_)
        seconds += block.total_seconds();
    return seconds / 60.0;
}
double IntervalPlan::work_fraction() const {
    double seconds = warmup_.active();
    for (const auto &block : blocks_)
        seconds += block.work_seconds();
    const double total = elapsed_minutes() * 60;
    return total == 0 ? 0 : seconds / total;
}
} // namespace fitness
