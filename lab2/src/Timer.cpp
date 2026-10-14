#include "Timer.hpp"
namespace cooking {
Timer::Timer(int remaining, bool running, int elapsed)
    : remaining_(std::move(remaining)), running_(std::move(running)), elapsed_(std::move(elapsed)) {
    if (remaining_ < 0 || elapsed_ < 0)
        throw WorkflowError("Неверный таймер");
}
void Timer::start() {
    if (running_ || remaining_ == 0)
        throw WorkflowError("Таймер нельзя запустить");
    running_ = true;
}
void Timer::tick(int minutes) {
    if (!running_ || minutes <= 0)
        throw WorkflowError("Таймер не запущен или неверное время");
    const int passed = std::min(minutes, remaining_);
    remaining_ -= passed;
    elapsed_ += passed;
    if (remaining_ == 0)
        running_ = false;
}
} // namespace cooking
