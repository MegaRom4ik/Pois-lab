#pragma once
#include "OrderError.hpp"
#include "PurchaseOrder.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Приёмка поставки по дате и температуре. */
class Delivery {
  public:
    Delivery(PurchaseOrder order = PurchaseOrder{}, int arrival_day = 2, double temperature = 4, bool accepted = false);
    const PurchaseOrder &order() const { return order_; }
    int arrival_day() const { return arrival_day_; }
    double temperature() const { return temperature_; }
    bool accepted() const { return accepted_; }
    bool on_time(int promised_day) const;
    void accept(double maximum_temperature);

  private:
    PurchaseOrder order_;
    int arrival_day_;
    double temperature_;
    bool accepted_;
};
} // namespace cooking
