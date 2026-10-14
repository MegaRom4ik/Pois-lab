#pragma once
#include "Kitchen.hpp"
#include "SerializationError.hpp"
#include <iosfwd>
namespace cooking {
/** Текстовый архив рецептов и склада; готовые блюда и незавершённые сессии не сохраняются. */
class KitchenArchive {
  public:
    KitchenArchive(int version = 1, int max_recipes = 1000, int max_entries = 10000);
    void save(const Kitchen &kitchen, std::ostream &output) const;
    Kitchen load(std::istream &input) const;

  private:
    int version_;
    int max_recipes_;
    int max_entries_;
};
} // namespace cooking
