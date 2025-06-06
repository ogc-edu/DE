#include "random.h"
#include <iostream>
#include <random>

// should be [0,1)
//  Function to generate a random floating-point number between 0.0 and 1.0
float generateRandomFloat()
{
    static std::mt19937 mt(std::random_device{}());         // Static PRNG to avoid reseeding
    std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Uniform distribution         //semi-open interval

    return dist(mt); // Generate and return a random float
}

// Function to generate a random double between two specified double values
double generateRandomDouble(double min, double max)
{
    static std::mt19937 mt(std::random_device{}());                                                            // Static PRNG to avoid reseeding
    std::uniform_real_distribution<double> dist(min, std::nextafter(max, std::numeric_limits<double>::max())); // moves max double to the nearest next 53-bit closest double
    // closed interval

    return dist(mt); // Generate and return a random double
}

// check random value

// int main()
// {
//     int random;
//     while (true)
//     {
//         random = static_cast<int>(generateRandomFloat() * 40);
//         std::cout << random << std::endl;
//         if (random > 39 || random < 0)
//         {
//             std::cout << "WRONG " << std::endl;
//             exit(1);
//         }
//     }
//     return 0;
// }