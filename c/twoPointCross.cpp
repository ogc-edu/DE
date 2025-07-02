#include <iostream>
#include "random.h"
#define dimension 30

using namespace std;

void twoPointCross(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float Cr, int np)
{
  for (int i = 0; i < np; i++)
  {
    float rand = generateRandomFloat();
    if (rand <= Cr)
    {
      float pos1, pos2;
      do
      {
        pos1 = generateRandomFloat() * dimension;
        pos2 = generateRandomFloat() * dimension;
      } while ((pos1 != pos2) && (abs(pos1 - pos2) < dimension)); // ensure unique pos and duplicated parent
      for (int j = 0; j < pos1; j++)
      {
        trialVector[i][j] = targetVector[i][j];
      }
      for (int j = pos1; j <= pos2; j++)
      {
        trialVector[i][j] = mutantVector[i][j];
      }
      if (pos2 < dimension - 1)
      { // if starting point is not last dimension(29)
        for (int j = pos2 + 1; j < dimension; j++)
        {
          trialVector[i][j] = targetVector[i][j];
        }
      }
    }
  }
}