#include "Feedback.hpp"
namespace cooking {
Feedback::Feedback(std::string dish, int score, std::string comment)
    : dish_(std::move(dish)), score_(std::move(score)), comment_(std::move(comment)) {
    text(dish_);
    text(comment_);
    if (score_ < 1 || score_ > 5)
        throw RecipeError("Оценка 1..5");
}
bool Feedback::needs_attention() const { return score_ <= 2; }
bool Feedback::refers_to(const Recipe &recipe) const { return dish_ == recipe.name(); }
} // namespace cooking
