#pragma once
#include "ExpiredFoodError.hpp"
#include "InventoryBatch.hpp"
#include "StorageError.hpp"
#include "StorageZone.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Учебное правило проверки продукта, не медицинская рекомендация. */
class FoodSafetyRule {
  public:
    FoodSafetyRule(double min_temperature = 0, double max_temperature = 5, int max_open_days = 2);
    double min_temperature() const { return min_temperature_; }
    double max_temperature() const { return max_temperature_; }
    int max_open_days() const { return max_open_days_; }
    bool permits(const StorageZone &zone, int open_days) const;
    void check(const InventoryBatch &batch, int day) const;

  private:
    double min_temperature_;
    double max_temperature_;
    int max_open_days_;
};
} // namespace cooking
