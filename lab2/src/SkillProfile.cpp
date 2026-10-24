#include "SkillProfile.hpp"
namespace cooking {
SkillProfile::SkillProfile(std::string speciality, int level, int practice_hours)
    : speciality_(std::move(speciality)), level_(std::move(level)), practice_hours_(std::move(practice_hours)) {
    text(speciality_);
    if (level_ < 1 || level_ > 5 || practice_hours_ < 0)
        throw WorkflowError("Неверная квалификация");
}
void SkillProfile::practice(int hours) {
    if (hours <= 0)
        throw WorkflowError("Неверная длительность практики");
    practice_hours_ += hours;
    level_ = std::min(5, 1 + practice_hours_ / 10);
}
bool SkillProfile::qualifies(const std::string &technique, int required_level) const {
    return speciality_ == technique && level_ >= required_level;
}
} // namespace cooking
