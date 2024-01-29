#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unistd.h> // TODO: remove, only for sleep function
#include <iterator>
#include <iostream>
#include <string.h>

Sound *Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound *Chasseur::_hunter_hit;  // cri du chasseur touch�.
Sound *Chasseur::_wall_hit;	   // on a tap� un mur.

/*
 *	Pour que l'interface puisse appeler le constucteur de
 *	la classe Labyrinthe sans en avoir les sources...
 */

Environnement *Environnement::init(char *filename)
{

	return new Labyrinthe(filename);
}

/*
 *	EXEMPLE de labyrinthe � taille fixe.
 */

void parse_assets(const std::vector<std::string> &input)
{
	// Iterate over input lines ignoring everything after # sign
	for (std::string line : input)
	{
		// Skip comments
		auto comment = line.find('#');
		if (comment != std::string::npos)
			line = line.substr(0, comment);

		// Skip empty lines
		if (line.empty())
			continue;

		// Split line into tokens
		std::istringstream iss(line);
		std::vector<std::string> tokens;
		std::copy(std::istream_iterator<std::string>(iss),
				  std::istream_iterator<std::string>(),
				  std::back_inserter(tokens));

		// Parse tokens
		message("%s", tokens[0].c_str());
		// sleep(2);
	}
}

void Labyrinthe::parse_maze(const std::vector<std::string> &input)
{
	// Find the size of the maze
	_height = input.size();
	unsigned int w = 0;

	for (std::string line : input)
	{
		w = std::max((unsigned int)line.length(), w);
	}

	// Initialize the maze data
	_width = w;

	// Create new array of size height and width

	_data = new char *[height()];

	for (int x = 0; x < height(); x++)
	{
		_data[x] = new char[width()];
	}

	// Copy data to maze definition array
	for (int x = 0; x < height(); x++)
	{
		// Copy the line contents
		for (int y = 0; y < width(); y++)
		{
			if (input[x][y] == ' ')
				_data[x][y] = EMPTY;
			else
				_data[x][y] = input[x][y];
		}
		// Fill out the missing elements with ' '
		for (int y = input[x].length(); y < width(); y++)
		{
			_data[x][y] = '@';
		}
	}
}

int countNumberOfWallHorizontal(std::string s1)
{
	int n = 0;
	size_t i = 0;
	int wallSize = 0;
	for (i = 0; i < s1.size(); i++)
	{
		if (s1[i] == '+')
		{
			wallSize++;
			i++;
			n++;
			while (i < s1.size())
			{
				wallSize++;

				if (s1[i] == '+' && s1[i + 1] != '-')
				{
					// std::cout << "Size " << wallSize << std::endl;
					wallSize = 0;
					i++;
					break;
				}
				i++;
			}
		}
	}
	// std::cout << "Size " << wallSize << std::endl;
	wallSize = 0;
	return n;
}

Labyrinthe::Labyrinthe(char *filename)
{
	std::vector<std::string> assets, maze;

	std::ifstream file(filename);
	// Read file into vector of strings
	if (file.is_open())
	{
		bool input_assets = true;
		std::string line;
		while (std::getline(file, line))
		{
			// Check if the line contains the maze definition
			if (input_assets && line.find('+') != std::string::npos)
				input_assets = false;

			// Add input line to appropriate vector
			if (input_assets)
				assets.push_back(line);
			else
				maze.push_back(line);
		}
		file.close();
		message("Read %d asset lines, %d maze lines, first line: %s", assets.size(), maze.size(), maze[0].c_str());
	}
	else
	{
		message("Error! File cannot be opened");
	}

	parse_maze(maze);

	for (int i = 0; i < height(); ++i)
	{
		// std::cout << "Checking for wall on line " << i << std::endl;
		_nwall += countNumberOfWallHorizontal(maze[i]);
		// printf("\n");
	}
	// for (int i = 0; i < height(); i++)
	// {
	// 	for (int j = 0; j < width(); j++)
	// 	{
	// 		std::cout << _data[i][j];
	// 	}
	// 	std::cout << std::endl;
	// }

	_walls = new Wall[_nwall];

	// Create wall
	for (int i = 0; i < height(); i++)
	{
		int j = 0;
		for (j = 0; j < width(); j++)
		{
			if (_data[i][j] == '+')
			{
				std::cout << "Wall begin X1=" << j << " Y1=" << i << ' ';

				while (j < strlen(_data[i]))
				{
					if (_data[i][j] == '+' && _data[i][j + 1] != '-' && _data[i][j + 1] != '@')
					{
						j++;
						break;
					}
					j++;
				}
			}
		}
		std::cout << "Wall stop X2=" << j << " Y2=" << i << '\n';
	}

	// _walls[0]._x1 = 0;
	// _walls[0]._y1 = 0;
	// _walls[0]._x2 = width() - 1;
	// _walls[0]._y2 = 0;
	// _walls[0]._ntex = 0;

	// First step get labyrinthe widht && height

	_nguards = 1;
	_npicts = 1;
	_nboxes = 1;
	_nmarks = 1;

	_picts = new Wall[_npicts];
	_boxes = new Box[_nboxes];
	_marks = new Box[_nmarks];

	_guards = new Mover *[_nguards];
	_guards[0] = new Chasseur(this);
}

Labyrinthe::~Labyrinthe()
{
	// Deallocate maze data
	for (int i = 0; i < this->_height; ++i)
		delete[] this->_data[i];
	delete[] this->_data;
}