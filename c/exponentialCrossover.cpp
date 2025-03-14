#include "exponentialCrossover.h"
#include <iostream>
#include <random>
#include "../random.h"

void exponentialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
{
  bool crossoverMask[30];
  for (int k = 0; k < np; k++) // generate trial vector for each target vector
  {
    for (int i = 0; i < 30; i++)
    {
      crossoverMask[i] = false;
    }
    int startDimension = generateRandomFloat() * 30;
    float generatedCR = generateRandomFloat();
    bool success; // exponential experiment
    int loopCount = 0;
    if (generatedCR <= crRate)
    {
      success = true; // continue generate cr Rate for next vector, until the first fail
    }
    while (success)
    {
      if (startDimension == 29)
      {
        startDimension = 0;
      }
      crossoverMask[startDimension] = true; // crossover happen at current position
      generatedCR = generateRandomFloat();
      success = (generatedCR <= crRate);
      startDimension++;
      loopCount++;
      if (loopCount > 29)
        break;
    }
    for (int i = 0; i < 30; i++)
    {
      if (crossoverMask[i]) // if crossover true
      {
        trialVector[k][i] = mutantVector[k][i];
      }
      else
      {
        trialVector[k][i] = targetVector[k][i];
      }
    }
  }
}