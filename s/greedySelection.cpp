#include <iostream>
#include "../fitnessEvaluation.h"
#include <math.h>
#include <vector>

using namespace std;
void greedySelection(double positionVector[][30], double trialVector[][30], int bench, int np, double bestSolution[30], double *pastBestFV, int *genBestPos)
{
  /*
  1) Replace position vector with trial vector if trial is better solution
  2) Identify the best solution in one generation
  3) Compare with past best solution, if better then replace past best solution with current best solution
  */
  vector<double> positionFV(np, 0), trialFV(np, 0); // changed from positionFV[40] to vector<double> positionFV(np)
  double genLowestFV = pow(30, 30);
  int bestPos;

  for (int i = 0; i < np; i++) // selection occurs
  {
    positionFV[i] = fitness(positionVector[i], bench);
    trialFV[i] = fitness(trialVector[i], bench);
    if (trialFV[i] < positionFV[i]) // if trial vector is better solution than position vector
    {
      for (int j = 0; j < 30; j++)
      {
        positionVector[i][j] = trialVector[i][j];
      }
      positionFV[i] = trialFV[i]; // new position vector FV = better trial vector FV, redundant
    }
  }

  for (int i = 0; i < np; i++) // find the lowest FV in generation to compare with best solution
  {
    if (positionFV[i] < genLowestFV)
    {
      genLowestFV = positionFV[i];
      bestPos = i;
    }
  }

  if (genLowestFV < *pastBestFV) // if the lowest gen is better than past best
  {
    // cout << "Lowest better, past: " << *pastBestFV << " newest: " << genLowestFV << "\t" << "Old position: " << *genBestPos << " New Pos: " << bestPos << endl;
    *pastBestFV = genLowestFV;
    *genBestPos = bestPos;

    for (int i = 0; i < 30; i++)
    {
      bestSolution[i] = positionVector[bestPos][i];
    }
  }
}