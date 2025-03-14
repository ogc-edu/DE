#include "init.h"
#include "random.h"
#include <iostream>
#include "fitnessEvaluation.h"
#include <math.h>

void init(double positionVector[][30], double rangeMin, double rangeMax, int np, int* bestPos, int bench){
  for(int i=0; i<np; i++){
    for(int j=0; j<30; j++){
      positionVector[i][j] = generateRandomDouble(rangeMin, rangeMax);
    }
  }
  double lowestFV = pow(30,30), fv;
  for(int i=0; i<np; i++){
    fv = fitness(positionVector[i], bench);
    if(fv < lowestFV){
      *bestPos = i;
      lowestFV = fv;
    }
  }
}