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
const int gen = 2000, dimension = 30, pSize = 40;
float CR = 0.00, f = 0.0;

void set1(float *cr, float *f)
{
  *cr = 0.80;
  *f = 0.30;
}

double average(double array[])
{
  double sum;
  for (int i = 0; i < 10; i++)
  {
    sum += array[i];
  }
  return sum / 10.0;
}

int main()
{
  ofstream outFileMin("allBinomial.txt", ios::trunc);   // best throughout 2000
  ofstream outFileAverage("allBinAvg.txt", ios::trunc); // average of 10 iteration of the same mutation
  ofstream outTime("time.txt", ios::trunc);
  for (int bench = 0; bench < 10; bench++) // loop through benchmarks
  {
    for (int m = 0; m < 10; m++) // diff mutation loop
    {
      double tenIterationMin[10];
      for (int repeat = 0; repeat < 10; repeat++)
      {
        auto start = chrono::high_resolution_clock::now();
        set1(&CR, &f);
        double positionVector[pSize][dimension], mutantVector[pSize][dimension], trialVector[pSize][dimension];
        double bestSolution[30], bestFitness = pow(99, 99);
        double rangeMin, rangeMax;
        /*
        f0 - f3 = U
        f4 - f9 = M
        0 Axis Parallel Hyper-Ellipsoid [-5.12, 5.12]
        1 Sum of Different Powers [-1,1]
        2 Rotated Hyper-Ellipsoid Function [-65.536, 65.536]
        3 Schewefel 2.22 Function [-10, 10]
        4 Sphere Function [-5.12, 5.12]
        5 Ackley Function [-30, 30]
        6 Rastrigin Function [-5.12, 5.12]
        7 Zakharov Function [-5, 10]
        8 Griewank Function [-600, 600]
        9 Quarctic with Noise Function [-1.28, 1.28]
        */

        int bestPos;
        updateRange(&rangeMin, &rangeMax, bench);                         // update min and max range according to benchmark function
        init(positionVector, rangeMin, rangeMax, pSize, &bestPos, bench); // initialize position vectors

        for (int i = 0; i < gen; i++) // start iteration for 2000 generations
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

        outFileMin << setprecision(15) << bestFitness << endl; // output best fitness throughout 2000 gen(one iteration)
        tenIterationMin[repeat] = bestFitness;                 // record best fitness throughout 10 iterations
        for (int i = 0; i < 30; i++)                           // output best solution in each iteration
        {
          cout << bestSolution[i] << endl;
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        outTime << elapsed.count() << endl;
      }
      outFileMin << "" << endl;
      double avg = average(tenIterationMin);
      outFileAverage << setprecision(15) << avg << endl;
    }
  }
}

// g++ ./m/unique.cpp ./m/best1.cpp ./m/best2.cpp ./m/best3.cpp ./m/currentToBest1.cpp ./m/currentToBest2.cpp ./m/currentToRand1.cpp ./m/currentToRand2.cpp ./m/rand1.cpp ./m/rand2.cpp ./m/rand3.cpp random.cpp ./main.cpp ./c/exponentialCross.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/main.exe