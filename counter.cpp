#include "counter.h"

namespace codeperf {
  CountMgr &CountMgr::Instance() {
      static CountMgr mgr = CountMgr();
      return mgr;
  }

  void CountMgr::Increment(std::string name, CountMgr::counter_type amount) {
      counters[name] += amount;
  }

  void CountMgr::Decrement(std::string name, CountMgr::counter_type amount) {
      counters[name] -= amount;
  }

  void CountMgr::Remove(std::string name) {
      auto it = counters.find(name);
      if (it != counters.end()) {
          counters.erase(it);
      }
  }

  CountMgr::counter_type CountMgr::Get(std::string name) {
      return counters[name];
  }

  const std::map<std::string, CountMgr::counter_type>& CountMgr::GetAll() {
      return counters;
  }

  BlockCounter::BlockCounter(std::string name) : name_(name) {
  }

  BlockCounter::~BlockCounter() {
      auto &mgr = CountMgr::Instance();
      mgr.Increment(name_, 1);
  }
}
