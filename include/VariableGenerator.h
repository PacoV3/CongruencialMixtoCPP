#pragma once
#include "Variables.h"

class VariableGenerator
{
    Variables variables;

    public:
    Variables get_correct_variable();
    void test_speed(int times);
};
