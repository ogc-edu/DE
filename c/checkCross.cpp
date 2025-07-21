#include <iostream>
#include "./onePointCross.h"
#include "./twoPointCross.h"
#include "../init.h"
#include "../random.h"
#include "../fitnessEvaluation.h"
#include "../m/best3.h"
#include "../m/unique.h"
using namespace std;
int main()
{
  const int np = 10;
  std::cout << "Target\t\tMutant\t\tTrial" << std::endl;
  double positionVector[np][30];
  double trialVector[np][30];
  double mutantVector[np][30];
  double rangeMin = -65.536, rangeMax = 65.536;
  int bestPos;
  int bench = 2;
  float cr = 0.30;
  init(positionVector, rangeMin, rangeMax, np, &bestPos, 2); // initialize position vectors once
  cout << "Mut" << endl;
  Best3Mutation(positionVector, mutantVector, np, 0.80, rangeMin, rangeMax, 2, bestPos);
  cout << "Cross" << endl;
  onePointCross(positionVector, mutantVector, trialVector, cr, np);
  cout << "Exit" << endl;
  std::cout << "Target\t\tMutant\t\tTrial" << std::endl;
  for (int j = 0; j < 30; j++)
  {
    std::cout << positionVector[0][j] << "\t" << mutantVector[0][j] << "\t" << trialVector[0][j] << std::endl;
  }
}

// g++ ../random.cpp ../init.cpp ../fitnessEvaluation.cpp ./checkCross.cpp ../m/best3.cpp ./onePointCross.cpp ../m/unique.cpp -o oneCross.exe