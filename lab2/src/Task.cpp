#include "Task.hpp"
namespace cooking {
Task::Task(Recipe recipe, int deadline, bool completed)
    : recipe_(std::move(recipe)), deadline_(std::move(deadline)), completed_(std::move(completed)) {
    if (deadline_ < 0)
        throw WorkflowError("Неверный срок задания");
}
bool Task::fits(int start) const { return start >= 0 && start + recipe_.duration() <= deadline_; }
void Task::complete(int finish) {
    if (completed_ || finish < 0 || finish > deadline_)
        throw WorkflowError("Невозможно закрыть задание");
    completed_ = true;
}
} // namespace cooking
