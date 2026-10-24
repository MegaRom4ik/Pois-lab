#include "RecordBook.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
RecordBook::RecordBook(const std::vector<PersonalRecord> &records, const std::string &owner, int capacity)
    : records_(records), owner_(owner), capacity_(capacity) {
    valid(!owner_.empty() && capacity_ > 0, "Invalid record book");
    auto initial = records_;
    records_.clear();
    for (const auto &record : initial)
        submit(record);
}
bool RecordBook::submit(const PersonalRecord &candidate) {
    for (auto &record : records_) {
        if (record.exercise().name() != candidate.exercise().name() ||
            record.repetitions() != candidate.repetitions())
            continue;
        if (!candidate.beats(record)) return false;
        record = candidate;
        return true;
    }
    valid(records_.size() < static_cast<std::size_t>(capacity_), "Record book full");
    records_.push_back(candidate);
    return true;
}
double RecordBook::best_load(const std::string &exercise, int repetitions) const {
    for (const auto &record : records_)
        if (record.exercise().name() == exercise && record.repetitions() == repetitions)
            return record.load_kg();
    throw GoalError("Record not found");
}
} // namespace fitness
