#include "AdjacencyMatrix.hpp"

AdjacencyMatrix::AdjacencyMatrix(FileHandler &handler) : adjacencyMatrix_{}
{
	handler.readDataFromFile(adjacencyMatrix_);
	vertices_ = adjacencyMatrix_.size();
	maxInCols_ = max_in_columns();
	maxInRows_ = max_in_rows();
}

bool AdjacencyMatrix::isEdge(const size_t start, const size_t end) const
{
	return (adjacencyMatrix_.at(start).at(end) >= 0);
}

double AdjacencyMatrix::getWeight(const size_t start, const size_t end) const
{
	return (isEdge(start, end) ? adjacencyMatrix_[start][end] : -1);
}

std::vector<double> AdjacencyMatrix::max_in_columns()
{
	std::vector<double> col;
	col.reserve(size());
	for (size_t i{0}; i < size(); ++i)
	{
		insert_sorted(col, get_column_max(i));
	}
	return col;
}

double AdjacencyMatrix::get_column_max(const size_t column_index) const
{
	double max_column_element{0.0};
	size_t diagonal{0};
	for (const auto &row : adjacencyMatrix_)
	{
		if (row.at(column_index) > max_column_element && column_index != diagonal)
			max_column_element = row[column_index];
		diagonal++;
	}
	return max_column_element;
}

std::vector<double> AdjacencyMatrix::max_in_rows()
{
	std::vector<double> row;
	row.reserve(size());
	size_t diagonal{0};
	auto max_element{0.0};
	for (auto &it : adjacencyMatrix_)
	{
		if (diagonal != 0 && diagonal != size() - 1)
		{
			max_element = std::max(*std::max_element(it.begin(), it.begin() + diagonal),
								   *std::max_element(it.begin() + diagonal + 1, it.end()));
		}
		else if (diagonal == 0)
		{
			max_element = *std::max_element(it.begin() + 1, it.end());
		}
		else if (diagonal == size() - 1)
		{
			max_element = *std::max_element(it.begin(), it.end() - 1);
		}
		insert_sorted(row, max_element);
		diagonal++;
	}
	return row;
}

void AdjacencyMatrix::insert_sorted(std::vector<double> &vec, const double min_element)
{
	const auto insert_pos(std::lower_bound(std::begin(vec), std::end(vec), min_element));
	vec.insert(insert_pos, min_element);
}

size_t AdjacencyMatrix::size() const
{
	return vertices_;
}

double AdjacencyMatrix::sum_max() const
{
	auto even{size() % 2};
	return std::accumulate(maxInCols_.begin(), maxInCols_.begin() + maxInCols_.size() / 2, 0.0) 
							+ std::accumulate(maxInRows_.begin(), maxInRows_.begin() 
							+ maxInRows_.size() / 2 + even, 0.0);
}

size_t AdjacencyMatrix::get_nearest(const size_t index, std::vector<bool> &is_visited)
{
	size_t position{0};
	auto min{std::numeric_limits<double>::max()};
	for (size_t i{0}; i < is_visited.size(); ++i)
	{
		if (is_visited[i] == false && min > adjacencyMatrix_[index][i])
		{
			min = adjacencyMatrix_[index][i];
			position = i;
		}
	}
	return position;
}