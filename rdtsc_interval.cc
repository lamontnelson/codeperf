#include <string>
#include <vector>
#include <unordered_map>

#include "rdtsc_interval.h"

namespace codeperf {
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

	RdtscInterval::RdtscInterval(std::string name) : name_(name) {
		starts_[name_] = rdtsc();
	}

	RdtscInterval::~RdtscInterval() {
		auto& v = intervals_[name_];
		v.push_back(std::make_pair(starts_[name_], rdtsc() - starts_[name_]));
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
