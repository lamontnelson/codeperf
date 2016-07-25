#include <string>
#include <vector>
#include <unordered_map>

#include "rdtsc_interval.h"

namespace codeperf {
	std::unordered_map<std::string, uint64_t> RdtscInterval::starts_;
	std::unordered_map<std::string, std::vector<uint64_t>> RdtscInterval::intervals_;

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
		v.push_back(rdtsc() - starts_[name_]);
	}

	const std::vector<RdtscInterval::interval_type>& RdtscInterval::Intervals(std::string name) {
		return intervals_[name];
	}
}
