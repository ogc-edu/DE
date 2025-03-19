#include <iostream>
#include "../init.h"
#include "../random.h"
#include "../c/binomialCross.h"
#include "../fitnessEvaluation.h"
#include "../s/greedySelection.h"
#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include "../m/unique.h"

using namespace std;

void rand3Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench)
{
  const int randomSize = 7;
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
      mutantVector[i][j] = positionVector[target[0]][j] + f * (positionVector[target[1]][j] - positionVector[target[2]][j]) + f * (positionVector[target[3]][j] - positionVector[target[4]][j]) + f * (positionVector[target[5]][j] - positionVector[target[6]][j]);
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

// g++ ./m/rand3.cpp random.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/rand3.exe