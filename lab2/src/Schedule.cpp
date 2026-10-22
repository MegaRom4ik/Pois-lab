#include "Schedule.hpp"
namespace cooking {
Schedule::Schedule(std::string day, std::vector<Task> tasks, int shift_minutes)
    : day_(std::move(day)), tasks_(std::move(tasks)), shift_minutes_(std::move(shift_minutes)) {
    text(day_);
    if (shift_minutes_ <= 0)
        throw WorkflowError("Неверная смена");
}
int Schedule::workload() const {
    int total = 0;
    for (const auto &task : tasks_)
        total += task.recipe().duration();
    return total;
}
void Schedule::add(const Task &task) {
    if (workload() + task.recipe().duration() > shift_minutes_)
        throw WorkflowError("Смена перегружена");
    tasks_.push_back(task);
}
} // namespace cooking
