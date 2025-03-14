#include <iostream>
#include "fitnessEvaluation.h"
#include "random.h"

using namespace std;

void sts(double positionVector[][30], double trialVector[][30], int n, int bench, int np){
  // if(np%ss ==0){
  //   n = np/ss;
  // }
  // else{
  //   n = (np/ss) + 1;
  // }
  int startPos = generateRandomFloat() * np;
  int npLeft = np;
  for(int i=0; i<n; i++){
    npLeft = np - (n*i);
    for(int j=0; j<npLeft; j++){
      if(j > n) break;
    }
    
  }
};