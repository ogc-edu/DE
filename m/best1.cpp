#include <iostream>
#include "../random.h"
#include "../m/unique.h"

using namespace std;

void Best1Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  // Xi = Xbest + f(Xr1 - Xr2)
  const int randomSize = 2;
  int random[randomSize];
  bool unique; // all random target are unique

  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < randomSize; k++)
      {
        random[k] = static_cast<int>(generateRandomFloat() * np); // make sure all difference vectors are unique
      }
      unique = areAllUnique(random, 2);
      for (int k = 0; k < randomSize; k++)
      {
        if (random[k] == bestPos) // make sure best vector and difference vector are diff
          unique = false;
      }
    } while (unique == false); // repeat if same r1 r2

    // begin mutation
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[bestPos][j] + (f * (positionVector[random[0]][j] - positionVector[random[1]][j]));
      if (mutantVector[i][j] > rangeMax)
      { // boundary assertion
        mutantVector[i][j] = rangeMax;
      }
      if (mutantVector[i][j] < rangeMin)
      {
        mutantVector[i][j] = rangeMin;
      }
    }
  }
}