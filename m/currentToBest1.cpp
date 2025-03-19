#include <iostream>
#include "../random.h"
#include "../m/unique.h"

using namespace std;

void currentToBest_1_Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  // X = Xi + f(Xbest - Xi) + f(X1 - X2);
  const int randomSize = 2;
  int target[randomSize];
  bool unique;

  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < randomSize; k++)
      {
        target[k] = static_cast<int>(generateRandomFloat() * np);
      }
      unique = areAllUnique(target, randomSize);
    } while (unique == false);
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[i][j] + f * (positionVector[bestPos][j] - positionVector[i][j]) + f * (positionVector[target[0]][j] - positionVector[target[1]][j]);
      if (mutantVector[i][j] > rangeMax)
      {
        mutantVector[i][j] = rangeMax;
      }
      if (mutantVector[i][j] < rangeMin)
      {
        mutantVector[i][j] = rangeMin;
      }
    }
  }
}

// g++ ./m/currentToBest1.cpp random.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToBest1.exe