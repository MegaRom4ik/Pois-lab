#include "CookingSession.hpp"
namespace cooking {
CookingSession::CookingSession(Recipe recipe, int next_step, bool started, int day)
    : recipe_(std::move(recipe)), next_step_(std::move(next_step)), started_(std::move(started)), day_(std::move(day)) {
    if (next_step_ < 0 || next_step_ > static_cast<int>(recipe_.steps().size()) || day_ < 0)
        throw WorkflowError("Неверная сессия");
}
void CookingSession::begin(Pantry &pantry) {
    if (started_ || recipe_.steps().empty() || recipe_.ingredients().empty())
        throw WorkflowError("Сессия не готова");
    pantry.consume_recipe(recipe_, day_);
    started_ = true;
}
void CookingSession::complete_step() {
    if (!started_ || next_step_ >= static_cast<int>(recipe_.steps().size()))
        throw WorkflowError("Нет текущего шага");
    ++next_step_;
}
Dish CookingSession::finish() const {
    if (!started_ || next_step_ != static_cast<int>(recipe_.steps().size()))
        throw WorkflowError("Не все шаги завершены");
    return Dish(recipe_, recipe_.servings(), day_);
}
} // namespace cooking
