#pragma once
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A timer for a cooking step. */
class Timer {
  public:
    Timer(int remaining = 5, bool running = false, int elapsed = 0);
    int remaining() const { return remaining_; }
    bool running() const { return running_; }
    int elapsed() const { return elapsed_; }
    void start();
    void tick(int minutes);

  private:
    int remaining_;
    bool running_;
    int elapsed_;
};
} // namespace cooking
