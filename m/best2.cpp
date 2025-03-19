#include <iostream>
#include "../random.h"
#include "../fitnessEvaluation.h"
#include <math.h>
#include <unordered_set>
#include "../m/unique.h"

using namespace std;

void Best2Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  int target[4];
  bool unique;

  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < 4; k++)
      {
        target[k] = static_cast<int>(generateRandomFloat() * np);
      }
      unique = areAllUnique(target, 4);
    } while (unique == false);
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[bestPos][j] + f * (positionVector[target[1]][j] - positionVector[target[0]][j]) + f * (positionVector[target[3]][j] - positionVector[target[2]][j]);
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