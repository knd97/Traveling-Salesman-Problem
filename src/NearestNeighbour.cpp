#include "NearestNeighbour.hpp"


NearestNeighbour::NearestNeighbour(AdjacencyMatrix &matrix) : matrix_{ matrix }, best_path_{ matrix, 0, 0 }, is_visited_(matrix.size(), false)
{
}

Path& NearestNeighbour::run()
{
	if (best_path_.getPathCost() > 0)
	{
		return best_path_;
	}
	else
	{
		init_solution();
		size_t current_city{ 0 };

		while (check_if_all_visited() == false)
		{
			current_city = matrix_.get_nearest(current_city, is_visited_);
			best_path_.add_to_path(current_city);
			update_visited_cites(current_city);
		}
		add_last_city();
	}
	return best_path_;
}

bool NearestNeighbour::check_if_all_visited() const
{
	bool visited{ true };
	if (std::any_of(is_visited_.begin(), is_visited_.end(), [](auto index_val) {return index_val == false; }))
	{
		visited = false;
	}
	return visited;
}

void NearestNeighbour::update_visited_cites(const size_t index)
{
	is_visited_[index] = true;
}

void NearestNeighbour::init_solution()
{
	best_path_.add_to_path(0);
	update_visited_cites(0);
}

void NearestNeighbour::add_last_city()
{
	best_path_.add_to_path(0);
	best_path_.update_path(best_path_.calc_path_cost());
}
