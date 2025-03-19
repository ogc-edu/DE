#include <iostream>
#include <unordered_set>

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