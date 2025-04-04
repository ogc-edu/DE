#include "fitnessEvaluation.h"
#include <iostream>
#define _USE_MATH_DEFINES // define use_math_defines macro before including <math.h>
#include <math.h>
#define dimension 30 // number of bits (dimension size)
#include "random.h"

using namespace std;

float fv = 0, sumFit = 0;

double fitness(double a[], int bench)
{
    sumFit = 0;
    //---------------------------------------------------------------------------------------------------------------------------
    // Insert Benchmark Functions

    //---------------------------------------------------------------------------------------------------------------------------

    if (bench == 0)
    {
        // Axis Parallel Hyper-Ellipsoid function
        for (int j = 0; j < dimension; j++)
        {
            sumFit += pow(a[j], 2) * (j + 1);
        }
        return sumFit;
    }
    else if (bench == 1)
    {
        // sum of different powers function
        for (int i = 0; i < dimension; i++)
        {
            sumFit += pow(fabs(a[i]), i + 2);
        }
        return sumFit;
    }
    else if (bench == 2)
    {
        // Rotated Hyper-Ellipsoid Function
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                sumFit += pow(a[j], 2);
            }
        }
        return sumFit;
    }
    else if (bench == 3)
    {
        // Schwefel 2.22
        double sumFit2 = 1;
        for (int counting = 0; counting < dimension; counting++)
        {
            sumFit += fabs(a[counting]);
            sumFit2 *= fabs(a[counting]);
        }
        return (sumFit + sumFit2);
    }
    else if (bench == 4)
    {
        // Sphere
        for (int j = 0; j < dimension; j++)
        {
            fv = pow(a[j], 2);
            sumFit = sumFit + fv;
        }
        return sumFit;
    }
    else if (bench == 5)
    {
        // Ackley
        float firstPartX = 0, firstPart = 0, secondPartX = 0, secondPart;
        for (int i = 0; i < dimension; i++)
        {
            firstPartX += pow(a[i], 2);
            secondPartX += cos(2 * M_PI * a[i]);
        }
        firstPart = -20 * exp(-0.2 * sqrt(firstPartX / dimension));
        secondPart = exp((1 / dimension) * secondPartX);
        return (firstPart - secondPart + 20 + exp(1));
    }
    else if (bench == 6)
    {
        // rastrigin
        float firstPart = 10 * dimension;
        for (int i = 0; i < dimension; i++)
        {
            fv = pow(a[i], 2) - 10 * cos(2 * M_PI * a[i]);
            sumFit += fv;
        }
        return firstPart + sumFit;
    }
    else if (bench == 7)
    {
        // Zakharov
        float x1 = 0, x2 = 0;
        for (int i = 0; i < dimension; i++)
        {
            x1 += pow(a[i], 2);
        }
        for (int i = 0; i < dimension; i++)
        {
            x2 += (0.5 * a[i]);
        }
        return x1 + pow(x2, 2) + pow(x2, 4);
    }
    else if (bench == 8)
    {
        // griewank
        float sumFit1 = 0, sumFit2 = 1;
        for (int i = 0; i < dimension; i++)
        {
            sumFit1 += pow(a[i], 2);
            sumFit2 *= cos(a[i] / sqrt(i + 1));
        }
        sumFit1 /= 4000;
        return sumFit1 - sumFit2 + 1;
    }
    else if (bench == 9)
    {
        // Quartic with Noise function
        for (int i = 0; i < dimension; i++)
        {
            sumFit += ((i + 1) * pow(a[i], 4)) + generateRandomFloat();
        }
        return sumFit;
    }

    else
        return 0;
}

void updateRange(double *rangeMin, double *rangeMax, int bench)
{
    if (bench == 0) // Axis Parallel Hyper Ellipsoid
    {
        *rangeMin = -5.12;
        *rangeMax = 5.12;
    }
    if (bench == 1) // Sum of Different Powers
    {
        *rangeMin = -1.00;
        *rangeMax = 1.00;
    }
    if (bench == 2) // Rotated Hyper-Ellipsoid
    {
        *rangeMin = -65.536;
        *rangeMax = 65.536;
    }
    if (bench == 3) // Schwefel 2.22
    {
        *rangeMin = -10.00;
        *rangeMax = 10.00;
    }
    if (bench == 4) // Sphere
    {
        *rangeMin = -5.12;
        *rangeMax = 5.12;
    }
    if (bench == 5) // Ackley
    {
        *rangeMin = -30.00;
        *rangeMax = 30.00;
    }
    if (bench == 6) // Rastrigin
    {
        *rangeMin = -5.12;
        *rangeMax = 5.12;
    }
    if (bench == 7) // Zakharov
    {
        *rangeMin = -5;
        *rangeMax = 10;
    }
    if (bench == 8) // Griewank
    {
        *rangeMin = -600;
        *rangeMax = 600;
    }
    if (bench == 9) // Quartic with Noise
    {
        *rangeMin = -1.28;
        *rangeMax = 1.28;
    }
}