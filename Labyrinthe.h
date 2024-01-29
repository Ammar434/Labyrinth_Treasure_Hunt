#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Environnement.h"
#include <vector>
#include <string>

class Labyrinthe : public Environnement
{
private:
	int _width;
	int _height;
	char **_data;

	void parse_maze(const std::vector<std::string> &);

public:
	Labyrinthe(char *);
	~Labyrinthe();
	int width() { return _width; }	 // retourne la largeur du labyrinthe.
	int height() { return _height; } // retourne la longueur du labyrinthe.
	char data(int i, int j)
	{
		return _data[i][j];
	} // retourne la case (i, j).
};

#endif