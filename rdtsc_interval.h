#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "CPUInfo.h"

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
		static std::vector<std::string> Names();
		RdtscInterval(std::string name);
	  	RdtscInterval(std::string name, uint32_t sample_percent);
		~RdtscInterval();


		// T should be std::chrono::duration
		template <typename T>
		static const std::vector<double> IntervalsTime(std::string name) {
			auto &intervals = RdtscInterval::Intervals(name);
			CPUInfo cpuInfo;
			getCPUInfo(cpuInfo);
			const long cpu_hz = cpuInfo.frequency * pow(10,6);
			const double units_per_second = ((double)T::period::den) / ((double)T::period::num);
			const double units_per_cycle = 1.0 / cpu_hz * units_per_second;

			std::vector<double> values;
			for (auto p : intervals) {
				values.push_back(p.second * units_per_cycle);
			}
			return std::move(values);
		}
	};
}
