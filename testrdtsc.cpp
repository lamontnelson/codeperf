#include <map>
#include <iostream>
#include <cmath>
#include <thread>
#include <assert.h>
#include "rdtsc_interval.h"
#include "stats.h"

using namespace codeperf;

int main() {
    const int tree_size = pow(10,6);
    const int trials = pow(10,4);
    const int ops = pow(10,3);

    std::cout << "tree size: " << tree_size << std::endl;
    std::cout << "trails: " << trials << std::endl;
    std::cout << "ops: " << ops << std::endl;

    std::map<int, int> m;
    for (int i=0; i < tree_size; i++) {
       m[i] = i;
    }

    std::cout << "start loop.\n";
    int sum=0;

    for (int k=0; k < trials; k++) {
        sum = 0;
        if (k % 1000 == 0)
            std::cout << "trial " << k << std::endl;

        {
            int i;
            std::vector<int> keys;
            for (i=0; i<ops; i++) {
                keys.push_back( rand() % tree_size );
            }

            {
                RdtscInterval interval("get");
                for (i = 0; i < ops; i++) {
                    auto k = keys[i];
                    auto it = m.find(k);
                    //sum += it->second;
                }
            }

            {
                RdtscInterval interval("put");
                for (i = 0; i < ops; i++) {
                    auto k = keys[i];
                    m[k] = i;
                }
            }
        }
    }

    std::cout << "sum :" << sum << std::endl;
    {
        typedef codeperf::Stats<RdtscInterval::interval_type> Stats;
        Stats stats(RdtscInterval::Intervals("get"));
        Stats pstats(RdtscInterval::Intervals("put"));

        std::cout << "Get:\n";
        stats.Report(true);
        std::cout << "Put:\n";
        pstats.Report(true);
        std::cout << "get cycles/op: " << stats.median() / ops << std::endl;
        std::cout << "get ops/s: " << 2.2*pow(10,9) / (stats.median() / ops) << std::endl;
        std::cout << "put cycles/op: " << pstats.median() / ops << std::endl;
        std::cout << "put ops/s: " << 2.2*pow(10,9) / (pstats.median() / ops) << std::endl;
    }

}
