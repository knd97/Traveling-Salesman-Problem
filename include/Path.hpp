#ifndef Path_h_
#define Path_h_

#include <iostream>
#include <vector>
#include <algorithm>
#include "AdjacencyMatrix.hpp"

class Path
{
	std::vector<unsigned>path_;
	size_t length_;
	double path_cost_;
	AdjacencyMatrix matrix_;

public:
	explicit Path(AdjacencyMatrix &matrix);
	explicit Path(AdjacencyMatrix &matrix, size_t length, double path_cost);

	double getPathCost() const;
	const size_t getPathLength() const;
	std::vector<unsigned>& get_path();
	void displayPathCost() const;

	void init_path();
	void add_to_path(const size_t index);
	double calc_path_cost() const;
	void update_path(const double new_cost);

	~Path() = default;
};
#endif // Path_h_
