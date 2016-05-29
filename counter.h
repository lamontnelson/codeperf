#ifndef CODEPERF_COUNTER_H
#define CODEPERF_COUNTER_H
#include <map>
#include <string>

namespace codeperf {
  class CountMgr {
   public:
    typedef long int counter_type;

    static CountMgr &Instance();
    void Increment(std::string name, counter_type amount = 1);
    void Decrement(std::string name, counter_type amount = 1);
    void Remove(std::string name);
    counter_type Get(std::string name);
    const std::map<std::string, counter_type>& GetAll();

   protected:
    std::map<std::string, counter_type> counters;
  };

  class BlockCounter {
   public:
    BlockCounter(std::string name);
    ~BlockCounter();

   protected:
    std::string name_;
  };
}
#endif //CODEPERF_COUNTER_H
