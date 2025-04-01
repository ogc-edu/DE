#include <iostream>
#include "../random.h"
#include "../m/unique.h"
#include <cmath>

using namespace std;
// const int gen = 2000, dimension = 30, pSize = 40;
// float CR = 0.00, f = 0.0;

void Best3Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  const int randomSize = 6;
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
      mutantVector[i][j] = positionVector[bestPos][j] + f * (positionVector[target[0]][j] - positionVector[target[1]][j] + positionVector[target[2]][j] - positionVector[target[3]][j] + positionVector[target[4]][j] - positionVector[target[5]][j]);
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