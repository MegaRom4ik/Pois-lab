#include "Dish.hpp"
namespace cooking {
Dish::Dish(Recipe recipe, int remaining, int cooked_day)
    : recipe_(std::move(recipe)), remaining_(std::move(remaining)), cooked_day_(std::move(cooked_day)) {
    if (remaining_ < 0 || remaining_ > recipe_.servings() || cooked_day_ < 0)
        throw WorkflowError("Неверное блюдо");
}
void Dish::serve(int portions) {
    if (portions <= 0 || portions > remaining_)
        throw WorkflowError("Недостаточно порций");
    remaining_ -= portions;
}
double Dish::calories_for(int portions) const {
    if (portions <= 0 || portions > remaining_)
        throw WorkflowError("Неверная порция");
    return recipe_.calories_per_serving() * portions;
}
} // namespace cooking
