#include "FileHandler.hpp"

FileHandler::FileHandler(const std::string fileName) :fileName_{ fileName }
{
}

void FileHandler::filesInDirectory(const std::experimental::filesystem::path &dir) const
{
	for (const std::experimental::filesystem::directory_entry &e : std::experimental::filesystem::directory_iterator {dir})
		std::cout << e.path().filename() << "\n";
}

const std::string& FileHandler::getFileName() const
{
	return fileName_;
}

size_t FileHandler::extractSize(const rapidxml::xml_node<> *node) const
{
	size_t size{ 0 };
	for (auto vertex{ node->first_node("vertex") }; vertex; vertex = vertex->next_sibling())
	{
		size++;
	}
	return size;
}

bool FileHandler::checkPath() const
{
	try
	{
		const std::experimental::filesystem::path directory{ getFileName() };
		std::cout << "Current working directory: " << std::experimental::filesystem::canonical(directory).string() << "\n";
		filesInDirectory(directory);
		return true;
	}
	catch (const std::experimental::filesystem::filesystem_error& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

void FileHandler::readDataFromFile(std::vector<std::vector<double>>&distances)
{
	auto file_name = getFileName().c_str();
	try
	{
		rapidxml::file<> xmlFile(file_name);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> * root_node = doc.first_node("travellingSalesmanProblemInstance");
		rapidxml::xml_node<> * graph_node = root_node->first_node("graph");

		std::string name = root_node->first_node("name")->value();
		distances.reserve(extractSize(graph_node));
		for (auto *vertex_node{ graph_node->first_node("vertex") }; vertex_node; vertex_node = vertex_node->next_sibling())
		{
			std::vector<double>row_from_file;
			for (auto *edge_node{ vertex_node->first_node("edge") }; edge_node; edge_node = edge_node->next_sibling())
			{
				double cost{ std::atof(edge_node->first_attribute("cost")->value()) };
				row_from_file.push_back(cost);
			}
			distances.push_back(row_from_file);
		}
	}	
	catch (const rapidxml::parse_error& e){
		std::cerr << "Parse error was: " << e.what() << std::endl;
	}
	catch (const std::runtime_error& e){
		std::cerr << "Runtime error was: " << e.what() << std::endl;
	}
	catch (...){
	}
}