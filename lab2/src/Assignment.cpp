#include "Assignment.hpp"
namespace cooking {
Assignment::Assignment(Chef chef, Task task, Workstation station, bool started)
    : chef_(std::move(chef)), task_(std::move(task)), station_(std::move(station)), started_(std::move(started)) {}
void Assignment::start(int minute) {
    if (started_ || !task_.fits(minute))
        throw WorkflowError("Назначение не готово");
    Chef next = chef_;
    Workstation place = station_;
    next.assign(task_.recipe());
    place.reserve(Quantity{});
    chef_ = next;
    station_ = place;
    started_ = true;
}
void Assignment::finish(int minute) {
    if (!started_)
        throw WorkflowError("Задание не начато");
    task_.complete(minute);
    station_.release();
    started_ = false;
}
} // namespace cooking
