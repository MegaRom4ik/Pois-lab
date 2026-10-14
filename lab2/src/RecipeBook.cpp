#include "RecipeBook.hpp"
namespace cooking {
RecipeBook::RecipeBook(std::string title, std::vector<Recipe> recipes, int revision)
    : title_(std::move(title)), recipes_(std::move(recipes)), revision_(std::move(revision)) {
    text(title_);
}
void RecipeBook::add(const Recipe &recipe) {
    for (const auto &item : recipes_)
        if (item.name() == recipe.name())
            throw RecipeError("Рецепт уже существует");
    recipes_.push_back(recipe);
    ++revision_;
}
Recipe RecipeBook::find(const std::string &name) const {
    for (const auto &recipe : recipes_)
        if (recipe.name() == name)
            return recipe;
    throw RecipeError("Рецепт не найден");
}
void RecipeBook::remove(const std::string &name) {
    const auto found =
        std::find_if(recipes_.begin(), recipes_.end(), [&](const auto &recipe) { return recipe.name() == name; });
    if (found == recipes_.end())
        throw RecipeError("Рецепт не найден");
    recipes_.erase(found);
    ++revision_;
}
} // namespace cooking
