#include "Leaderboard.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
Leaderboard::Leaderboard(const std::string &name, const std::vector<Participant> &participants, int first_day)
    : name_(name), participants_(participants), first_day_(first_day) {
    valid(!name_.empty() && first_day_ >= 0, "Invalid leaderboard");
    auto initial = participants_;
    participants_.clear();
    for (const auto &participant : initial)
        join(participant);
}
void Leaderboard::join(const Participant &participant) {
    for (const auto &stored : participants_)
        valid(stored.name() != participant.name(), "Duplicate participant");
    participants_.push_back(participant);
}
std::vector<std::string> Leaderboard::ranking(int last_day) const {
    valid(last_day >= first_day_, "Invalid ranking period");
    auto sorted = participants_;
    std::sort(sorted.begin(), sorted.end(), [&](const auto &left, const auto &right) {
        const auto left_score = left.step_score(first_day_, last_day);
        const auto right_score = right.step_score(first_day_, last_day);
        return left_score == right_score ? left.name() < right.name() : left_score > right_score;
    });
    std::vector<std::string> result;
    for (const auto &participant : sorted)
        result.push_back(participant.name());
    return result;
}
} // namespace fitness
