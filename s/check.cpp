#include <iostream>
#include "../init.h"
#include "../random.h"
#include "../fitnessEvaluation.h"
#include "../s/STS40.h"

#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <chrono>

int main()
{
  double positionVector[10][30];
  double trialVector[10][30];
  double rangeMin = -65.536, rangeMax = 65.536;
  int bestPos;
  init(positionVector, rangeMin, rangeMax, 10, &bestPos, 2); // initialize position vectors once

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 30; j++) // Fixed: j < 30; j++
    {
      trialVector[i][j] = 10000;
    }
  }

  for (int i = 0; i < 30; i++)
  {
    trialVector[9][i] = 0;
  }
  for (int j = 0; j < 10; j++)
  {
    std::cout << "target vector " << j + 1 << ": ";
    for (int i = 0; i < 30; i++)
    {
      std::cout << positionVector[j][i] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "trial" << std::endl;
  for (int j = 0; j < 10; j++)
  {
    std::cout << "trial vector " << j + 1 << ": ";
    for (int i = 0; i < 30; i++)
    {
      std::cout << trialVector[j][i] << " ";
    }
    std::cout << std::endl;
  }

  sts(positionVector, trialVector, 2);
  return 0;
}

// g++ ../random.cpp ../init.cpp ../fitnessEvaluation.cpp ./STS40.cpp ./check.cpp -o check.exe
