#include "MenuHandler.hpp"

MenuHandler::MenuHandler(FileHandler &file) 
	:time_{ 0.0 }, cooling_type_{ 0 }, cooling_rate_{ 0.0 }, neighbour_type_{ 0 }, file_{file}
{
}

void MenuHandler::run_main_menu()
{
	auto choice{ 0 };

	while (choice != 8)
	{
		std::cout << "\n";
		for (const auto &it : main_menu_options_)
			std::cout << it << "\n";
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				clear_screen();
				file_.checkPath();
				std::string fileName;
				std::cout << "Prosze podac nazwe wybranego pliku testowego: " << std::endl;
				std::cin >> fileName;

				FileHandler file{ fileName };
				AdjacencyMatrix matrix{ file };
				set_matrix(matrix);
				break;
			}
			case 2:
			{
				clear_screen();
				sa_parameters_menu();
				break;
			}
			case 3:
			{
				clear_screen();
				tabu_parameters_menu();
				break;
			}
			case 4:
			{
				clear_screen();
				sa_cooling_menu();
				break;
			}
			case 5:
			{
				clear_screen();
				tabu_neighbours_menu();
				break;
			}
			case 6:
			{
				clear_screen();
				std::cout << "Symulowane wyzarzanie:\n" << std::endl;
				NearestNeighbour n{ matrix_ };
				SimAnnealing s{ cooling_rate_, matrix_, time_, n };
				switch (cooling_type_)
				{
					case 1:
					{
						s.run(matrix_, std::bind(&SimAnnealing::linearCooling, s, std::placeholders::_1, std::placeholders::_2));
						break;
					}
					case 2:
					{
						s.run(matrix_, std::bind(&SimAnnealing::logarithmicalCooling, s, std::placeholders::_1, std::placeholders::_2));
						break;
					}
					case 3:
					{
						s.run(matrix_, std::bind(&SimAnnealing::exponentialCooling, s, std::placeholders::_1, std::placeholders::_2));
						break;
					}
					default:
					{
						break;
					}
				}
				break;
			}
			case 7:
			{
				clear_screen();
				std::cout << "Tabu search:\n" << std::endl;
				NearestNeighbour n{ matrix_ };
				TabuSearch t{matrix_, n, time_};
				switch (neighbour_type_)
				{
					case 1:
					{
						t.run(std::bind(&TabuSearch::swap_cities, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					case 2:
					{
						t.run(std::bind(&TabuSearch::invert_cities, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					case 3:
					{
						t.run(std::bind(&TabuSearch::insert_city, t, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
						break;
					}
					default:
					{
						break;
					}
				}
				break;
			}
			case 8:
			{
				clear_screen();
				exit(0);
			}
			default:
			{
				exit(0);
			}
		}
	}
}

void MenuHandler::set_time(double time)
{
	time_ = time;
}

void MenuHandler::set_cooling_type(int cooling_type)
{
	cooling_type_ = cooling_type;
}

void MenuHandler::set_cooling_rate(double cooling_rate)
{
	cooling_rate_ = cooling_rate;
}

void MenuHandler::set_neighbour_type(int neighbour_type)
{
	neighbour_type_ = neighbour_type;
}

void MenuHandler::set_matrix(AdjacencyMatrix & matrix)
{
	matrix_ = matrix;
}

void MenuHandler::sa_parameters_menu()
{
	auto time{ 0.0 };
	auto cooling_rate{ 0.0 };
	auto choice{ 0 };

	while (choice != 3)
	{
		for (const auto &it : sa_parameters_)
			std::cout << it << "\n";
		
		std::cin >> choice;
		switch (choice)
		{
			case 1:
			{
				std::cin >> time;
				set_time(time);
				break;
			}
			case 2:
			{
				std::cin >> cooling_rate;
				set_cooling_rate(cooling_rate);
				break;
			}
			case 3:
			{
				clear_screen();
				break;
			}
			default:
			{
				break;
			}
		}
	}	
}

void MenuHandler::tabu_parameters_menu()
{
	auto time{ 0.0 };
	for (const auto &it : tabu_parametrs_)
		std::cout << it << "\n";
	std::cin >> time;
	set_time(time);
}

void MenuHandler::sa_cooling_menu()
{
	auto cooling_choice{ 0 };
	
	for (const auto &it : sa_cooling_)
		std::cout << it << "\n";
	std::cin >> cooling_choice;

	set_cooling_type(cooling_choice);
}

void MenuHandler::tabu_neighbours_menu()
{
	auto neighbour_type{ 0 };

	for (const auto &it : tabu_neighbours_)
		std::cout << it << "\n";
	std::cin >> neighbour_type;

	set_neighbour_type(neighbour_type);
}

void MenuHandler::clear_screen()
{
	#ifdef __linux__
    	system("clear");
	#elif _WIN32
    	system("CLS");
	#endif
}