#include "binomialCross.h"
#include <iostream>
#include <random>
#include "../random.h"

using namespace std;

void binomialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
{
  /*
  1. Create trial vector from mutant vector and target vector
  2. Crossover happens where trial vector inherits a dimension from mutant vector, target vector otherwise
  3. At least one dimension will be inherited onto trial vector to create diff child
  */
  for (int i = 0; i < np; i++)
  {
    // Ensure at least one dimension comes from mutant vector
    int d_rand = static_cast<int>(generateRandomFloat() * 30);

    for (int j = 0; j < 30; j++)
    {
      if (generateRandomFloat() <= crRate || j == d_rand) // crossover happens for random generate float [0, 1.0) lower than crRate rate || random dimension matched
      {
        trialVector[i][j] = mutantVector[i][j];
      }
      else // crossover does not happen
      {
        trialVector[i][j] = targetVector[i][j];
      }
    }
  }
}