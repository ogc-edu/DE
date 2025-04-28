#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES // define use_math_defines macro before including <math.h>
#include <math.h>
float fv = 0;
double ras(double arr[])
{
  int dimension = 30;
  double sumFit = 0;
  float firstPart = 10 * dimension;
  for (int i = 0; i < dimension; i++)
  {
    fv = pow(arr[i], 2) - 10 * cos(2 * M_PI * arr[i]);
    sumFit += fv;
  }
  return firstPart + sumFit;
}

int main()
{
  long double tiny = 1e-25;
  std::cout << "Default: " << tiny << std::endl;
  std::cout << "With precision: " << std::setprecision(50) << tiny << std::endl;
  double arr[30] = {-1.84141e-05, 3.30335e-05, -2.20391e-05, 3.43912e-05, 4.25915e-05, -5.1099e-05, 8.17622e-06, -1.0271e-05, 5.28569e-06, -5.36032e-06, 4.64715e-05, -2.3989e-05, -4.83772e-05, -3.9413e-05, 4.74691e-06, 4.29824e-05, 6.05541e-06, 1.75738e-05, -6.98656e-06, -4.2879e-05, -2.86779e-05, 2.73519e-05, 4.12987e-05, -9.10208e-06, 8.21024e-06, -2.3331e-05, -1.03836e-05, -2.00136e-05, -1.92628e-05, 6.22287e-06};
  double arr2[30] = {2.72325e-05, 1.34041e-05, -2.12752e-05, 1.15856e-05, 2.26533e-05, -4.5007e-05, 3.36869e-05, 3.60527e-06, 2.83031e-05, 3.86196e-05, 4.65224e-05, -2.64543e-05, -2.72425e-05, -7.98421e-06, 1.50001e-05, -9.18427e-06, 3.1887e-05, 1.64287e-05, 2.53105e-06, -3.66769e-05, -4.28656e-05, -2.39881e-06, 2.06764e-05, -6.66712e-06, -9.24994e-06, 8.16239e-07, -3.23646e-05, 2.58984e-05, -3.07457e-05, 1.05153e-05};

  double value = ras(arr);
  double value2 = ras(arr2);
  std::cout << "value is " << std::setprecision(50) << value << std::endl;
  std::cout << "value2 is " << std::setprecision(50) << value2 << std::endl;
}
