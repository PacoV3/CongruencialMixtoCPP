#pragma once
#include "Variables.h"
#include <iostream>
#include <deque>

class Test
{
public:
    std::deque<Variables> apply_tests(int n_variables, int sample_size);
};
