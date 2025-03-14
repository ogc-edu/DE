#include <iostream>
#include "../init.h"
#include "../random.h"
#include "../c/binomialCross.h"
#include "../fitnessEvaluation.h"
#include "../s/greedySelection.h"
#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <iomanip>

using namespace std;

bool areAllUnique(int arr[], int size)
{
  unordered_set<int> seen;
  for (int i = 0; i < size; ++i)
  {
    if (seen.find(arr[i]) != seen.end())
    {
      return false; // Duplicate found
    }
    seen.insert(arr[i]);
  }
  return true; // All elements are unique
}

void currentToRand1Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench)
{
  const int randomSize = 3;
  int target[randomSize];
  bool unique;
  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < randomSize; k++)
      {
        target[k] = static_cast<int>(generateRandomFloat() * np);
      }
      unique = areAllUnique(target, randomSize);
    } while (unique == false);
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[i][j] + f * (positionVector[target[0]][j] - positionVector[i][j]) + f * (positionVector[target[1]][j] - positionVector[target[2]][j]);
      if (mutantVector[i][j] > rangeMax)
      {
        mutantVector[i][j] = rangeMax;
      }
      if (mutantVector[i][j] < rangeMin)
      {
        mutantVector[i][j] = rangeMin;
      }
    }
  }
}

// g++ ./m/currentToRand1.cpp random.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/currentToRand1.exe