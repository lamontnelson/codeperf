#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace codeperf {
	struct RdtscInterval {
		typedef uint64_t interval_type;
		typedef std::pair<interval_type, interval_type> StartDurationPair;
    	static const uint32_t seed = 0xdeaddead;
		static thread_local std::unordered_map<std::string, interval_type> starts_;
		static thread_local std::unordered_map<std::string, std::vector<StartDurationPair>> intervals_;
		std::string name_;
    	bool do_sample_;
		static interval_type rdtsc();
		static const std::vector<StartDurationPair>& Intervals(std::string name);
		static const std::vector<double> IntervalsMs(std::string name);
		static std::vector<std::string> Names();
		RdtscInterval(std::string name);
	  	RdtscInterval(std::string name, uint32_t sample_percent);
		~RdtscInterval();
	};
}
