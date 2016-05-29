#ifndef CODEPERF_SAMPLE_H
#define CODEPERF_SAMPLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

namespace codeperf {
  class Interval {
   public:
    typedef std::chrono::microseconds duration_type;

    void Start(std::string name);
    std::chrono::microseconds End(std::string name);
    void Erase(std::string name);
    const std::vector<duration_type> &Intervals(std::string name);
    static Interval& instance() {
      static Interval* i = new Interval();
      return *i;
    }
   protected:
    std::unordered_map<std::string, std::chrono::time_point<std::chrono::steady_clock>> starts;
    std::unordered_map<std::string, std::vector<duration_type>> intervals;
  };

  class BlockInterval {
   public:
    BlockInterval(std::string name);
    ~BlockInterval();
   protected:
    std::string name_;
    Interval &interval_;
  };
}
#endif //CODEPERF_SAMPLE_H
