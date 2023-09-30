#include <iostream>
#include "maze/maze.hpp"
int main(int nargs, char** vargs){
	maze::Maze laberinto(21,21);
	laberinto.print();
	laberinto.solve_pila(0,0,21,21);
	laberinto.solve_cola(0,0,21,21);

	return 0;
}
