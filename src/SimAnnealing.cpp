#include "SimAnnealing.hpp"


SimAnnealing::SimAnnealing(double cooling_rate, AdjacencyMatrix &matrix, double diff, NearestNeighbour &n_n) 
	:initial_temp_{ matrix.sum_max() }, best_path_{ n_n.run() },
	cooling_rate_{ cooling_rate }, time_{ diff }, 
	period_{ static_cast<int>(0.01 *matrix.size() + 2) }, temp_path_{ n_n.run()}
{
}

double SimAnnealing::random_probability() const
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<> uniform_dist(0.0, 1.0);

	return uniform_dist(e1);
}

bool SimAnnealing::checkSolution(double best_cost, double current_cost, double current_temp) const
{
	return ((exp((best_cost - current_cost) / current_temp)) > random_probability());
}

void SimAnnealing::updatePathCost(Path & current_solution, double temp)
{
	if (temp_path_.getPathCost() > current_solution.getPathCost() ||
		checkSolution(temp_path_.getPathCost(), current_solution.getPathCost(), temp))
	{
		temp_path_ = current_solution;
		temp_path_.update_path(temp_path_.calc_path_cost());
		is_global_min(temp_path_);
	}
}

void SimAnnealing::insert_rand_city(Path& current_path)
{
	auto current_position{ random_city() };
	auto value_at{ current_path.get_path().at(current_position) };

	current_path.get_path().erase(current_path.get_path().begin() + current_position);
	current_path.get_path().insert(current_path.get_path().begin() + random_city(), value_at);
	current_path.update_path(current_path.calc_path_cost());
}

void SimAnnealing::generate_new_solution(double temp)
{
	for (size_t i{ 0 }; i < period_; ++i)
	{
		Path current_solution{ temp_path_ };
		insert_rand_city(current_solution);
		updatePathCost(current_solution, temp);
	}
}

int SimAnnealing::random_city()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(1, static_cast<int>(temp_path_.getPathLength() - 2));

	return uniform_dist(e1);
}

void SimAnnealing::is_global_min(Path & current_path)
{
	if (current_path.getPathCost() < best_path_.getPathCost())
	{
		best_path_ = current_path;
		best_path_.update_path(best_path_.calc_path_cost());
	}
}