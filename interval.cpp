#include "interval.h"

namespace codeperf {
  void Interval::Start(std::string name) {
    starts[name] = std::chrono::steady_clock::now();
  }

  void Interval::Erase(std::string name) {
    starts.erase(name);
    intervals.erase(name);
  }

  Interval::duration_type Interval::End(std::string name) {
    auto end = std::chrono::steady_clock::now();
    auto d = std::chrono::duration_cast<Interval::duration_type>(end - starts[name]);
    auto &v = intervals[name];
    v.push_back(d);
    return d;
  }

  const std::vector<Interval::duration_type> &Interval::Intervals(std::string name) {
    return intervals[name];
  }

  BlockInterval::BlockInterval(std::string name) : name_(name), interval_(Interval::instance()) {
    interval_.Start(name);
  }

  BlockInterval::~BlockInterval() {
    interval_.End(name_);
  }
}
