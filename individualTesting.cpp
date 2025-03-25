#include <iostream>
#include "./init.h"
#include "./random.h"
#include "./fitnessEvaluation.h"
#include "./m/unique.h"

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

using namespace std;
const int gen = 2000, dimension = 30, pSize = 40;
float CR = 0.00, f = 0.0;

void set1(float *cr, float *f)
{
  *cr = 0.80;
  *f = 0.30;
}

int main()
{
  ofstream outFile("txt/individualOutput.txt", ios::app); // output each gen best
  for (int repeat = 0; repeat < 1; repeat++)
  {
    set1(&CR, &f);
    double positionVector[pSize][dimension], mutantVector[pSize][dimension], trialVector[pSize][dimension], positionFV[pSize], trialFV[pSize];
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
    int bench = 7;                            // select benchmark function
    updateRange(&rangeMin, &rangeMax, bench); // update min and max range according to benchmark function

    int bestPos;
    init(positionVector, rangeMin, rangeMax, pSize, &bestPos, bench);

    cout << "Start now" << endl;

    for (int i = 0; i < 10; i++) // gen
    {
      // Best1Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
      // Best2Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
      // Best3Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
      // currentToBest_1_Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
      // currentToBest_2_Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
      // currentToRand1Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
      // currentToRand2Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
      // rand1Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
      // rand2Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);
      // rand3Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench);

      binomialCrossover(positionVector, mutantVector, trialVector, CR, pSize);
      // exponentialCrossover(positionVector, mutantVector, trialVector, CR, pSize);

      greedySelection(positionVector, trialVector, bench, pSize, bestSolution, &bestFitness, &bestPos); // update bestPos here

      outFile << bestFitness << endl;
      if (i % 10 == 0)
      {
        cout << "Gen " << i << " best index " << bestPos << endl;
      }
    }

    cout << "The best fitness value is " << setprecision(8) << bestFitness << "\n"
         << "The best solution " << endl;
    outFile << bestFitness << endl; // output best fitness throughout 2000 gen
    for (int i = 0; i < 30; i++)
    {
      cout << bestSolution[i] << endl;
    }
  }
  outFile << "" << endl;
}

// g++ ./m/best1.cpp ./m/best2.cpp ./m/unique.cpp ./m/best3.cpp ./m/currentToBest1.cpp ./m/currentToBest2.cpp ./m/currentToRand1.cpp ./m/currentToRand2.cpp ./m/rand1.cpp ./m/rand2.cpp ./m/rand3.cpp random.cpp ./testIndi.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/run.exe

// g++ ./m/best1.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best1BG.exe
// g++ ./m/best2.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best2BG.exe
// g++ ./m/best3.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best3BG.exe
// g++ ./m/best1.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best1BG.exe
// g++ ./m/best2.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best2BG.exe
// g++ ./m/best3.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best3BG.exe

// g++ ./m/currentToBest1.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToBest1BG.exe
// g++ ./m/currentToBest2.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToBest2BG.exe
// g++ ./m/currentToBest1.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToBest2BG.exe
// g++ ./m/currentToBest2.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToBest2BG.exe

// g++ ./m/currentToRand1.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToRand1BG.exe
// g++ ./m/currentToRand2.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToRand2BG.exe
// g++ ./m/currentToRand1.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToRand2BG.exe
// g++ ./m/currentToRand2.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToRand2BG.exe

// g++ ./m/rand1.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand1BG.exe
// g++ ./m/rand2.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand2BG.exe
// g++ ./m/rand3.cpp random.cpp ./individualTesting.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand3BG.exe
// g++ ./m/rand1.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand1EG.exe
// g++ ./m/rand2.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand2EG.exe
// g++ ./m/rand3.cpp random.cpp ./individualTesting.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand3EG.exe