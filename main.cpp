#include "Test.h"
#include <iostream>
#include <chrono>
#include <deque>

int main()
{
    Test t;
    int n_vars = 500;
    int sample_size = 500;
    auto start = std::chrono::steady_clock::now();

    auto correct_vars = t.apply_tests(n_vars, sample_size);
    // for (const auto &var : correct_vars)
    // {
    //     std::cout << var.a << std::endl;
    // }
    std::cout << correct_vars.size() << " correct variables." << std::endl;

    auto stop = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    std::cout << "Time for " << n_vars << " turns with a sample size of " 
                << sample_size << ": " << duration / 1e6 << " ms" << std::endl;
    return 0;
}
