#include <iostream>
#include "../fitnessEvaluation.h"
#include "../random.h"
#include <vector>
#include <algorithm>
#include "./STS.h"

using namespace std;

struct vectorFitness // just to keep vectors with assoc fitness value
{
  double *vector;
  double fitnessValue;
};

// Function to determine subset size for specific population sizes
int calculateSubsetSize(int np)
{
  if (np == 40)
    return 2;
  else if (np == 100)
    return 6;
  else if (np == 150)
    return 12;
  else if (np == 10)
    return 2;
  else
  {
    cout << "Wrong np inserted, please check" << endl;
    exit(1);
  }
}

void STSFilter(vector<vector<double>> &TAS, vector<vector<double>> &TRS, int bench, vector<vector<double>> &bestVectors, int vectorCount)
{
  int unionSize = vectorCount * 2; // TAS + TRS vectors
  vector<vectorFitness> unionSet(unionSize);

  // union set contains TAS and TRS vectors
  for (int i = 0; i < vectorCount; i++)
  {
    unionSet[i].vector = TAS[i].data();
    unionSet[i].fitnessValue = fitness(TAS[i].data(), bench);

    unionSet[i + vectorCount].vector = TRS[i].data();
    unionSet[i + vectorCount].fitnessValue = fitness(TRS[i].data(), bench);
  }

  // sort union set in ascending order using fitnessValue as key
  sort(unionSet.begin(), unionSet.end(), [](const vectorFitness &a, const vectorFitness &b)
       { return a.fitnessValue < b.fitnessValue; });

  // select the best vectorCount vectors
  bestVectors.resize(vectorCount); // resize to fit in last remaining vector size
  for (int i = 0; i < vectorCount; i++)
  {
    bestVectors[i].resize(30); // make sure size is always 30
    for (int j = 0; j < 30; j++)
    {
      bestVectors[i][j] = unionSet[i].vector[j];
    }
  }
}

void sts(double positionVector[][30], double trialVector[][30], int bench, int np, double bestSolution[30], double *pastBestFV, int *genBestPos)
{
  int remainingVectors;
  bool hasRemainder;
  int subsetNumber = 0;
  const int ss = calculateSubsetSize(np); // subset size based on specific np values

  if (np % ss == 0) // determine number of subsets
  {
    subsetNumber = np / ss;
    hasRemainder = false;
  }
  else
  {
    subsetNumber = (np / ss) + 1;
    hasRemainder = true;
  }

  int pos = generateRandomFloat() * np;
  // cout << "Starting position: " << pos + 1 << endl;

  for (int i = 0; i < subsetNumber; i++) // ensure loop is iterated n times, where n = number of subset
  /*
  in each subset do 3 things
  1. Copy dimension from position and trial vector
  2. Take the best vectors from (TAS) U (TRS) set
  3. Paste vectors into position vector
  */
  {
    int currentVectorCount;

    // Determine how many vectors to process in this subset
    if (hasRemainder && i == subsetNumber - 1)
    {
      currentVectorCount = np % ss; // remainder vectors in last subset
    }
    else
    {
      currentVectorCount = ss; // normal subset size
    }

    // Create dynamic arrays for this subset
    vector<vector<double>> TAS(currentVectorCount, vector<double>(30));
    vector<vector<double>> TRS(currentVectorCount, vector<double>(30));
    vector<vector<double>> bestVectors;
    vector<int> subsetPositions(currentVectorCount); // Track original positions

    int basePos = pos; // Save the starting position for this subset

    // Copy vectors from position and trial arrays and track positions
    for (int j = 0; j < currentVectorCount; j++)
    {
      subsetPositions[j] = pos; // Store the actual position
      for (int k = 0; k < 30; k++)
      {
        TAS[j][k] = positionVector[pos][k];
        TRS[j][k] = trialVector[pos][k];
      }
      pos = (pos + 1) % np; // Move to next position with wraparound
    }

    // Sort positions using sort algorithm
    vector<pair<int, int>> positionMapping; // pair<originalIndex, position>
    for (int j = 0; j < currentVectorCount; j++)
    {
      positionMapping.push_back({j, subsetPositions[j]});
    }
    sort(positionMapping.begin(), positionMapping.end(),
         [](const pair<int, int> &a, const pair<int, int> &b)
         {
           return a.second < b.second; // Sort by position
         });

    // filter to get the best vectors
    STSFilter(TAS, TRS, bench, bestVectors, currentVectorCount);

    // Copy best vectors back to position vector RANDOMLY
    // Extract positions and shuffle them for random assignment
    vector<int> targetPositions(currentVectorCount);
    for (int j = 0; j < currentVectorCount; j++)
    {
      targetPositions[j] = positionMapping[j].second; // Extract all positions
    }

    // Shuffle positions randomly using Fisher-Yates shuffle
    for (int j = currentVectorCount - 1; j > 0; j--)
    {
      int randomIndex = static_cast<int>(generateRandomFloat() * (j + 1));
      swap(targetPositions[j], targetPositions[randomIndex]);
    }

    // Assign best vectors to randomly shuffled positions
    // Best vector goes to random position, 2nd best to different random position, etc.
    for (int j = 0; j < currentVectorCount; j++)
    {
      int targetPos = targetPositions[j]; // Get j-th shuffled position
      for (int k = 0; k < 30; k++)
      {
        positionVector[targetPos][k] = bestVectors[j][k]; // j-th best vector to random position
      }
    }

    double genLowestFV = pow(30, 30);
    vector<double> positionFV(np, 0);
    int bestPos;
    for (int i = 0; i < np; i++) // find the lowest FV in generation to compare with best solution
    {
      positionFV[i] = fitness(positionVector[i], bench);
    }
    for (int i = 0; i < np; i++) // find the lowest FV in generation to compare with best solution
    {
      if (positionFV[i] < genLowestFV)
      {
        genLowestFV = positionFV[i];
        bestPos = i;
      }
    }
    if (positionFV[bestPos] < *pastBestFV)
    {
      *pastBestFV = positionFV[bestPos];
      *genBestPos = bestPos;
      for (int i = 0; i < 30; i++)
      {
        bestSolution[i] = positionVector[bestPos][i];
      }
    }
    // cout << "Subset " << i + 1 << " finished, processed " << currentVectorCount << " vectors" << endl;
  }
}
