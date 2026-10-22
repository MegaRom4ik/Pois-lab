#include "CleaningTask.hpp"
namespace cooking {
CleaningTask::CleaningTask(KitchenTool tool, int required_minutes, int spent_minutes)
    : tool_(std::move(tool)), required_minutes_(std::move(required_minutes)), spent_minutes_(std::move(spent_minutes)) {
    if (required_minutes_ <= 0 || spent_minutes_ < 0)
        throw WorkflowError("Неверное задание мойки");
}
void CleaningTask::work(int minutes) {
    if (minutes <= 0)
        throw WorkflowError("Неверное время уборки");
    spent_minutes_ += minutes;
}
KitchenTool CleaningTask::finish() const {
    if (spent_minutes_ < required_minutes_)
        throw WorkflowError("Мойка не завершена");
    KitchenTool result = tool_;
    if (!result.clean())
        result.wash();
    return result;
}
} // namespace cooking
