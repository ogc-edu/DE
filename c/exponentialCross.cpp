#include "exponentialCross.h"
#include <iostream>
#include <random>
#include "../random.h"

void exponentialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
{
  for (int k = 0; k < np; k++) // generate trial vector for each target vector
  {
    bool crossoverMask[30] = {false}; // all dimension to be false at initialization

    // Randomly select starting dimension
    int startDimension = static_cast<int>(generateRandomFloat() * 30);

    // Perform exponential crossover
    int currentDimension = startDimension;
    int crossoverCount = 1;

    while (crossoverCount < 30)
    {
      crossoverMask[currentDimension] = true; // Mark start dimension to true for crossover
      if (generateRandomFloat() > crRate)
      { // binomial experiment
        break;
      }
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

// first not included
// void exponentialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
// {
//   for (int k = 0; k < np; k++) // generate trial vector for each target vector
//   {
//     bool crossoverMask[30] = {false}; // all dimension to be false at initialization

//     // Randomly select starting dimension
//     int startDimension = static_cast<int>(generateRandomFloat() * 30);

//     // Perform exponential crossover
//     int currentDimension = startDimension;
//     int crossoverCount = 0;

//     while (crossoverCount < 30)
//     {
//       if (generateRandomFloat() > crRate)
//       { // binomial experiment
//         break;
//       }
//       // if (currentDimension == 29)
//       // {
//       //   currentDimension = 0;
//       // }
//       crossoverMask[currentDimension] = true;
//       currentDimension++;
//       currentDimension %= 30;
//       crossoverCount++;
//     }

//     // Construct trial vector
//     for (int i = 0; i < 30; i++)
//     {
//       trialVector[k][i] = crossoverMask[i] ? mutantVector[k][i] : targetVector[k][i]; // if crossover == true, take mutant vector, target vector otherwise
//     }
//   }
// }

// void exponentialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
// {
//   bool crossoverMask[30];
//   for (int k = 0; k < np; k++) // generate trial vector for each target vector
//   {
//     for (int i = 0; i < 30; i++)
//     {
//       crossoverMask[i] = false;
//     }
//     int startDimension = generateRandomFloat() * 30;
//     float generatedCR = generateRandomFloat();
//     bool success; // exponential experiment
//     int loopCount = 0;
//     if (generatedCR <= crRate)
//     {
//       success = true; // continue generate cr Rate for next vector, until the first fail
//     }
//     while (success)
//     {
//       if (startDimension == 29)
//       {
//         startDimension = 0;
//       }
//       crossoverMask[startDimension] = true; // crossover happen at current position
//       generatedCR = generateRandomFloat();
//       success = (generatedCR <= crRate); // success binomial experiment
//       startDimension++;
//       loopCount++;
//       if (loopCount > 29)
//         break;
//     }
//     if (crossoverMask[29] == true) // crossoverMask[29] is never true
//       exit(1);
//     for (int i = 0; i < 30; i++)
//     {
//       if (crossoverMask[i]) // if crossover true
//       {
//         trialVector[k][i] = mutantVector[k][i];
//       }
//       else
//       {
//         trialVector[k][i] = targetVector[k][i];
//       }
//     }
//   }
// }
