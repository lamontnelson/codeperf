#include "interval.h"

namespace codeperf {
  thread_local std::unordered_map<std::string, std::chrono::time_point<std::chrono::steady_clock>> Interval::starts_;
  thread_local std::unordered_map<std::string, std::vector<Interval::duration_type>> Interval::intervals_;

  void Interval::Start(std::string name) {
    starts_[name] = std::chrono::steady_clock::now();
  }

  void Interval::Erase(std::string name) {
    starts_.erase(name);
    intervals_.erase(name);
  }

  Interval::duration_type Interval::End(std::string name) {
    auto end = std::chrono::steady_clock::now();
    auto d = std::chrono::duration_cast<Interval::duration_type>(end - starts_[name]);
    auto &v = intervals_[name];
    v.push_back(d);
    return d;
  }

  const std::vector<std::string> Interval::Names() {
    std::vector<std::string> names;
    for (auto p : intervals_) {
      names.push_back(p.first);
    }
    return names;
  }

  const std::vector<Interval::duration_type> &Interval::Intervals(std::string name) {
    return intervals_[name];
  }

  BlockInterval::BlockInterval(std::string name) : name_(name) {
    Interval::Start(name_);
  }

  BlockInterval::~BlockInterval() {
    Interval::End(name_);
  }
}
