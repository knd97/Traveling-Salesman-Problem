#ifndef NearestNeighbour_h_
#define NearestNeighbour_h_
#include <iostream>
#include "AdjacencyMatrix.hpp"
#include "Path.hpp"

class NearestNeighbour
{
	AdjacencyMatrix matrix_;
	Path best_path_;
	std::vector<bool>is_visited_;

public:
	explicit NearestNeighbour(AdjacencyMatrix &matrix);
	Path& run();
	~NearestNeighbour() = default;

private:
	bool check_if_all_visited() const;
	void update_visited_cites(const size_t index);
	void init_solution();
	void add_last_city();
};
#endif // NearestNeighbour_h_
