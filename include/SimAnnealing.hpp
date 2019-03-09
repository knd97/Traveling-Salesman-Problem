#ifndef SimAnnealing_h_
#define SimAnnealing_h_

#include <iostream>
#include <chrono>
#include <random>
#include <math.h>
#include "Path.hpp"
#include "NearestNeighbour.hpp"

class SimAnnealing
{
	const double initial_temp_;
	const double cooling_rate_;
	Path temp_path_;
	Path best_path_;
	const double time_;
	const int period_;

public:
	explicit SimAnnealing(double cooling_rate, AdjacencyMatrix &matrix, const double diff, NearestNeighbour &n_n);

	template<class T>
	void run(AdjacencyMatrix &matrix, T cooling)
	{
		auto start{ std::chrono::system_clock::now() };
		std::chrono::system_clock::time_point end{};
		double start_temp = initial_temp_;		
		int iteration{ 0 };
		int j{ 1 };

		while (std::chrono::duration<double>(end - start).count() < time_)
		{
			generate_new_solution(start_temp);
			start_temp = cooling(start_temp, iteration);
			++iteration;
			end = std::chrono::system_clock::now();
		}
		best_path_.displayPathCost();
	}

	double linearCooling(double current_temp, int temp_cycle) const
	{
		return cooling_rate_ * current_temp;
	}

	double logarithmicalCooling(double current_temp, int temp_cycle) const
	{
		return (initial_temp_ / (1 + cooling_rate_ * log10(1 + temp_cycle)));
	}

	double exponentialCooling(double current_temp, int temp_cycle) const
	{
		return initial_temp_ * pow(cooling_rate_, temp_cycle);
	}

	~SimAnnealing() = default;

private:
	double random_probability() const;
	bool checkSolution(double best_cost, double current_cost, double current_temp) const;
	void updatePathCost(Path &current_solution, double temp);
	void insert_rand_city(Path& current_path);
	void generate_new_solution(double temp);
	int random_city();
	void is_global_min(Path& current_path);
};
#endif // SimAnnealing_h_
