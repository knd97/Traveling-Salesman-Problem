#ifndef TabuSearch_h_
#define TabuSearch_h_

#include <iostream>
#include "NearestNeighbour.hpp"

class TabuSearch
{
	AdjacencyMatrix matrix_;
	Path best_path_;
	Path temp_path_;
	std::vector<std::vector<int>>tabu_list_;
	const int no_improving_moves_;
	const double time_;

public:
	explicit TabuSearch(AdjacencyMatrix &matrix, NearestNeighbour &nearest, const double time);

	~TabuSearch() = default;

	void swap_cities(Path & temp_path, size_t start, size_t end)
	{
		auto it_begin{ temp_path.get_path().begin() + start };
		auto it_end{ temp_path.get_path().begin() + end };

		std::iter_swap(it_begin, it_end);
		temp_path.update_path(temp_path.calc_path_cost());
	}

	void invert_cities(Path & temp_path, size_t start, size_t end)
	{
		auto it_begin{ temp_path.get_path().begin() + start };
		auto it_end{ temp_path.get_path().begin() + end };

		std::reverse(it_begin, it_end);
		temp_path.update_path(temp_path.calc_path_cost());
	}

	void insert_city(Path & temp_path, size_t current_position, size_t target_position)
	{
		auto value_at{ temp_path.get_path().at(current_position) };

		temp_path.get_path().erase(temp_path.get_path().begin() + current_position);
		temp_path.get_path().insert(temp_path.get_path().begin() + target_position, value_at);
		temp_path.update_path(temp_path.calc_path_cost());
	}

	template<class T>
	void run(T neighborhood)
	{
		auto start{ std::chrono::system_clock::now() };
		std::chrono::system_clock::time_point end{};
		auto counter{ 0 };
		int j{ 1 };

		while (std::chrono::duration<double>(end - start).count() < time_)
		{
			Path current_solution = { temp_path_ };
			std::pair<bool, Path> best_neighbour{ nearest_neighbour(neighborhood, current_solution) };
			if (best_neighbour.first)
			{
				temp_path_ = best_neighbour.second;
				check_global_min(temp_path_);
				counter = 0;
			}
			else
			{
				counter = diversification(counter);	
			}
			decrement_tabu_list();
			end = std::chrono::system_clock::now();
		}
		best_path_.displayPathCost();
	}

	template<class T>
	std::pair<bool, Path> nearest_neighbour(T& neighborhood, Path &current_path)
	{
		std::pair<size_t, size_t>move;
		bool is_better{ false };
		Path best{ current_path };

		for (size_t i{ 1 }; i < current_path.getPathLength() - 1; ++i)
		{
			for (size_t j{ i + 1 }; j < current_path.getPathLength() - 1; ++j)
			{
				Path temp_neighbour{ current_path };
				neighborhood(temp_neighbour, i, j);
				if (check_solution(temp_neighbour, best, i, j))
				{
					best = temp_neighbour;
					move = std::make_pair(i, j);
					is_better = true;
				}
			}
		}
		update_tabu_list(move);
		return { is_better, best };
	}

private:
	void update_tabu_list(const std::pair<size_t, size_t>move);
	bool check_solution(Path &current, Path& best, const size_t start, const size_t end) const;
	bool aspiration_criterion(Path &current, Path& best, const size_t start, const size_t end) const;
	int diversification(int it);
	void decrement_tabu_list();
	double rand_tabu_tenure();
	void clear_tabu_list();
	void random_solution();
	void check_global_min(Path &temp_path);
};
#endif // TabuSearch_h_
