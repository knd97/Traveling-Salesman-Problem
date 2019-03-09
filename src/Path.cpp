#include "Path.hpp"


Path::Path(AdjacencyMatrix &matrix) :length_{matrix.size()}, matrix_{matrix}, path_(matrix.size())
{
	std::iota(path_.begin(), path_.end() - 1, 0);
	path_.insert(path_.end(), 0);
	path_cost_ = calc_path_cost();
}

Path::Path(AdjacencyMatrix &matrix, size_t length, double path_cost) : length_{ length_ }, path_cost_{path_cost}, matrix_(matrix)
{
}

const size_t Path::getPathLength() const
{
	return length_;
}

std::vector<unsigned>& Path::get_path()
{
	return path_;
}

void Path::init_path()
{
	std::iota(path_.begin(), path_.end() - 1, 0);
	path_cost_ = calc_path_cost();
}

void Path::add_to_path(const size_t index)
{
	path_.push_back(static_cast<unsigned>(index));
	length_++;
}

void Path::update_path(const double new_cost)
{
	path_cost_ = new_cost;
}

double Path::calc_path_cost() const
{
	double cost{ 0.0 };
	for (size_t i{ 0 }; i < getPathLength() - 1; ++i)
	{
		cost += matrix_.getWeight(path_[i], path_[i + 1]);
	}
	return cost;
}

double Path::getPathCost() const
{
	return path_cost_;
}

void Path::displayPathCost() const
{
	std::cout << "Minimalny znaleziony koszt przejscia wynosi: " << path_cost_ << std::endl;
	for (const auto &it : path_)
		std::cout << it << ";";
}
