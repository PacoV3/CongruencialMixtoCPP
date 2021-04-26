#pragma once
#include "Variables.h"
#include <iostream>
#include <deque>

class VariableGenerator
{
public:
    Variables get_complete_variable();
    std::deque<Variables> get_complete_variables(int n_variables);
    void save_variables(std::deque<Variables> nice_vars);
    // void test_speed(int times);
};
