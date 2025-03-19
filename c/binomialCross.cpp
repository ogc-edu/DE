#include "binomialCross.h"
#include <iostream>
#include <random>
#include "../random.h"

using namespace std;

void binomialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np)
{
  for (int i = 0; i < np; i++)
  {
    // Ensure at least one dimension comes from mutant vector
    int d_rand = static_cast<int>(generateRandomFloat() * 30);

    for (int j = 0; j < 30; j++)
    {
      if (generateRandomFloat() <= crRate || j == d_rand)
      {
        trialVector[i][j] = mutantVector[i][j];
      }
      else
      {
        trialVector[i][j] = targetVector[i][j];
      }
    }
  }
}

// void binomialCrossover(double targetVector[][30], double mutantVector[][30], double trialVector[][30], float crRate, int np, float cr[][30])
// {
//   // generate random crossover value
//   // int totalCross = 0;
//   for (int i = 0; i < np; i++)
//   {
//     for (int j = 0; j < 30; j++)
//     {
//       cr[i][j] = generateRandomFloat();
//     }
//   }
//   int d_rand; // random dimension value for crossover

//   for (int i = 0; i < np; i++)
//   {
//     // totalCross = 0;
//     d_rand = static_cast<int>(generateRandomDouble(0, 29));
//     for (int j = 0; j < 30; j++)
//     {
//       if (cr[i][j] <= crRate || j == d_rand)
//       { // take mutant vector dimension if CR rate >= generated rand[0,1]
//         trialVector[i][j] = mutantVector[i][j];
//         // totalCross++;
//       }
//       else
//       {
//         trialVector[i][j] = targetVector[i][j];
//       }
//     }
//     // cout << "Total cross " << totalCross << endl;
//   }
// }