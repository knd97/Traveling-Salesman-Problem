#include "TabuSearch.hpp"

TabuSearch::TabuSearch(AdjacencyMatrix & matrix, NearestNeighbour &nearest, const double time)
	:matrix_{ matrix }, best_path_{ nearest.run() }, 
	tabu_list_(matrix_.size(), std::vector<int>(matrix_.size(), 0)), 
	time_{time}, no_improving_moves_{ 10 }, temp_path_{ nearest.run() }
{
}

void TabuSearch::update_tabu_list(const std::pair<size_t, size_t>move)
{
	auto tabu_tenure{ rand_tabu_tenure() };
	auto start{ move.first };
	auto end{ move.second };

	tabu_list_[start][end] = static_cast<int>(tabu_tenure);
}

bool TabuSearch::check_solution(Path & current, Path & best, const size_t start, const size_t end) const
{
	return ((tabu_list_[start][end] == 0 && current.getPathCost() < best.getPathCost()) ||
		aspiration_criterion(current, best, start, end)) ? true : false;
}

bool TabuSearch::aspiration_criterion(Path & current, Path & best, const size_t start, const size_t end) const
{
	return (tabu_list_[start][end] != 0 && current.getPathCost() < best.getPathCost()) ? true : false;
}

int TabuSearch::diversification(int it)
{
	++it;
	if(it == no_improving_moves_)
	{
		clear_tabu_list();
		temp_path_.init_path();
		random_solution();
		check_global_min(temp_path_);
		it = 0;
	}
	return it;
}

void TabuSearch::decrement_tabu_list()
{
	for (auto &it : tabu_list_)
	{
		std::for_each(it.begin(), it.end(), [&](int &i) {if (i > 0) { return --i; } else { return i; }});
	}
}

double TabuSearch::rand_tabu_tenure()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<> uniform_dist(sqrt(matrix_.size()), 2 * sqrt(matrix_.size()));

	return uniform_dist(e1);
}

void TabuSearch::clear_tabu_list()
{
	std::fill(tabu_list_.begin(), tabu_list_.end(), std::vector<int>(matrix_.size(), 0));
}

void TabuSearch::random_solution()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(temp_path_.get_path().begin() + 1, temp_path_.get_path().end() - 1, g);
	temp_path_.update_path(temp_path_.calc_path_cost());
}

void TabuSearch::check_global_min(Path & temp_path)
{
	if (best_path_.getPathCost() > temp_path.getPathCost())
	{
		best_path_ = temp_path;
	}
}
