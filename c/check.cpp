#include <iostream>
#include "../init.h"
#include "../random.h"
#include "../fitnessEvaluation.h"
#include "../m/best3.h"
#include "../c/onePointCross.h"
#include "../c/twoPointCross.h"
#include "../m/unique.h"
#include "../s/STS.cpp"

#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <string>
#include <sstream>

int main()
{
  const int np = 10;
  const int dimensions = 30;
  double positionVector[np][30];
  double trialVector[np][30];
  double mutantVector[np][30];
  double rangeMin = -65.536, rangeMax = 65.536;
  int bestPos;
  int bench = 2;
  init(positionVector, rangeMin, rangeMax, np, &bestPos, 2); // initialize position vectors once

  Best3Mutation(positionVector, mutantVector, np, 0.80, rangeMin, rangeMax, 2, bestPos);
  twoPointCross(positionVector, mutantVector, trialVector, 0.30, np);

  for (int i = 0; i < np; i++)
  {
    std::cout << "Vector " << (i + 1) << ":" << std::endl;
    for (int j = 0; j < dimensions; j++)
    {
      std::cout << "Dim " << (j + 1) << ": "
                << "Position=" << std::fixed << std::setprecision(3) << positionVector[i][j]
                << " Mutant=" << mutantVector[i][j]
                << " Trial=" << trialVector[i][j] << std::endl;
    }
    std::cout << std::endl;
  }

  sts(positionVector, trialVector, 2, np);

  std::cout << "After selection:" << std::endl;
  for (int j = 0; j < np; j++)
  {
    std::cout << "Vector " << (j + 1) << ": " << std::fixed << std::setprecision(6) << fitness(positionVector[j], bench) << std::endl;
  }

  return 0;
}

// g++ ../random.cpp ../init.cpp ../fitnessEvaluation.cpp ./check.cpp ../m/best3.cpp ./onePointCross.cpp ./twoPointCross.cpp ../m/unique.cpp -o check.exe
