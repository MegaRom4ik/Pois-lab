#pragma once
#include "Chef.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include "Task.hpp"
#include "WorkflowError.hpp"
#include "Workstation.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A task assigned to a chef and workstation. */
class Assignment {
  public:
    Assignment(Chef chef = Chef{}, Task task = Task{}, Workstation station = Workstation{}, bool started = false);
    const Chef &chef() const { return chef_; }
    const Task &task() const { return task_; }
    const Workstation &station() const { return station_; }
    bool started() const { return started_; }
    void start(int minute);
    void finish(int minute);

  private:
    Chef chef_;
    Task task_;
    Workstation station_;
    bool started_;
};
} // namespace cooking
