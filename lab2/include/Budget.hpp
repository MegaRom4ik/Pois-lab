#pragma once
#include "BudgetError.hpp"
#include "ShoppingList.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Бюджет закупок и учёт возвратов. */
class Budget {
  public:
    Budget(double limit = 1000, double spent = 0, std::string currency = "BYN");
    double limit() const { return limit_; }
    double spent() const { return spent_; }
    const std::string &currency() const { return currency_; }
    void pay(double amount);
    void refund(double amount);
    bool covers(const ShoppingList &list) const;

  private:
    double limit_;
    double spent_;
    std::string currency_;
};
} // namespace cooking
