#include "counter.h"

namespace codeperf {
  thread_local std::map<std::string, CountMgr::counter_type> CountMgr::counters_;

  void CountMgr::Increment(std::string name, CountMgr::counter_type amount) {
      counters_[name] += amount;
  }

  void CountMgr::Decrement(std::string name, CountMgr::counter_type amount) {
      counters_[name] -= amount;
  }

  void CountMgr::Remove(std::string name) {
      auto it = counters_.find(name);
      if (it != counters_.end()) {
          counters_.erase(it);
      }
  }

  CountMgr::counter_type CountMgr::Get(std::string name) {
      return counters_[name];
  }

  const std::map<std::string, CountMgr::counter_type>& CountMgr::GetAll() {
      return counters_;
  }

  BlockCounter::BlockCounter(std::string name) : name_(name) {
  }

  BlockCounter::~BlockCounter() {
      CountMgr::Increment(name_, 1);
  }
}
