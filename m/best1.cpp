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

void Best1Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  // Xi = Xbest + f(Xr1 - Xr2)
  int randTarget[2];
  bool unique; // all random target are unique

  for (int i = 0; i < np; i++)
  {
    do
    {
      for (int k = 0; k < 2; k++)
      {
        randTarget[k] = static_cast<int>(generateRandomFloat() * np); // random value [0, np)
      }
      unique = areAllUnique(randTarget, 2);
      if (randTarget[0] == bestPos || randTarget[1] == bestPos) // rand cannot be bestPos
      {
        unique = false;
      }
    } while (unique == false); // repeat if same r1 r2

    // begin mutation
    for (int j = 0; j < 30; j++)
    {
      mutantVector[i][j] = positionVector[bestPos][j] + (f * (positionVector[randTarget[1]][j] - positionVector[randTarget[0]][j]));
      if (mutantVector[i][j] > rangeMax)
      { // boundary assertion
        mutantVector[i][j] = rangeMax;
      }
      if (mutantVector[i][j] < rangeMin)
      { // boundary assertion
        mutantVector[i][j] = rangeMin;
      }
    }
  }
}

// g++ ./m/best1.cpp random.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best1BG.exe