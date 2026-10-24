#include "FoodSafetyRule.hpp"
namespace cooking {
FoodSafetyRule::FoodSafetyRule(double min_temperature, double max_temperature, int max_open_days)
    : min_temperature_(std::move(min_temperature)), max_temperature_(std::move(max_temperature)),
      max_open_days_(std::move(max_open_days)) {
    finite_number(min_temperature_);
    finite_number(max_temperature_);
    if (min_temperature_ > max_temperature_ || max_open_days_ < 0)
        throw StorageError("Неверное правило");
}
bool FoodSafetyRule::permits(const StorageZone &zone, int open_days) const {
    return open_days >= 0 && open_days <= max_open_days_ && zone.temperature() >= min_temperature_ &&
           zone.temperature() <= max_temperature_;
}
void FoodSafetyRule::check(const InventoryBatch &batch, int day) const {
    if (!batch.usable(day))
        throw ExpiredFoodError("Продукт не пригоден");
}
} // namespace cooking
