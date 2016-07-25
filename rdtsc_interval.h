#include <string>
#include <vector>
#include <unordered_map>

namespace codeperf {
	struct RdtscInterval {
		typedef uint64_t interval_type;
		static std::unordered_map<std::string, interval_type> starts_;
		static std::unordered_map<std::string, std::vector<interval_type>> intervals_;
		std::string name_;

		static interval_type rdtsc();
		static const std::vector<interval_type>& Intervals(std::string name);
		RdtscInterval(std::string name);
		~RdtscInterval();
	};
}
