#include <iostream>
#include "../fitnessEvaluation.h"
#include "../random.h"
#include <vector>
#include <algorithm>
#include "./STS40.h"

using namespace std;

struct vectorFitness // just to keep vectors with assoc fitness value
{
  double *vector;
  double fitnessValue;
};

int remainingVectors;
bool hasRemainder;

void STSFilter(double TAS[2][30], double TRS[2][30], int bench, double bestVectors[2][30], bool hasRemainder, int vectorCount)
{
  int unionSize = hasRemainder ? vectorCount * 2 : 4; // remainder case: vectorCount*2, normal: 4
  vectorFitness unionSet[4];                          // max size is still 4

  // union set contains TAS and TRS vectors
  for (int i = 0; i < vectorCount; i++)
  {
    unionSet[i].vector = TAS[i];
    unionSet[i].fitnessValue = fitness(TAS[i], bench);
    unionSet[i + vectorCount].vector = TRS[i];
    unionSet[i + vectorCount].fitnessValue = fitness(TRS[i], bench);
  }

  // sort union set in ascending order using fitnessValue as key
  sort(unionSet, unionSet + unionSize, [](const vectorFitness &a, const vectorFitness &b)
       { return a.fitnessValue < b.fitnessValue; });

  int selectCount = hasRemainder ? vectorCount : 2; // select vectorCount in remainder case, 2 otherwise
  for (int i = 0; i < selectCount; i++)
  {
    for (int j = 0; j < 30; j++)
    {
      bestVectors[i][j] = unionSet[i].vector[j];
    }
  }
}

void sts(double positionVector[][30], double trialVector[][30], int bench)
{
  int subsetNumber = 0;
  int np = 40;
  const int ss = 2;           // subset number
  double bestVectors[ss][30]; // to keep best vectors dimensions
  if (np % ss == 0)           // determine number of subset
  {
    subsetNumber = np / ss;
    hasRemainder = false;
  }
  else
  {
    subsetNumber = (np / ss) + 1;
    hasRemainder = true;
  }
  double TAS[ss][30], TRS[ss][30]; // assigned per subset number, get replaced for each new subset
  int pos = generateRandomFloat() * np;
  for (int i = 0; i < subsetNumber; i++) // ensure loop is iterated n times, where n = number of subset
  /*
  in each subset do 3 things
  1. Copy dimension from position and trial vector
  2. Take the best ss vectors from (TAS) U (TRS) set
  3. Paste ss vectors into position vector
  */
  {
    if (hasRemainder && i == subsetNumber - 1)
    { // if has remainder, last subset will have less than ss vectors
      remainingVectors = np % ss;
      for (int j = 0; j < remainingVectors; j++)
      {
        for (int k = 0; k < 30; k++)
        {
          TAS[j][k] = positionVector[pos][k];
          TRS[j][k] = trialVector[pos][k];
        }
        pos++;
        pos %= 40; // ensure within boundary of np
      }
    }
    else // no remainder
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
    }
    // compare fitness value, filter the best ss vectors
    int cur; // use to track pos
    if (hasRemainder && i == subsetNumber - 1)
    {
      STSFilter(TAS, TRS, bench, bestVectors, true, remainingVectors); // pass remainder info
      for (int j = 0; j < remainingVectors; j++)
      {
        for (int k = 0; k < 30; k++)
        {
          cur = (pos - j + np) % np; // ensure boundary e.g: pos = 0
          positionVector[cur][k] = bestVectors[j][k];
        }
      }
    }
    else
    {
      STSFilter(TAS, TRS, bench, bestVectors, false, ss); // normal case
      for (int j = 0; j < ss; j++)
      {
        for (int k = 0; k < 30; k++)
        {
          cur = (pos - j + np) % np; // ensure boundary e.g: pos = 0
          positionVector[cur][k] = bestVectors[j][k];
        }
      }
    }
  }
};
