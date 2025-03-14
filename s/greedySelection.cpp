#include <iostream>
#include "../fitnessEvaluation.h"
#include <math.h>
#include <iomanip>

using namespace std;
void greedySelection(double positionVector[][30], double trialVector[][30], int bench, int np, double bestSolution[30], double *pastBestFV, int *genBestPos)
{
  cout << fixed << setprecision(40);
  double positionFV[40], trialFV[40]; // store fv  of position vector and trial vector
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

  for (int i = 0; i < np; i++)
  { // find the lowest FV in one gen
    if (positionFV[i] < genLowestFV)
    {
      genLowestFV = positionFV[i];
      bestPos = i;
    }
  }

  if (genLowestFV < *pastBestFV) // if the lowest gen is better than past best
  {
    cout << "Lowest better, past: " << *pastBestFV << " newest: " << genLowestFV << "\t" << "Old position: " << *genBestPos << " New Pos: " << bestPos << endl;
    *pastBestFV = genLowestFV;
    *genBestPos = bestPos;

    for (int i = 0; i < 30; i++)
    {
      bestSolution[i] = positionVector[bestPos][i];
    }
  }
}