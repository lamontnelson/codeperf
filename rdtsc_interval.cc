#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <cmath>

#include "rdtsc_interval.h"
#include "MurmurHash3.h"
#include "CPUInfo.h"

namespace codeperf {
	using namespace std::chrono;
	thread_local std::unordered_map<std::string, RdtscInterval::interval_type> RdtscInterval::starts_;
	thread_local std::unordered_map<std::string, std::vector<RdtscInterval::StartDurationPair>> RdtscInterval::intervals_;

	uint64_t RdtscInterval::rdtsc() {
		uint32_t hi, lo;
		// serialize instructions
		__asm__ __volatile__ (
		"xorl %%eax,%%eax \n    cpuid"
		::: "%rax", "%rbx", "%rcx", "%rdx" );

		__asm__ __volatile__ (
		   "rdtsc" : "=a"(lo), "=d"(hi));
		return (((uint64_t) hi) << 32) | ((uint64_t) lo);
	}

	RdtscInterval::RdtscInterval(std::string name) : name_(name), do_sample_(true) {
		starts_[name_] = rdtsc();
	}

	RdtscInterval::RdtscInterval(std::string name, uint32_t sample_percent) : name_(name) {
        auto us = time_point_cast<microseconds>(system_clock::now()).time_since_epoch().count();
        uint32_t h;
        MurmurHash3_x86_32(static_cast<void*>(&us), sizeof(us), RdtscInterval::seed, &h);
        if (h % 100 < sample_percent) {
              starts_[name_] = rdtsc();
          do_sample_ = true;
        } else {
          do_sample_ = false;
        }
	}


	RdtscInterval::~RdtscInterval() {
        if (do_sample_) {
              auto& v = intervals_[name_];
              v.push_back(std::make_pair(starts_[name_], rdtsc() - starts_[name_]));
        }
	}

	const std::vector<RdtscInterval::StartDurationPair>& RdtscInterval::Intervals(std::string name) {
		return intervals_[name];
	}


	std::vector<std::string> RdtscInterval::Names() {
		std::vector<std::string> result;
		for (auto p : intervals_) {
			auto name = p.first;
			result.push_back(name);
		}
		return result;
	}
}
