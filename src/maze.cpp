#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <queue>

namespace maze{

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = '-';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;
Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH;
	dir[1] = SOUTH;
	dir[2] = EAST;
	dir[3] = WEST;
	std::srand(time(0));
	generate_maze(h, w);

}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width= w;
	grid = new uchar*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new uchar[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	 }
}
bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){

	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);

		}
	}
}

void Maze::print(){
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0) {
				std::cout << EMPTY;
			}
			else {
				std::cout << WALL;
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}


void Maze::print_solved(Cords* solution){
	if (!solution[0].x){
		std::cout << " Laberinto sin solucion" << std::endl;
	}
	else{
		char LIMIT = '=';
		int is = 0;
		std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
		std::cout << " ";
		for (int j = 0; j < width; j++){
			std::cout << LIMIT;
		}
		std::cout << " ";
		std::cout << std::endl;
		for (int i = 0; i < height; i++){
			std::cout << "|";
			for (int j = 0; j < width; j++){
				if (grid[i][j] == 0) {
					is = 0;
					for (int k = 1; k < solution[0].x +1; k++){
						if (solution[k].y == i){
							if (solution[k].x == j){
								is = 1;
							}
						}
					}
					if (is){
						std::cout << "x";
					}
					else {
						std::cout << EMPTY;
					}
				}
				else {
					std::cout << WALL;
				}
			}
			std::cout << "|";
			std::cout << std::endl;
		}
		std::cout << " ";
		for (int j = 0; j < width; j++){
			std::cout << LIMIT;
		}
		std::cout << " ";
		std::cout << std::endl;
	}

}

Cords* Maze::solve_cola(int f1, int c1, int f2, int c2){
	
	return 0;
}

Cords* Maze::solve_pila(int f1, int c1, int f2, int c2){
	std::stack<Cords> pila_solucion;
	int finish = 1;
	int counter = 0;
	int counter_ran;
	int counter_ran2;
	int random;
	int visitado;
	int revisados[4];
	int total = height*width;

	Cords cordenada_actual;
	cordenada_actual.x = f1;
  	cordenada_actual.y = c1;

	Cords cordenada_revisar;
	cordenada_revisar.x = -1;
  	cordenada_revisar.y = -1;

	Cords visitados[total];
	for (int i=0;i<total;i++){
		visitados[i] = cordenada_revisar;
	}

	while(finish){
		//revisa que no sea el final
		if (cordenada_actual.x == f2-1 && cordenada_actual.y == c2-1){
			visitados[counter] = cordenada_actual;
			pila_solucion.push(cordenada_actual);
			finish = 0;
		}

		else{
			revisados[0] = 0;
			revisados[1] = 0;
			revisados[2] = 0;
			revisados[3] = 0;

			//revisa que sea un nodo nuevo
			visitado = 0;
			for (int i=0;i<total;i++){
				if (visitados[i].x == cordenada_actual.x && visitados[i].y == cordenada_actual.y){
					visitado = 1;
				}
			}
			if (visitado == 0){
				visitados[counter] = cordenada_actual;
				pila_solucion.push(cordenada_actual);
			}

			//revisa si las cordenadas adjacentes son empty y no esten revisadas
			if (cordenada_actual.x > 0){
				cordenada_revisar.x = cordenada_actual.x - 1;
				cordenada_revisar.y = cordenada_actual.y;
				if (grid[cordenada_revisar.y][cordenada_revisar.x] == 0) {
					visitado = 0;
					for (int i=0;i<total;i++){
						if (visitados[i].x == cordenada_revisar.x && visitados[i].y == cordenada_revisar.y){
							visitado = 1;
						}
					}
					if (visitado == 0){
						revisados[0] = 1;
					}
				}
			}

			if (cordenada_actual.x < width - 1){
				cordenada_revisar.x = cordenada_actual.x + 1;
				cordenada_revisar.y = cordenada_actual.y;
				if (grid[cordenada_revisar.y][cordenada_revisar.x] == 0) {
					visitado = 0;
					for (int i=0;i<total;i++){
						if (visitados[i].x == cordenada_revisar.x && visitados[i].y == cordenada_revisar.y){
							visitado = 1;
						}
					}
					if (visitado == 0){
						revisados[1] = 1;
					}
				}
			}

			if (cordenada_actual.y > 0){
				cordenada_revisar.x = cordenada_actual.x;
				cordenada_revisar.y = cordenada_actual.y - 1;
				if (grid[cordenada_revisar.y][cordenada_revisar.x] == 0) {
					visitado = 0;
					for (int i=0;i<total;i++){
						if (visitados[i].x == cordenada_revisar.x && visitados[i].y == cordenada_revisar.y){
							visitado = 1;
						}
					}
					if (visitado == 0){
						revisados[2] = 1;
					}
				}
			}

			if (cordenada_actual.y < height - 1){
				cordenada_revisar.x = cordenada_actual.x;
				cordenada_revisar.y = cordenada_actual.y + 1;
				if (grid[cordenada_revisar.y][cordenada_revisar.x] == 0) {
					visitado = 0;
					for (int i=0;i<total;i++){
						if (visitados[i].x == cordenada_revisar.x && visitados[i].y == cordenada_revisar.y){
							visitado = 1;
						}
					}
					if (visitado == 0){
						revisados[3] = 1;
					}
				}
			}

			// ejecuta si alguna coordenada adjacente esta empty y no revisada, y elige aleatoriamente uno de los adjacentes
			if (revisados[0] == 1 || revisados[1] == 1 || revisados[2] == 1 || revisados[3] == 1){
				counter_ran = -1;
				for (int i = 0; i < 4; i++){
					if (revisados[i] == 1){
						counter_ran ++;
					}
	 			}
				random = std::rand() & counter_ran;
				random ++;
				counter_ran2 = 0;
				for (int i = 0; i < 4; i++){
					if (revisados[i] == 1){
						counter_ran2 ++;
						if(counter_ran2 == random){
							if(i == 0){
								cordenada_actual.x = cordenada_actual.x - 1;
							}
							else if(i == 1){
								cordenada_actual.x = cordenada_actual.x + 1;
							}
							else if(i == 2){
								cordenada_actual.y = cordenada_actual.y - 1;
							}
							else{
								cordenada_actual.y = cordenada_actual.y + 1;
							}
						}
					}
	 			}

			}
			
			// popea porque esta en un lugar sin salida
			else {
				pila_solucion.pop();
				if (pila_solucion.empty()){
					finish = 0;
				}
				else{
					cordenada_actual = pila_solucion.top();
				}
			}

			counter ++;
		}
	}

	int sizec = pila_solucion.size();
    Cords* respuesta = new Cords[sizec + 1];
	cordenada_actual.x = sizec;
	respuesta[0] = cordenada_actual;
    for (int i = 1; i< sizec+1; i++){
        respuesta[i] = pila_solucion.top();
        pila_solucion.pop();
    }

	return respuesta;
}
}