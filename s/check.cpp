#include <iostream>
#include "../init.h"
#include "../random.h"
#include "../fitnessEvaluation.h"
#include "../m/best3.h"
#include "../c/binomialCross.h"
#include "../m/unique.h"
#include "../s/STS.cpp"

#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <chrono>

int main()
{
  const int np = 150;
  double positionVector[np][30];
  double trialVector[np][30];
  double mutantVector[np][30];
  double rangeMin = -65.536, rangeMax = 65.536;
  int bestPos;
  int bench = 2;
  init(positionVector, rangeMin, rangeMax, np, &bestPos, 2); // initialize position vectors once

  // for (int i = 0; i < 10; i++)
  // {
  //   for (int j = 0; j < 30; j++) // Fixed: j < 30; j++
  //   {
  //     trialVector[i][j] = 10000;
  //   }
  // }

  // for (int i = 0; i < 30; i++)
  // {
  //   trialVector[9][i] = 0;
  // }

  // for (int j = 0; j < 10; j++)
  // {
  //   std::cout << "trial vector " << j + 1 << ": ";
  //   for (int i = 0; i < 30; i++)
  //   {
  //     std::cout << trialVector[j][i] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  Best3Mutation(positionVector, mutantVector, np, 0.80, rangeMin, rangeMax, 2, bestPos);
  binomialCrossover(positionVector, mutantVector, trialVector, 0.30, np);
  for (int j = 0; j < np; j++)
  {
    std::cout << "target vector " << j + 1 << ": ";
    std::cout << fitness(positionVector[j], bench);
    std::cout << "\ttrial vector " << j + 1 << ": ";
    std::cout << fitness(trialVector[j], bench) << std::endl;
  }
  sts(positionVector, trialVector, 2, np);

  std::cout << "After selection: " << std::endl;
  for (int j = 0; j < np; j++)
  {
    std::cout << "\ntarget vector " << j + 1 << ": ";
    std::cout << fitness(positionVector[j], bench) << std::endl;
  }

  return 0;
}

// g++ ../random.cpp ../init.cpp ../fitnessEvaluation.cpp ./STS40.cpp ./check.cpp ../m/best3.cpp ../c/binomialCross.cpp ../m/unique.cpp -o check.exe
// g++ ../random.cpp ../init.cpp ../fitnessEvaluation.cpp ./check.cpp ../m/best3.cpp ../c/binomialCross.cpp ../m/unique.cpp -o check.exe
