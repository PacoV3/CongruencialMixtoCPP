#include "VariableGenerator.h"
#include "Test.h"
#include <iostream>
#include <chrono>
#include <deque>

using namespace std::chrono;

int main()
{
    Test t{};
    VariableGenerator var_gen{};
    std::deque<Variables> nice_vars{};
    int n_vars = 1000;
    int sample_size = 1000;
    auto start = steady_clock::now();

    auto correct_vars = var_gen.get_complete_variables(n_vars);
    for (const auto &var : correct_vars)
    {
        if (t.apply_tests(var, sample_size)) {
            nice_vars.push_front(var);
        }
    }
    std::cout << "From " << n_vars << " variables we got " <<  nice_vars.size() 
                << " full variables." << std::endl;

    auto stop = steady_clock::now();
    var_gen.save_variables(nice_vars);
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    std::cout << "Time for " << n_vars << " turns with a sample size of " 
                << sample_size << ": " << duration / 1e6 << " ms" << std::endl;
    return 0;
}
