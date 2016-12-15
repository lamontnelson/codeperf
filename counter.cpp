#include "counter.h"

namespace codeperf {
  thread_local std::map<std::string, Counter::counter_type> Counter::counters_;

  void Counter::Increment(std::string name, Counter::counter_type amount) {
      auto it = counters_.find(name);
      if (it == counters_.end())
          counters_[name] = 0;
      counters_[name] += amount;
  }

  void Counter::Decrement(std::string name, Counter::counter_type amount) {
      counters_[name] -= amount;
  }

  void Counter::Remove(std::string name) {
      auto it = counters_.find(name);
      if (it != counters_.end()) {
          counters_.erase(it);
      }
  }

  Counter::counter_type Counter::Get(std::string name) {
      return counters_[name];
  }

  const std::map<std::string, Counter::counter_type>& Counter::GetAll() {
      return counters_;
  }

  void Counter::PrintAll() {
      printf("counters:\n");
      for (auto &p : counters_) {
          auto &n = p.first;
          auto &c = p.second;
          printf("%s = %lu\n", n.c_str(), c);
      }
  }


    BlockCounter::BlockCounter(std::string name) : name_(name) {
  }

  BlockCounter::~BlockCounter() {
      Counter::Increment(name_, 1);
  }
}
