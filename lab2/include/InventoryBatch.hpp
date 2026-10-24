#pragma once
#include "ExpiredFoodError.hpp"
#include "Ingredient.hpp"
#include "StockError.hpp"
#include "StorageError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** An ingredient batch with an expiry date. */
class InventoryBatch {
  public:
    InventoryBatch(Ingredient ingredient = Ingredient{}, double grams = 1000, int expires_day = 30,
                   std::string lot = "A1");
    const Ingredient &ingredient() const { return ingredient_; }
    double grams() const { return grams_; }
    int expires_day() const { return expires_day_; }
    const std::string &lot() const { return lot_; }
    bool usable(int day) const;
    void consume(double grams, int day);

  private:
    Ingredient ingredient_;
    double grams_;
    int expires_day_;
    std::string lot_;
};
} // namespace cooking
