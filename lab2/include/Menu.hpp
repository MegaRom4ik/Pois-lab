#pragma once
#include "DietProfile.hpp"
#include "MenuItem.hpp"
#include "OrderError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Меню с подбором по рациону. */
class Menu {
  public:
    Menu(std::string title = "Обед", std::vector<MenuItem> items = {}, int max_items = 20);
    const std::string &title() const { return title_; }
    const std::vector<MenuItem> &items() const { return items_; }
    int max_items() const { return max_items_; }
    void add(const MenuItem &item);
    std::vector<MenuItem> select(const DietProfile &profile) const;

  private:
    std::string title_;
    std::vector<MenuItem> items_;
    int max_items_;
};
} // namespace cooking
