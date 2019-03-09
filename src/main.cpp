#include <iostream>
#include <functional>
#include "MenuHandler.hpp"

int main(int argc, char *argv[])
{
	std::string path = (std::string) argv[1];
    
	FileHandler file(path);
	MenuHandler handler(file);
	handler.run_main_menu();

	system("pause");
	return 0;
}
