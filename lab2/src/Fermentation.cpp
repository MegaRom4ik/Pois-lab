#include "Fermentation.hpp"
namespace cooking {
Fermentation::Fermentation(Dough dough, int required_minutes, int elapsed_minutes)
    : dough_(std::move(dough)), required_minutes_(std::move(required_minutes)),
      elapsed_minutes_(std::move(elapsed_minutes)) {
    if (required_minutes_ <= 0 || elapsed_minutes_ < 0)
        throw RecipeError("Неверное брожение");
}
void Fermentation::advance(int minutes) {
    if (minutes <= 0)
        throw WorkflowError("Неверное время брожения");
    elapsed_minutes_ += minutes;
}
bool Fermentation::ready() const { return elapsed_minutes_ >= required_minutes_; }
double Fermentation::progress() const {
    return std::min(1.0, static_cast<double>(elapsed_minutes_) / required_minutes_);
}
} // namespace cooking
