#include <iostream>
#include "maze/maze.hpp"
#include <stack>
#include <queue>
int main(int nargs, char** vargs){

	maze::Maze laberinto(21,21);
	std::cout <<"Laberinto sin resolver:"<< std::endl;
	std::cout << std::endl;
	laberinto.print();
	std::cout << std::endl;
	std::cout << std::endl;
	Cords* ponter = laberinto.solve_pila(0,0,21,21);
	std::cout <<"Laberinto Solucion pila:"<< std::endl;
	std::cout << std::endl;
	laberinto.print_solved(ponter);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout <<"Laberinto Solucion cola:"<< std::endl;
	std::cout << std::endl;
	//laberinto.solve_cola(0,0,21,21);
	std::cout << std::endl;
	std::cout << std::endl;

	delete ponter;
	return 0;
}
