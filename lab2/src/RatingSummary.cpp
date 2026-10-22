#include "RatingSummary.hpp"
namespace cooking {
RatingSummary::RatingSummary(Recipe recipe, std::vector<Feedback> feedback, int minimum_reviews)
    : recipe_(std::move(recipe)), feedback_(std::move(feedback)), minimum_reviews_(std::move(minimum_reviews)) {
    if (minimum_reviews_ <= 0)
        throw RecipeError("Неверный порог отзывов");
}
void RatingSummary::add(const Feedback &item) {
    if (!item.refers_to(recipe_))
        throw RecipeError("Отзыв о другом блюде");
    feedback_.push_back(item);
}
double RatingSummary::average() const {
    if (static_cast<int>(feedback_.size()) < minimum_reviews_)
        throw RecipeError("Недостаточно отзывов");
    int total = 0;
    for (const auto &item : feedback_)
        total += item.score();
    return static_cast<double>(total) / feedback_.size();
}
} // namespace cooking
