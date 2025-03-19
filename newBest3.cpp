#include <iostream>
#include "./init.h"
#include "./random.h"
#include "./fitnessEvaluation.h"
#include <unordered_set>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;
const int pSize = 40, dimension = 30;

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

int main()
{
  double targetVector[pSize][dimension], mutantVector[pSize][dimension], trialVector[pSize][dimension];
  double rangeMin = -5.12, rangeMax = 5.12, genBestFV;
  int bestPos, bench = 4;

  // Initialize target population and set bestPos
  init(targetVector, rangeMin, rangeMax, pSize, &bestPos, bench);
  genBestFV = fitness(targetVector[bestPos], bench);

  double f = 0.3, cr = 0.8;

  for (int generation = 0; generation < 2000; generation++)
  {
    // Process each individual in the population
    for (int i = 0; i < pSize; i++)
    {
      const int randomSize = 6;
      int idx[randomSize];
      bool unique;
      // cout << "The best index in gen" << generation << " for position " << i << " is " << bestPos << endl;
      //  Generate 6 unique random indices for mutation
      do
      {
        for (int k = 0; k < randomSize; k++)
        {
          idx[k] = static_cast<int>(generateRandomFloat() * pSize);
        }
        unique = areAllUnique(idx, randomSize);
      } while (!unique);

      // Mutation
      // best + F * (x_r1 - x_r2) + F * (x_r3 - x_r4) + F * (x_r5 - x_r6))
      for (int j = 0; j < dimension; j++)
      {
        mutantVector[i][j] = targetVector[bestPos][j] + f * ((targetVector[idx[0]][j] - targetVector[idx[1]][j]) + (targetVector[idx[2]][j] - targetVector[idx[3]][j]) + (targetVector[idx[4]][j] - targetVector[idx[5]][j]));

        // boundary enforce
        if (mutantVector[i][j] > rangeMax)
          mutantVector[i][j] = rangeMax;
        if (mutantVector[i][j] < rangeMin)
          mutantVector[i][j] = rangeMin;
      }

      // Crossover
      int d_rand = static_cast<int>(generateRandomFloat() * dimension);
      for (int j = 0; j < dimension; j++)
      {
        if (generateRandomFloat() <= cr || j == d_rand)
          trialVector[i][j] = mutantVector[i][j];
        else
          trialVector[i][j] = targetVector[i][j];
      }

      // Selection
      double trialFitness = fitness(trialVector[i], bench);
      double targetFitness = fitness(targetVector[i], bench);
      if (trialFitness <= targetFitness)
      {
        for (int j = 0; j < dimension; j++)
        {
          targetVector[i][j] = trialVector[i][j];
        }
        targetFitness = trialFitness;
      }

      // Update the best solution in the population if necessary
      if (targetFitness <= genBestFV)
      {
        genBestFV = targetFitness;
        bestPos = i;
      }
    }
    if (generation % 100 == 0)
      std::cout << "Generation " << generation
                << ", Best fitness: " << std::scientific << std::setprecision(10) << genBestFV << std::endl;
  }
}

// g++ random.cpp init.cpp fitnessEvaluation.cpp newBest3.cpp -o ./exe/newBest.exe

// #include <iostream>
// #include "./init.h"
// #include "./random.h"
// #include "./fitnessEvaluation.h"
// #include <unordered_set>
// #include <cmath>

// using namespace std;
// const int pSize = 40, dimension = 30;

// bool areAllUnique(int arr[], int size)
// {
//   unordered_set<int> seen;
//   for (int i = 0; i < size; ++i)
//   {
//     if (seen.find(arr[i]) != seen.end())
//     {
//       return false; // Duplicate found
//     }
//     seen.insert(arr[i]);
//   }
//   return true; // All elements are unique
// }

// int main()
// {
//   double targetVector[pSize][dimension], mutantVector[pSize][dimension], trialVector[pSize][dimension];
//   double rangeMin = -5.12, rangeMax = 5.12, genBestFV;
//   int bestPos, bench = 4;
//   init(targetVector, rangeMin, rangeMax, pSize, &bestPos, bench);
//   for (int i = 0; i < 30; i++)
//   {
//     cout << targetVector[2][i] << endl;
//   }
//   genBestFV = fitness(targetVector[bestPos], bench);
//   double f = 0.3, cr = 0.8;
//   cout << "Best is " << genBestFV;
//   for (int generation = 0; generation < 2000; generation++)
//   {
//     for (int i = 0; i < pSize; i++)
//     {
//       const int randomSize = 6;
//       int target[randomSize];
//       bool unique;
//       double bestFV = pow(30, 30), fv;

//       for (int j = 0; j < pSize; j++)
//       {
//         do
//         {
//           for (int k = 0; k < randomSize; k++)
//           {
//             target[k] = static_cast<int>(generateRandomFloat() * pSize);
//           }
//           unique = areAllUnique(target, randomSize);
//         } while (unique == false);
//         for (int j = 0; j < 30; j++)
//         {
//           // mutantVector[i][j] = targetVector[bestPos][j] + f * (targetVector[target[0]][j] - targetVector[target[1]][j]) + f * (targetVector[target[2]][j] - targetVector[target[3]][j]) + f * (targetVector[target[4]][j] - targetVector[target[5]][j]);
//           mutantVector[i][j] = targetVector[bestPos][j] + f * (targetVector[target[0]][j] - targetVector[target[1]][j] + targetVector[target[2]][j] - targetVector[target[3]][j] + targetVector[target[4]][j] - targetVector[target[5]][j]);
//           if (mutantVector[i][j] > rangeMax)
//           {
//             mutantVector[i][j] = rangeMax;
//           }
//           if (mutantVector[i][j] < rangeMin)
//           {
//             mutantVector[i][j] = rangeMin;
//           }
//         }

//         // crossover
//         for (int j = 0; j < pSize; j++)
//         {
//           // Ensure at least one dimension comes from mutant vector
//           int d_rand = static_cast<int>(generateRandomFloat() * 30);

//           for (int j = 0; j < 30; j++)
//           {
//             if (generateRandomFloat() <= cr || j == d_rand)
//             {
//               trialVector[i][j] = mutantVector[i][j];
//             }
//             else
//             {
//               trialVector[i][j] = targetVector[i][j];
//             }
//           }
//         }

//         // selection
//         if (fitness(trialVector[i], bench) <= fitness(targetVector[i], bench))
//         {
//           for (int j = 0; j < 30; j++)
//           {
//             targetVector[i][j] = trialVector[i][j];
//           }
//         }
//         // update best fitness
//         if (fitness(trialVector[i], bench) <= genBestFV)
//         {
//           genBestFV = fitness(trialVector[i], bench);
//           bestPos = i;
//         }
//       }
//     }
//     cout << "Curr " << generation << "\t" << genBestFV << endl;
//   }
//   cout << "Best fitness overall " << genBestFV;
// }
// // g++ random.cpp init.cpp fitnessEvaluation.cpp -o ./exe/newBest.exe