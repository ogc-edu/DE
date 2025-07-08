#include <iostream>
#include "fitnessEvaluation.h"
#include "random.h"
#include <vector>
#include <algorithm>

using namespace std;

void sts(double positionVector[][30], double trialVector[][30], int n, int bench, int np)
{
  int ss = 0; // subset size
  if (np == 40)
    ss = 2;
  else if (np == 100)
    ss = 6;
  else if (np == 150)
    ss = 12;
  else
  {
    cout << "Wrong NP";
    exit(1); // only receive NP=40,100,150
  }
  int subsetNumber = 0;
  if (np % ss == 0) // determine number of subset, no remainder
  {
    subsetNumber = np / ss;
  }
  else // remainder, additional vector become extra subset with < SS vectors
  {
    subsetNumber = (np / ss) + 1;
  }
  vector<vector<vector<double>>> TAS(subsetNumber, vector<vector<double>>(ss, vector<double>(30, 0))); // 3d vector for target vector subset e.g: TAS[subsetNumber][subset size][dimension]
  vector<vector<vector<double>>> TRS(subsetNumber, vector<vector<double>>(ss, vector<double>(30, 0))); // 3d vector for trial vector subset
  int pos = generateRandomFloat() * np;                                                                // generate random starting index
  int temp = np;                                                                                       // keep track of uncategorized vectors
  vector<vector<double>> bestVector(ss, vector<double>(30, 0));                                        // to get the best ss vectors and its dimensions bestVector[ss][30];
  for (int i = 0; i < subsetNumber; i++)
  {
    for (int j = 0; j < ss; j++) // arrange into TAS and TRS in one subset
    {
      for (int k = 0; k < 30; k++)
      {
        TAS[i][j][k] = positionVector[pos][k];
        TRS[i][j][k] = trialVector[pos][k];
      }
      pos++;
      pos %= np;
    }
    std::vector<std::pair<double, std::vector<double>>> combined; // combined[0].first = fv, combined[0].second = dimensions
    for (int j = 0; j < ss; j++)
    {
      vector<double> targetFit = TAS[i][j];
      vector<double> trialFit = TRS[i][j];
      combined.push_back({fitness(targetFit.data(), bench), TAS[i][j]});
      combined.push_back({fitness(trialFit.data(), bench), TRS[i][j]});
    }
    nth_element(combined.begin(), combined.begin() + ss, combined.end(), [](const auto &a, const auto &b)
                { return a.first < b.first; });
    int currentPos;
    for (int j = 0; j < ss; j++)
    {
      for (int k = 0; k < 30; k++)
      {
        currentPos = (pos - ss + j) % 40;
        positionVector[pos - ss + j][k] = combined[j].second[k]; // copy array
      }
    }
  }
};