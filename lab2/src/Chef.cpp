#include "Chef.hpp"
namespace cooking {
Chef::Chef(std::string name, SkillProfile skills, int available_minutes)
    : name_(std::move(name)), skills_(std::move(skills)), available_minutes_(std::move(available_minutes)) {
    text(name_);
    if (available_minutes_ < 0)
        throw WorkflowError("Неверное рабочее время");
}
void Chef::assign(const Recipe &recipe) {
    if (recipe.duration() > available_minutes_)
        throw WorkflowError("Нет времени у повара");
    available_minutes_ -= recipe.duration();
}
bool Chef::can_cook(const std::string &technique, int level) const { return skills_.qualifies(technique, level); }
} // namespace cooking
