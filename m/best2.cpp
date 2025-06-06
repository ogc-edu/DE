#include <iostream>
#include "../random.h"
#include "../m/unique.h"

using namespace std;

void Best2Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  // Xi = Xbest + f(Xr1 - Xr2) + f(Xr3 - Xr4)
  const int randomSize = 4;
  int random[randomSize];
  bool unique;

  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < randomSize; k++)
      {
        random[k] = static_cast<int>(generateRandomFloat() * np); // make sure 4 unique diff vector
      }
      unique = areAllUnique(random, 4);
      for (int k = 0; k < 4; k++)
      {
        if (random[k] == bestPos) // make sure all diff vector diff with best vector
          unique = false;
      }
    } while (unique == false);
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[bestPos][j] + f * (positionVector[random[0]][j] - positionVector[random[1]][j]) + f * (positionVector[random[2]][j] - positionVector[random[3]][j]);
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