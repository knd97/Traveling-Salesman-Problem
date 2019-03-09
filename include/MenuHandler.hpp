#ifndef MenuHandler_h_
#define MenuHandler_h_

#include <iostream>
#include <array>
#include <functional>
#include "NearestNeighbour.hpp"
#include "SimAnnealing.hpp"
#include "TabuSearch.hpp"

class MenuHandler
{
private:
	const std::array<std::string, 8> main_menu_options_{ "1 - Wybor pliku", "2 - Parametry do SW", "3 - Parametry do tabu search", 
		"4 - Wybor schladzania", "5 - Wybor sasiedztwa", "6 - Algorytm SW", "7 - Algorytm tabu serach", "8 - Wyjscie" };
	const std::array<std::string, 3> sa_parameters_{"1 - Prosze podac czas [s]", "2 - Wspolczynnik ochladzania", "3 - Powrot"};
	const std::array<std::string, 3> sa_cooling_{"1 - Schladzanie liniowe", "2 - Schladzanie logarytmiczne", "3 - Schladzanie wykladnicze"};
	const std::array<std::string, 1> tabu_parametrs_{ "1 - Prosze podac czas w [s]"};
	const std::array<std::string, 3> tabu_neighbours_{ "1 - Swap", "2 - Invert", "3 - Insert" };
	
	double time_;
	int cooling_type_;
	double cooling_rate_;
	int neighbour_type_;
	AdjacencyMatrix matrix_;
	FileHandler file_;

public:
	MenuHandler(FileHandler &file);
	
	void run_main_menu();
	
	~MenuHandler() = default;

private:
	void set_time(double time);
	void set_cooling_type(int cooling_type);
	void set_cooling_rate(double cooling_rate);
	void set_neighbour_type(int neighbour_type);
	void set_matrix(AdjacencyMatrix &matrix);

	void sa_parameters_menu();
	void tabu_parameters_menu();
	void sa_cooling_menu();
	void tabu_neighbours_menu();
	void clear_screen();
};
#endif // MenuHandler_h_

