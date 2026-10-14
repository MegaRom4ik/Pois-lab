#include "RecipeStep.hpp"
namespace cooking {
RecipeStep::RecipeStep(std::string instruction, int minutes, int prerequisite)
    : instruction_(std::move(instruction)), minutes_(std::move(minutes)), prerequisite_(std::move(prerequisite)) {
    if (minutes_ <= 0 || prerequisite_ < -1)
        throw RecipeError("Недопустимый шаг");
    text(instruction_);
}
bool RecipeStep::ready(int completed_steps) const { return prerequisite_ < completed_steps; }
int RecipeStep::finish_at(int start_minute) const {
    if (start_minute < 0)
        throw WorkflowError("Отрицательное время");
    return start_minute + minutes_;
}
} // namespace cooking
