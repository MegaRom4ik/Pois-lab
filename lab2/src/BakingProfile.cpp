#include "BakingProfile.hpp"
namespace cooking {
BakingProfile::BakingProfile(std::string name, double temperature, int minutes)
    : name_(std::move(name)), temperature_(std::move(temperature)), minutes_(std::move(minutes)) {
    text(name_);
    positive(temperature_);
    if (minutes_ <= 0)
        throw RecipeError("Неверный режим выпечки");
}
void BakingProfile::prepare(Oven &oven) const { oven.preheat(temperature_); }
int BakingProfile::finish_at(int start) const {
    if (start < 0)
        throw WorkflowError("Неверное время выпечки");
    return start + minutes_;
}
} // namespace cooking
