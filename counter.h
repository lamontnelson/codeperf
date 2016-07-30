#ifndef CODEPERF_COUNTER_H
#define CODEPERF_COUNTER_H
#include <map>
#include <string>

namespace codeperf {
  class Counter {
   public:
    typedef long int counter_type;

    static void Increment(std::string name, counter_type amount = 1);
    static void Decrement(std::string name, counter_type amount = 1);
    static counter_type Get(std::string name);
    static const std::map<std::string, counter_type>& GetAll();
    static void Remove(std::string name);

   protected:
    static thread_local std::map<std::string, counter_type> counters_;
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
