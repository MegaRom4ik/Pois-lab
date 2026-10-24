#pragma once
#include "KitchenTool.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A tool cleaning task with time tracking. */
class CleaningTask {
  public:
    CleaningTask(KitchenTool tool = KitchenTool{}, int required_minutes = 5, int spent_minutes = 0);
    const KitchenTool &tool() const { return tool_; }
    int required_minutes() const { return required_minutes_; }
    int spent_minutes() const { return spent_minutes_; }
    void work(int minutes);
    KitchenTool finish() const;

  private:
    KitchenTool tool_;
    int required_minutes_;
    int spent_minutes_;
};
} // namespace cooking
