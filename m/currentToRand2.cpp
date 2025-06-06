#include <iostream>
#include "../random.h"
#include "../m/unique.h"

using namespace std;

void currentToRand2Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench)
{
  const int randomSize = 5;
  int random[randomSize];
  bool unique;
  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < randomSize; k++)
      {
        random[k] = static_cast<int>(generateRandomFloat() * np);
      }
      unique = areAllUnique(random, randomSize);
      if (random[0] == i || random[1] == i || random[2] == i || random[3] == i || random[4] == i)
        unique = false;
    } while (unique == false);
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[i][j] + f * (positionVector[random[0]][j] - positionVector[i][j]) + f * (positionVector[random[1]][j] - positionVector[random[2]][j]) + f * (positionVector[random[3]][j] - positionVector[random[4]][j]);
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

// g++ ./m/currentToRand2.cpp random.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToRand2.exe