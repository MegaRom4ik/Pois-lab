#pragma once
#include "Ingredient.hpp"
#include "OrderError.hpp"
#include "PriceQuote.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Учёт списания продукта и стоимости потерь. */
class WasteRecord {
  public:
    WasteRecord(Ingredient ingredient = Ingredient{}, Quantity amount = Quantity{}, std::string reason = "Порча");
    const Ingredient &ingredient() const { return ingredient_; }
    const Quantity &amount() const { return amount_; }
    const std::string &reason() const { return reason_; }
    double loss(const PriceQuote &quote, int day) const;
    double fraction_of(const Quantity &purchased) const;

  private:
    Ingredient ingredient_;
    Quantity amount_;
    std::string reason_;
};
} // namespace cooking
