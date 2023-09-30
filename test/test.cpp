#include <iostream>
#include "maze/maze.hpp"
#include <stack>
#include <queue>
int main(int nargs, char** vargs){

	maze::Maze laberinto(21,21);
	laberinto.print();
	Cords* ponter = laberinto.solve_pila(0,0,21,21);
	for (int i= 0; i< 20; i++){
	std::cout << ponter[i].x << "," << ponter[i].y << std::endl;
	}
	laberinto.print_solved(ponter);
	laberinto.solve_cola(0,0,21,21);


	delete ponter;
	return 0;
}
