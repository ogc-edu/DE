#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>

// Definition of a solution vector
using Solution = std::vector<double>;

// Sphere function (benchmark function)
double sphere(const Solution &x)
{
  double sum = 0.0;
  for (const auto &val : x)
  {
    sum += val * val;
  }
  return sum;
}

class DifferentialEvolution
{
private:
  int population_size;
  int dimension;
  int max_generations;
  double F;  // Scaling factor
  double CR; // Crossover rate
  double lower_bound;
  double upper_bound;
  std::vector<Solution> population;
  std::vector<double> fitness;
  Solution best_solution;
  double best_fitness;

  // Random number generators
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<double> dist_real;
  std::uniform_int_distribution<int> dist_int;

public:
  DifferentialEvolution(int pop_size, int dim, int max_gen, double scaling_factor,
                        double crossover_rate, double lb, double ub)
      : population_size(pop_size), dimension(dim), max_generations(max_gen),
        F(scaling_factor), CR(crossover_rate), lower_bound(lb), upper_bound(ub),
        gen(rd()), dist_real(0.0, 1.0), dist_int(0, pop_size - 1)
  {

    // Initialize population and fitness
    population.resize(population_size, Solution(dimension));
    fitness.resize(population_size);
    best_fitness = std::numeric_limits<double>::max();
    best_solution.resize(dimension);

    initialize();
  }

  void initialize()
  {
    // Initialize population with random values within bounds
    for (int i = 0; i < population_size; ++i)
    {
      for (int j = 0; j < dimension; ++j)
      {
        population[i][j] = lower_bound + dist_real(gen) * (upper_bound - lower_bound);
      }
      // Evaluate fitness
      fitness[i] = sphere(population[i]);

      // Update best solution if needed
      if (fitness[i] < best_fitness)
      {
        best_fitness = fitness[i];
        best_solution = population[i];
      }
    }
  }

  void optimize()
  {
    for (int generation = 0; generation < max_generations; ++generation)
    {
      for (int i = 0; i < population_size; ++i)
      {
        // Select 6 distinct random individuals different from i
        std::vector<int> indices;
        while (indices.size() < 6)
        {
          int idx = dist_int(gen);
          if (idx != i && std::find(indices.begin(), indices.end(), idx) == indices.end())
          {
            indices.push_back(idx);
          }
        }

        // Perform DE/rand/3 mutation
        Solution mutant(dimension);
        for (int j = 0; j < dimension; ++j)
        {
          mutant[j] = population[indices[0]][j] + F * (population[indices[1]][j] - population[indices[2]][j] +
                                                       population[indices[3]][j] - population[indices[4]][j] +
                                                       population[indices[5]][j] - population[i][j]);

          // Bound constraint handling
          mutant[j] = std::max(lower_bound, std::min(upper_bound, mutant[j]));
        }

        // Crossover
        Solution trial(dimension);
        int random_dim = dist_int(gen) % dimension; // Ensure at least one dimension is from mutant

        for (int j = 0; j < dimension; ++j)
        {
          if (dist_real(gen) < CR || j == random_dim)
          {
            trial[j] = mutant[j];
          }
          else
          {
            trial[j] = population[i][j];
          }
        }

        // Selection
        double trial_fitness = sphere(trial);
        if (trial_fitness <= fitness[i])
        {
          population[i] = trial;
          fitness[i] = trial_fitness;

          // Update best solution if needed
          if (trial_fitness < best_fitness)
          {
            best_fitness = trial_fitness;
            best_solution = trial;
          }
        }
      }

      // Print progress every 100 generations
      if (generation % 100 == 0 || generation == max_generations - 1)
      {
        std::cout << "Generation " << generation
                  << ", Best fitness: " << std::scientific << std::setprecision(10) << best_fitness << std::endl;
      }
    }
  }

  Solution get_best_solution() const
  {
    return best_solution;
  }

  double get_best_fitness() const
  {
    return best_fitness;
  }
};

int main()
{
  // Parameters
  int population_size = 40;
  int dimension = 30;
  int max_generations = 2000;
  double scaling_factor = 0.3; // F
  double crossover_rate = 0.8; // CR
  double lower_bound = -5.12;
  double upper_bound = 5.12;

  // Create and run the DE algorithm
  DifferentialEvolution de(population_size, dimension, max_generations,
                           scaling_factor, crossover_rate, lower_bound, upper_bound);

  std::cout << "Starting Differential Evolution (DE/rand/3) optimization..." << std::endl;
  std::cout << "Benchmark function: Sphere" << std::endl;
  std::cout << "Population size: " << population_size << std::endl;
  std::cout << "Dimension: " << dimension << std::endl;
  std::cout << "Max generations: " << max_generations << std::endl;
  std::cout << "F: " << scaling_factor << ", CR: " << crossover_rate << std::endl;
  std::cout << "Bounds: [" << lower_bound << ", " << upper_bound << "]" << std::endl;
  std::cout << "------------------------------------------------------" << std::endl;

  de.optimize();

  std::cout << "------------------------------------------------------" << std::endl;
  std::cout << "Optimization completed!" << std::endl;
  std::cout << "Best fitness: " << std::scientific << std::setprecision(20) << de.get_best_fitness() << std::endl;

  std::cout << "Best solution: ";
  const auto &best_solution = de.get_best_solution();
  for (size_t i = 0; i < best_solution.size(); ++i)
  {
    std::cout << std::fixed << std::setprecision(6) << best_solution[i];
    if (i < best_solution.size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;

  return 0;
}