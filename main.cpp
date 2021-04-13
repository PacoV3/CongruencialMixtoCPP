#include "var_generator.h"
#include <iostream>
#include <chrono>

// int main() {
//     VariableGenerator var_gen {};
//     Variables temp_variables {};
//     int n {100000};
//     auto start = std::chrono::steady_clock::now();

//     for (int i = 0; i < n; i++)
//     {   
//         temp_variables = var_gen.get_correct_variable();
//         // std::cout << temp_variables.a << " - " << temp_variables.c << " - " << temp_variables.m << " - " << temp_variables.seed << std::endl;
//     }

//     auto stop = std::chrono::steady_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
//     std::cout << "Time for " << n << " turns: " << duration / 1e6 << " ms" << std::endl;
//     return 0;
// }