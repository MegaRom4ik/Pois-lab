#include "MenuItem.hpp"
namespace cooking {
MenuItem::MenuItem(Recipe recipe, double price, bool enabled)
    : recipe_(std::move(recipe)), price_(std::move(price)), enabled_(std::move(enabled)) {
    positive(price_);
}
double MenuItem::charge(int portions) const {
    if (!enabled_ || portions <= 0)
        throw OrderError("Блюдо недоступно");
    return portions * price_;
}
bool MenuItem::suitable(const DietProfile &profile) const { return enabled_ && profile.accepts(recipe_); }
} // namespace cooking
