#pragma once
#include "InventoryBatch.hpp"
#include "Recipe.hpp"
#include "StockError.hpp"
#include "StorageError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Ingredient storage that consumes usable batches by earliest expiry. */
class Pantry {
  public:
    Pantry(std::string name = "Склад", const std::vector<InventoryBatch> &batches = {},
           double capacity = 100000);
    const std::string &name() const { return name_; }
    const std::vector<InventoryBatch> &batches() const { return batches_; }
    double capacity() const { return capacity_; }
    double stored() const;
    void receive(const InventoryBatch &batch);
    double available(const std::string &product, int day) const;
    void consume(const std::string &product, double grams, int day);
    void consume_recipe(const Recipe &recipe, int day);

  private:
    std::string name_;
    std::vector<InventoryBatch> batches_;
    double capacity_;
};
} // namespace cooking
