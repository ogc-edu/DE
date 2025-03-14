#include <iostream>
#include "../init.h"
#include "../random.h"
#include "../c/binomialCross.h"
#include "../fitnessEvaluation.h"
#include "../s/greedySelection.h"
#include "../c/exponentialCrossover.h"
#include <vector>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <iomanip>

using namespace std;
// const int gen = 2000, dimension = 30, pSize = 40;
// float CR = 0.00, f = 0.0;

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

void Best3Mutation(double positionVector[][30], double mutantVector[][30], int np, float f, double rangeMin, double rangeMax, int bench, int bestPos)
{
  const int randomSize = 6;
  int target[randomSize];
  bool unique;
  double bestFV = pow(30, 30), fv;

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
      mutantVector[i][j] = positionVector[bestPos][j] + f * (positionVector[target[0]][j] - positionVector[target[1]][j]) + f * (positionVector[target[2]][j] - positionVector[target[3]][j]) + f * (positionVector[target[4]][j] - positionVector[target[5]][j]);
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

// void set1(float *cr, float *f)
// {
//   *cr = 0.80;
//   *f = 0.30;
// }

// void set2(float *cr, float *f)
// {
//   *cr = 0.90;
//   *f = 0.50;
// }

// void set3(float *cr, float *f)
// {
//   *cr = 0.80;
//   *f = 0.50;
// }

// int main()
// {
//   set1(&CR, &f);
//   double positionVector[pSize][dimension], mutantVector[pSize][dimension], trialVector[pSize][dimension], positionFV[pSize], trialFV[pSize], worstFV;
//   double bestSolution[30], bestFitness = pow(99, 99);
//   float CRrate[pSize][dimension];
//   double rangeMin, rangeMax;
//   int bench = 0, bestPos;
//   updateRange(&rangeMin, &rangeMax, bench);
//   init(positionVector, rangeMin, rangeMax, pSize, &bestPos, bench);

//   cout << "Start now" << endl;

//   ofstream clearFile("output.txt", ios::trunc); // clear content
//   ofstream outFile("output.txt", ios::app);     // Open file in append mode

//   for (int i = 0; i < gen; i++)
//   {
//     Best3Mutation(positionVector, mutantVector, pSize, f, rangeMin, rangeMax, bench, bestPos);
//     binomialCrossover(positionVector, mutantVector, trialVector, CR, pSize, CRrate);
//     // exponentialCrossover(positionVector, mutantVector, trialVector, CR, pSize);
//     greedySelection(positionVector, trialVector, bench, pSize, bestSolution, &bestFitness, &bestPos);
//     outFile << bestFitness << endl;
//     if (i % 10 == 0)
//     {
//       cout << "Gen " << i << " best index " << bestPos << endl;
//     }
//   }

//   cout << "The best fitness value is " << bestFitness << "\n"
//        << "The best solution " << endl;
//   for (int i = 0; i < 30; i++)
//   {
//     cout << bestSolution[i] << endl;
//   }
//   for (int i = 0; i < 30; i++)
//   {
//     cout << fixed << setprecision(15) << positionVector[30][i] << "\t" << positionVector[31][i] << "\t" << positionVector[32][i] << "\t" << positionVector[33][i] << "\t" << positionVector[34][i] << "\t" << positionVector[35][i] << "\t" << positionVector[36][i] << "\t" << positionVector[37][i] << "\t" << positionVector[38][i] << "\t" << positionVector[39][i] << endl;
//   }
// }

// g++ ./m/best3.cpp random.cpp ./c/binomialCross.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best3BG.exe
// g++ ./m/best3.cpp random.cpp ./c/exponentialCrossover.cpp ./s/greedySelection.cpp init.cpp fitnessEvaluation.cpp -o ./exe/best3EG.exe