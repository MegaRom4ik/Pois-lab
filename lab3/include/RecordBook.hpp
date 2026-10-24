#pragma once
#include "GoalError.hpp"
#include "PersonalRecord.hpp"
#include "Support.hpp"
namespace fitness {
/** Personal records grouped by exercise and repetition count. */
class RecordBook {
  public:
    RecordBook(const std::vector<PersonalRecord> &records = {}, const std::string &owner = "User",
               int capacity = 1000);
    /** Read records. */
    const std::vector<PersonalRecord> &records() const { return records_; }
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Read capacity. */
    const int &capacity() const { return capacity_; }
    /** Insert a new record category or replace a strictly lower load. */
    bool submit(const PersonalRecord &candidate);
    /** Find the best load for one exercise and repetition count. */
    double best_load(const std::string &exercise, int repetitions) const;

  private:
    std::vector<PersonalRecord> records_;
    std::string owner_;
    int capacity_;
};
} // namespace fitness
