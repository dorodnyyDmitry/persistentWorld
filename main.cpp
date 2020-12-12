#include "worlds.hpp"

int main()
{

    nonius::configuration cfg;
    nonius::benchmark_registry benchmarks = {
        nonius::benchmark("init_automatic(100)", []{ init_automatic(100); })
    };

    nonius::go(cfg, benchmarks);

}
