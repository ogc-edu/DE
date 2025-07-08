#include <iostream>
#include "fitnessEvaluation.h"
#include "random.h"
#include <vector>
#include <algorithm>

using namespace std;

struct vectorFitness // just to keep vectors with assoc fitness value
{
  double *vector;
  double fitnessValue;
};

void sts(double positionVector[][30], double trialVector[][30], int bench)
{
  int subsetNumber = 0;
  int np = 40;
  const int ss = 2;           // subset number
  double bestVectors[ss][30]; // to keep best vectors dimensions
  if (np % ss == 0)           // determine number of subset
  {
    subsetNumber = np / ss;
  }
  else
  {
    subsetNumber = (np / ss) + 1;
  }
  double TAS[ss][30], TRS[ss][30];
  int pos = generateRandomFloat() * np;
  for (int i = 0; i < subsetNumber; i++) // ensure loop is iterated n times, where n = number of subset
  /*
  in each subset do 3 things
  1. Copy dimension from position and trial vector
  2. Take the best ss vectors from (TAS) U (TRS) set
  3. Paste ss vectors into position vector
  */
  {
    for (int j = 0; j < ss; j++) // copy dimension of target and trial vector to TAS and TRS
    {
      for (int k = 0; k < 30; k++)
      {
        TAS[j][k] = positionVector[pos][k];
        TRS[j][k] = trialVector[pos][k];
      }
      pos++;
      pos %= 40; // ensure within boundary of np
    }
    // compare fitness value, filter the best ss vectors
    STSFilter(TAS, TRS, bench, bestVectors); // perform at the end of each subset loop
    int cur;                                 // use to track pos
    for (int j = 0; j < ss; j++)
    {
      for (int k = 0; k < 30; k++)
      {
        cur = (pos - j + np) % np; // ensure boundary
        positionVector[pos - j][k] = bestVectors[j][k];
      }
    }
  }
};

void STSFilter(double TAS[2][30], double TRS[2][30], int bench, double bestVectors[2][30])
{
  vectorFitness unionSet[4];

  // union set contains TAS and TRS vectors
  unionSet[0].vector = TAS[0];
  unionSet[0].fitnessValue = fitness(TAS[0], bench);
  unionSet[1].vector = TAS[1];
  unionSet[1].fitnessValue = fitness(TAS[1], bench);
  unionSet[2].vector = TRS[0];
  unionSet[2].fitnessValue = fitness(TRS[0], bench);
  unionSet[3].vector = TRS[1];
  unionSet[3].fitnessValue = fitness(TRS[1], bench);

  // sort union set in ascending order using fitnessValue as key
  sort(unionSet, unionSet + 4, [](const vectorFitness &a, const vectorFitness &b)
       { return a.fitnessValue < b.fitnessValue; });

  for (int i = 0; i < 2; i++) // only take the first two lowest/best
  {
    for (int j = 0; j < 30; j++)
    {
      bestVectors[i][j] = unionSet[i].vector[j];
    }
  }
}