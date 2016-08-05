#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

namespace codeperf {
  class Interval {
   public:
    typedef std::chrono::microseconds duration_type;
    typedef std::pair<std::chrono::time_point<std::chrono::steady_clock>,Interval::duration_type> StartDurationPair;

    static void Start(std::string name);
    static std::chrono::microseconds End(std::string name);
    static const std::vector<std::pair<std::chrono::time_point<std::chrono::steady_clock>,Interval::duration_type>> &Intervals(std::string name);
    static const std::vector<std::string> Names();
    static void Erase(std::string name);

   protected:
    thread_local static std::unordered_map<std::string, std::chrono::time_point<std::chrono::steady_clock>> starts_;
    thread_local static std::unordered_map<std::string, std::vector<std::pair<std::chrono::time_point<std::chrono::steady_clock>,Interval::duration_type>>> intervals_;
  };


  class BlockInterval {
   public:
    BlockInterval(std::string name);
    ~BlockInterval();
   protected:
    std::string name_;
  };
}
