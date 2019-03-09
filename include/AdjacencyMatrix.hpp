#ifndef AdjacencyMatrix_h_
#define AdjacencyMatrix_h_

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <limits>
#include <numeric>
#include "FileHandler.hpp"

class AdjacencyMatrix
{
private:
	typedef std::vector<std::vector<double>>adjacencyMatrix;
	adjacencyMatrix adjacencyMatrix_;
	std::vector<double>maxInRows_;
	std::vector<double>maxInCols_;
	size_t vertices_;

public:
	AdjacencyMatrix() = default;
	explicit AdjacencyMatrix(FileHandler& handler);

	bool isEdge(const size_t start, const size_t end) const;
	double getWeight(const size_t start, const size_t end) const;
	size_t size() const;
	double sum_max() const;
	size_t get_nearest(const size_t index, std::vector<bool>&is_visited);


	~AdjacencyMatrix() = default;

private:
	std::vector<double> max_in_columns();
	double get_column_max(const size_t column_index) const;
	std::vector<double> max_in_rows();
	void insert_sorted(std::vector<double>&vec, const double max_element);
};
#endif // AdjacencyMatrix_h_
