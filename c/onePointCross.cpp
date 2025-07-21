#include <iostream>
#include "../random.h"

using namespace std;

void onePointCross(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float Cr, int np)
{
  for (int i = 0; i < np; i++)
  {
    float rand = generateRandomFloat(); // generate random float for each target vector
    if (rand <= Cr)
    {
      // std::cout << "Crossover happened for vector " << i + 1;
      int pos = generateRandomFloat() * 30;
      // std::cout << "\tPosition: " << pos + 1 << std::endl;
      if (pos == 0)
        pos = 1;                    // ensure trial vector is diff from parents
      for (int j = 0; j < pos; j++) // before pos taken from target vector
      {
        trialVector[i][j] = targetVector[i][j];
      }
      for (int j = pos; j < 30; j++) // start from pos taken from mutant vector
      {
        trialVector[i][j] = mutantVector[i][j];
      }
    }
    else // trial vector copies from target vector
    {
      for (int j = 0; j < 30; j++)
      {
        trialVector[i][j] = targetVector[i][j];
      }
    }
  }
}