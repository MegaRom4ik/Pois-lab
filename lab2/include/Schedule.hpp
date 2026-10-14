#pragma once
#include "Support.hpp"
#include "Task.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** План заданий с проверкой общего времени. */
class Schedule {
  public:
    Schedule(std::string day = "Понедельник", std::vector<Task> tasks = {}, int shift_minutes = 480);
    const std::string &day() const { return day_; }
    const std::vector<Task> &tasks() const { return tasks_; }
    int shift_minutes() const { return shift_minutes_; }
    int workload() const;
    void add(const Task &task);

  private:
    std::string day_;
    std::vector<Task> tasks_;
    int shift_minutes_;
};
} // namespace cooking
