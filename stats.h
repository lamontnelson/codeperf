//
// Created by lamont on 6/1/16.
//

#ifndef CODEPERF_STATS_H
#define CODEPERF_STATS_H
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace codeperf {

  template <typename T>
  class Optional {
   public:
    Optional() : has_value_(false), v_(T()) {
    }

    Optional(const T& v) : has_value_(true), v_(v) {
    }

    T& operator*() & {
      if (!has_value_) {
        sqrt(-1);
      }
      return v_;
    }

    constexpr T value_or( const T& default_value ) const& {
      if (!has_value_) return T(default_value);
      return v_;
    }

    Optional<T>& operator=( const Optional<T>& other ) {
      if (other.has_value_) {
        this->v_ = other.v_;
        has_value_ = true;
      } else {
        has_value_ = false;
      }
      return *this;
    }

    Optional<T>& operator=( T&& other ) {
      return *this = Optional(other);
    }

   protected:
    bool has_value_;
    T v_;
  };

  template <typename T>
  class Stats {
   public:
    const double MISSING = -99999.99;

    Stats(const std::vector<T>& data) : data_(data) {
      std::sort(data_.begin(), data_.end());
      DoStats();
    }

    ~Stats() {
    }

    T min() { return data_[0]; }
    T max() { return data_[data_.size()-1]; }
    T median() { return Percentile(50); }
    T Percentile(float pct) {
      if (pct==0) {
        return min();
      } else {
        size_t index = ceil(((double)pct/100.0)*((double)data_.size()));
        return data_[index-1];
      }
    }
    double Variance() { return variance_.value_or(MISSING); }
    double StdDev() { return std_dev_.value_or(MISSING); }

    void Report(bool header=false) {
      if (header) {
        std::cout << "min 50 90 99 99.9 max stddev" << std::endl;
      }
      std::cout <<
        min() << " " <<
        Percentile(50) << " " <<
        Percentile(90) << " " <<
        Percentile(99) << " " <<
        Percentile(99.9) << " " <<
        max() << " " <<
        StdDev() << std::endl;
    }
   protected:
    void DoStats() {
      for (T x : data_) {
        sum_ += x;
      }
      mean_ = sum_ / data_.size();

      double sum_square_diff_mean = 0;
      for (T x : data_) {
        double d = x - *mean_;
        sum_square_diff_mean += pow(d, 2);
      }

      if (data_.size() > 0) {
        variance_ = Optional<double>(sum_square_diff_mean / data_.size());
        std_dev_ = Optional<double>(sqrt(*variance_));
      }
    }

    std::vector<T> data_;
    T sum_ = 0;
    Optional<double> mean_;
    Optional<double> std_dev_;
    Optional<double> variance_;
  };
}

#endif //CODEPERF_STATS_H
