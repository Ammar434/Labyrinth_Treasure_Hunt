/* This is just a header file that contains the declaration of the Labyrinthe class.
*/

#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Environnement.h"
#include <vector>
#include <string>
#include <iostream>
#include "Parser.h"
#include "LabyrinthCounter.h"

class Labyrinthe : public Environnement
{

private:
	int _width;
	int _height;
	char **_data;

	Parser _parser;

public:
	Labyrinthe(char *);
	Labyrinthe(int width, int height, char **data)
		: _width(width), _height(height), _data(data) {}

	void parseFile(const char *filename);
	void countElements(); // Count the number of elements in the labyrinth
	void placeElements(); // Place the elements in the labyrinth

	void placePosterHorizontal(int i, int j, int k); // Place the posters on the horizontal walls in the labyrinth
	void placePosterVertical(int i, int j, int k);  // Place the posters on the vertical walls in the labyrinth
	void placeGuards(); // Place the guards in the labyrinth
	void placeMark(); // Place the mark in the labyrinth

	~Labyrinthe(); // Destructor

	int width() { return _width; }	 // retourne la largeur du labyrinthe.
	int height() { return _height; } // retourne la longueur du labyrinthe.

	char data(int i, int j)
	{
		return _data[i][j];
	} // retourne la case (i, j).

	void print_maze()
	{
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				std::cout << _data[x][y];
			}
			std::cout << std::endl;
		}
	};
};

#endif