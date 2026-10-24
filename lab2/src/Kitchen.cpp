#include "Kitchen.hpp"
namespace cooking {
Kitchen::Kitchen(RecipeBook book, Pantry pantry, std::vector<Dish> dishes, int day)
    : book_(std::move(book)), pantry_(std::move(pantry)), dishes_(std::move(dishes)), day_(std::move(day)) {
    if (day_ < 0)
        throw WorkflowError("Неверный день");
}
void Kitchen::register_recipe(const Recipe &recipe) { book_.add(recipe); }
void Kitchen::stock(const InventoryBatch &batch) {
    if (!batch.usable(day_))
        throw ExpiredFoodError("Нельзя принять просроченное");
    pantry_.receive(batch);
}
Recipe Kitchen::plan(const std::string &name, int portions, const DietProfile &profile) const {
    Recipe result = book_.find(name).scaled_to(portions);
    if (!profile.accepts(result))
        throw AllergyError("Рецепт не подходит");
    return result;
}
void Kitchen::cook(const std::string &name, int portions, const DietProfile &profile) {
    const auto recipe = plan(name, portions, profile);
    Pantry next = pantry_;
    CookingSession session(recipe, 0, false, day_);
    session.begin(next);
    for (std::size_t index = 0; index < recipe.steps().size(); ++index)
        session.complete_step();
    Dish dish = session.finish();
    dishes_.push_back(dish);
    pantry_ = std::move(next);
}
void Kitchen::next_day() { ++day_; }
} // namespace cooking
