#include "exponentialCross.h"
#include <iostream>
#include <random>
#include "../random.h"

// correct version
void exponentialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
{
  for (int k = 0; k < np; k++) // generate trial vector for each target vector
  {
    bool crossoverMask[30] = {false}; // all dimension to be false at initialization

    // Randomly select starting dimension
    int startDimension = static_cast<int>(generateRandomFloat() * 30);
    int crossoverCount = 1; // number of crossed dimension (include the first dimension so starts from 1)
    crossoverMask[startDimension] = true;

    // Perform exponential crossover
    int currentDimension = (startDimension + 1) % 30;

    while (crossoverCount < 30)
    {
      if (generateRandomFloat() > crRate)
      { // binomial experiment failed
        break;
      }
      crossoverMask[currentDimension] = true;
      currentDimension = (currentDimension + 1) % 30;
      crossoverCount++;
    }

    // Construct trial vector
    for (int i = 0; i < 30; i++)
    {
      trialVector[k][i] = crossoverMask[i] ? mutantVector[k][i] : targetVector[k][i]; // if crossover == true, take mutant vector, target vector otherwise
    }
  }
}
