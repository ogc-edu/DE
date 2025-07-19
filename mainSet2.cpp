#include <iostream>
#include "./init.h"
#include "./random.h"
#include "./fitnessEvaluation.h"

#include "./m/best1.h"
#include "./m/best2.h"
#include "./m/best3.h"
#include "./m/currentToBest1.h"
#include "./m/currentToBest2.h"
#include "./m/currentToRand1.h"
#include "./m/currentToRand2.h"
#include "./m/rand1.h"
#include "./m/rand2.h"
#include "./m/rand3.h"

#include "./c/binomialCross.h"
#include "./c/exponentialCross.h"
#include "./s/greedySelection.h"

#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;
const int gen = 2000, dimension = 30, pSize = 100;
float CR = 0.00, f = 0.0;

void set1(float *cr, float *f)
{
  *cr = 0.90;
  *f = 0.50;
}

double average(double array[])
{
  double sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sum += array[i];
  }
  return sum / 10.0;
}

int main()
{
  try
  {
    // ofstream outFileMin("binomial.txt", ios::trunc);            // output best solution in each generation
    // ofstream outFileAverage("binomialAverage.txt", ios::trunc); // output average best solution for each 10 iterations
    // ofstream outTime("binomialTime.txt", ios::trunc);           // output time taken for each iteration
    // ofstream outAverageTime("binomialAvgTime.txt", ios::trunc);
    ofstream outFileMin("exponential.txt", ios::trunc);
    ofstream outFileAverage("exponentialAverage.txt", ios::trunc);
    ofstream outTime("exponentialTime.txt", ios::trunc);
    ofstream outAverageTime("exponentialAvgTime.txt", ios::trunc);
    for (int bench = 0; bench < 10; bench++) // run different benchmark, one benchmark run 10 models, each model run 10 times
    {
      for (int m = 0; m < 10; m++) // mutation loop
      {
        double fitnessAvg[10]; // best solution in each iteration, refresh for each new mutation
        double timeAvg[10];
        for (int repeat = 0; repeat < 10; repeat++)
        {
          auto start = chrono::high_resolution_clock::now();
          set1(&CR, &f);
          double positionVector[pSize][dimension], mutantVector[pSize][dimension], trialVector[pSize][dimension];
          double bestSolution[30];
          double bestFitness = pow(99, 99);
          double rangeMin, rangeMax;
          /*
          f0 - f4 = U
          f5 - f9 = M
          0 Axis Parallel Hyper-Ellipsoid [-5.12, 5.12]
          1 Sum of Different Powers [-1,1]
          2 Rotated Hyper-Ellipsoid Function [-65.536, 65.536]
          3 Schewefel 2.22 Function [-10, 10] -unimodal, saparable
          4 Sphere Function [-5.12, 5.12] -unimodal, saparable
          5 Ackley Function [-30, 30]  -multimodal, non-separable
          6 Rastrigin Function [-5.12, 5.12] -multimodal, separable
          7 Zakharov Function [-5, 10] -multimodal
          8 Griewank Function [-600, 600] -multimodal, non-separable
          9 Quarctic with Noise Function [-1.28, 1.28]
          */

          int bestPos;
          updateRange(&rangeMin, &rangeMax, bench);                         // update min and max range according to benchmark function
          init(positionVector, rangeMin, rangeMax, pSize, &bestPos, bench); // initialize position vectors
          for (int i = 0; i < gen; i++)                                     // start iteration for 2000 generations
          {
            switch (m) // mutation scheme
            {
            case 0:
              Best1Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
              break;

            case 1:
              Best2Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
              break;

            case 2:
              Best3Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
              break;

            case 3:
              currentToBest_1_Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
              break;

            case 4:
              currentToBest_2_Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
              break;

            case 5:
              currentToRand1Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
              break;

            case 6:
              currentToRand2Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
              break;

            case 7:
              rand1Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
              break;

            case 8:
              rand2Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
              break;

            case 9:
              rand3Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
              break;

            default:
              break;
            }
            // binomialCrossover(positionVector, mutantVector, trialVector, CR, pSize);
            exponentialCrossover(positionVector, mutantVector, trialVector, CR, pSize);

            greedySelection(positionVector, trialVector, bench, pSize, bestSolution, &bestFitness, &bestPos); // update bestPos here

          } // end of each generation

          outFileMin << setprecision(30) << bestFitness << endl; // output best fitness throughout 2000 gen(one iteration)
          // for (int i = 0; i < 30; i++)                           // output best solution in each iteration
          // {
          //   cout << bestSolution[i] << endl;
          // }
          fitnessAvg[repeat] = bestFitness; // record best fitness throughout 10 iterations
          auto end = chrono::high_resolution_clock::now();
          chrono::duration<double> elapsed = end - start;
          outTime << elapsed.count() << endl; // output time for each iteration
          timeAvg[repeat] = elapsed.count();
        } // end of 10 iterations
        outTime << "" << endl;
        outFileMin << "" << endl;
        double avgFV = average(fitnessAvg);
        double avgTime = average(timeAvg);
        outFileAverage << setprecision(30) << avgFV << endl;
        outAverageTime << setprecision(30) << avgTime << endl;
      }
    }
  }
  catch (const exception &e)
  {
    cout << "Error" << endl;
    cerr << "An exception occurred: " << e.what() << endl;
    exit(1);
  };
}

// g++ ./m/unique.cpp ./m/best1.cpp ./m/best2.cpp ./m/best3.cpp ./m/currentToBest1.cpp ./m/currentToBest2.cpp ./m/currentToRand1.cpp ./m/currentToRand2.cpp ./m/rand1.cpp ./m/rand2.cpp ./m/rand3.cpp random.cpp ./mainSet2.cpp ./c/exponentialCross.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/binomial.exe