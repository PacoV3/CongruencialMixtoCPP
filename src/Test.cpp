#include "VariableGenerator.h"
#include "Variables.h"
#include "Test.h"
#include <iostream>
#include <deque>
#include <math.h>
#include <algorithm>
#include <cmath>

int calc_xn1(Variables var, int xn)
{
    return (var.a * xn + var.c) % var.m;
}

// alpha == 5%
bool mean_test(float const random_samples[], int sample_size)
{
    float const EXPECTED_MEAN = 0.5;
    float const Z_VALUE = 1.96;
    float sum{}, observed_mean{}, z0{};
    for (int i = 0; i < sample_size; i++)
    {
        sum += random_samples[i];
    }
    observed_mean = sum / sample_size;
    z0 = (observed_mean - EXPECTED_MEAN) * sqrt(sample_size) / sqrt(1 / 12.0);
    return abs(z0) < Z_VALUE;
}

// alpha == 5%
bool frequency_test(float const random_samples[], int sample_size, int n)
{
    // From n = 2 to n = 11
    float const CHI_VALS[] = {3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067, 15.507, 16.919, 18.307};
    float const EXPECTED_FREQUENCY = (float)sample_size / n;
    float val = 1.0 / n;
    float observed_frequency[n]{};
    float chi2_0{}, chi2_alpha_lib = CHI_VALS[n - 2];
    for (int i = 0; i < sample_size; i++)
    {
        for (int interval = 0; interval < n; interval++)
        {
            if (val * interval <= random_samples[i] && random_samples[i] < val * (interval + 1))
            {
                observed_frequency[interval]++;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        chi2_0 += pow(observed_frequency[i] - EXPECTED_FREQUENCY, 2) / EXPECTED_FREQUENCY;
    }
    return chi2_0 < chi2_alpha_lib;
}

// alpha == 5%
bool series_test(float const random_samples[], int sample_size, int n)
{
    // From n = 2 to n = 5
    float const CHI_VALS[] = {7.815, 15.507, 24.996, 36.415};
    int pow2_n = (int)pow(n, 2);
    float const EXPECTED_FREQUENCY = (sample_size - 1) / (float)pow2_n;
    float val = 1.0 / n;
    float observed_frequency[pow2_n]{};
    float chi2_0{}, chi2_alpha_lib = CHI_VALS[n - 2];
    for (int i = 0; i < sample_size - 1; i++)
    {
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if ((val * row <= random_samples[i] && random_samples[i] < val * (row + 1)) &&
                    (val * col <= random_samples[i + 1] && random_samples[i + 1] < val * (col + 1)))
                {
                    observed_frequency[row * n + col]++;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < pow2_n; i++)
    {
        chi2_0 += pow(observed_frequency[i] - EXPECTED_FREQUENCY, 2);
    }
    chi2_0 = (float)pow2_n / (sample_size - 1) * chi2_0;
    return chi2_0 < chi2_alpha_lib;
}

// alpha == 5%
bool poker_test(float const random_samples[], int sample_size)
{
    float CHI_VALS[] = {3.841, 5.991, 7.815, 9.488, 11.070, 12.592, 14.067};
    float P[] = {0.0001, 0.0045, 0.009, 0.072, 0.108, 0.504, 0.3024};
    float expected_frequency[7]{};
    float observed_frequency[7]{};
    int hand[10]{};
    int index{}, max_val{}, count = 0;
    float accumulated_ef{}, accumulated_of{}, chi2_0{}, chi2_alpha_lib{};
    for (int i = 0; i < 7; i++)
    {
        expected_frequency[i] = sample_size * P[i];
    }
    for (int i = 0; i < sample_size; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            index = (int)(pow(10, j + 1) * random_samples[i]) % 10;
            hand[index]++;
        }
        max_val = *std::max_element(hand, hand + 10);
        switch (max_val) {
            case 5:
                observed_frequency[0]++;
                break;
            case 4:
                observed_frequency[1]++;
                break;
            case 3:
                if (std::find(hand, hand + 10, 2) != hand + 10)
                    observed_frequency[2]++;
                else
                    observed_frequency[3]++;
                break;
            case 2:
                if (std::count(hand, hand + 10, 2) == 2)
                    observed_frequency[4]++;
                else
                    observed_frequency[5]++;
                break;
            case 1:
                observed_frequency[6]++;
                break;
        }
        std::fill(hand, hand + 10, 0);       
    }
    while (accumulated_ef + expected_frequency[count] < 5 && count + 1 < 7)
    {
        accumulated_ef += expected_frequency[count];
        accumulated_of += observed_frequency[count];
        count++;
    }
    for (int i = count; i < 7; i++)
    {
        chi2_0 += pow(observed_frequency[i] - expected_frequency[i], 2) / expected_frequency[i]; 
    }
    chi2_0 += pow(accumulated_ef - accumulated_of, 2) / accumulated_ef;
    chi2_alpha_lib = CHI_VALS[count];
    return chi2_0 < chi2_alpha_lib;
}

bool Test::apply_tests(Variables vars, int sample_size)
{
    float random_samples[sample_size]{};
    float xn{}, xn1{};
    // Create the random samples for the tests
    for (int j = 0; j < sample_size; j++)
    {
        // The first time xn == seed
        xn = j == 0 ? vars.seed : xn1;
        xn1 = calc_xn1(vars, xn);
        random_samples[j] = xn1 / vars.m;
    }

    // Put in practice each test
    if (!mean_test(random_samples, sample_size))
        return false;
    if (!frequency_test(random_samples, sample_size, 11))
        return false;
    if (!series_test(random_samples, sample_size, 5))
        return false;
    if (!poker_test(random_samples, sample_size))
        return false;
    return true;
}
