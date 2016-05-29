#include "gtest/gtest.h"
#include "counter.h"
#include "interval.h"
#include "stats.h"

namespace codeperf {
  TEST(basic, should_count_on_block_exit) {
      for (int i = 0; i < 10; i++) {
          BlockCounter b("foo");
          auto c = CountMgr::Instance().Get("foo");
          ASSERT_EQ(c, i);
      }
      auto c = CountMgr::Instance().Get("foo");
      ASSERT_EQ(c, 10);
  }

  TEST(basic, should_measure_intervals) {
      const int iterations = 10000;
      Interval interval;
      for (int i = 0; i < iterations; i++) {
          std::string s("");
          interval.Start("FOO");
          for (int j = 0; j < iterations; j++) {
              s += "a";
          }
          interval.End("FOO");
      }
      auto v = interval.Intervals("FOO");
      ASSERT_EQ(v.size(), iterations);

      float sum = 0;
      for (auto d : v) {
          ASSERT_GT(d.count(), 0);
          sum += d.count();
      }
      printf("avg per concatenation: %.10f\n", sum / v.size() / iterations);
  }

  TEST(basic, static_instance_should_work) {
      Interval *i1, *i2;
      i1 = &Interval::instance();
      i2 = &Interval::instance();
      ASSERT_EQ(i1, i2);
  }


  TEST(basic, should_calculate_50th_percentile) {
    std::vector<int> v{4,5,3,1,2, 6, 7, 8, 9, 10};
    Stats<int> stats(v);
    stats.Report();
    ASSERT_EQ(stats.Percentile(50), 5);
  }
}
