#ifndef FileHandler_h_
#define FileHandler_h_

#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <fstream>
#include <regex>
#include <memory>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"


class FileHandler
{
	const std::string fileName_;

public:
	FileHandler() = default;
	explicit FileHandler(const std::string fileName);
	void readDataFromFile(std::vector<std::vector<double>>&distances);
	bool checkPath() const;
	~FileHandler() = default;

private:
	const std::string& getFileName() const;
	void filesInDirectory(const std::experimental::filesystem::path &dir) const;
	size_t extractSize(const rapidxml::xml_node<> *node) const;
};
#endif // FileHandler_h_