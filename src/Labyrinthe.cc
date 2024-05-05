/* This class encapsulates all the functionalities related to managing and manipulating the labyrinth environment, 
including parsing, placing elements, accessing data, and printing the labyrinth layout. */


#include "../include/Labyrinthe.h"
#include "../include/Chasseur.h"
#include "../include/Gardien.h"
#include "../include/LabyrintheFiller.h"

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string.h>

Sound *Chasseur::_guard_fire; // sound of the guard's weapon.
Sound *Chasseur::_guard_hit;  // cry of the guard touched.
Sound *Chasseur::_wall_hit;	  // we hit a wall.
Sound *Gardien::_hunter_fire; // sound of the hunter's weapon.
Sound *Gardien::_hunter_hit; // cry of the hunter touched.
Sound *Gardien::_wall_hit; // we hit a wall.

/* So that the interface can call the constructor of the Labyrinth class without having the sources... */
Environnement *Environnement::init(char *filename)
{
	return new Labyrinthe(filename);
}

//Labirynthe constructor
Labyrinthe::Labyrinthe(char *filename)
{

	srand(static_cast<unsigned int>(time(NULL)));

	// First we will parse the file to get the maze structure
	parseFile(filename);

	// Then we will count the number of each elements guards,walls...
	// to avoid unnecessary memory allocation
	countElements();

	_walls = new Wall[_nwall]; // We allocate the memory for the walls
	_guards = new Mover *[_nguards]; // We allocate the memory for the guards
	_boxes = new Box[_nboxes]; // We allocate the memory for the boxes
	_picts = new Wall[_npicts]; // We allocate the memory for the posters
	_marks = new Box[_nmarks]; // We allocate the memory for the marks

	// Finally we will place the elements in the maze
	placeElements();
}

/*
 * Parse the file to get the maze structure
 */
void Labyrinthe::parseFile(const char *filename)
{
	std::vector<std::string> assets, maze;
	std::ifstream file(filename);

	_parser.readMaze(file, assets, maze);
	_parser.parse_assets(assets);
	_parser.parse_maze(maze, _width, _height, _data, _treasor);
}
/*
 * Count the number of each elements guards,walls...
 */
void Labyrinthe::countElements()
{
	_nwall = LabyrinthCounter::countWallVertical(_data, _width, _height);
	_nwall += LabyrinthCounter::countWallHorizontal(_data, _width, _height);

	_nguards = LabyrinthCounter::countGuardians(_data, _width, _height);

	_nboxes = LabyrinthCounter::countBoxes(_data, _width, _height);

	_npicts = LabyrinthCounter::countPosters(_data, _width, _height);

	_nmarks = 2;
}

/*
 * Place the elements in the maze
 */
void Labyrinthe::placeElements()
{
	int wallAlreadyPlaced = 0;
	// We place health box first so we know the position of the health box
	//  inside box array we do that so we dont modify Mover.h
	// We will assume that we only have two health box
	LabyrintheFiller::placeHealthBoxes(this);
	LabyrintheFiller::placeBoxes(this);
	LabyrintheFiller::placeWallHorizontal(this, &wallAlreadyPlaced);
	LabyrintheFiller::placeWallVertical(this, &wallAlreadyPlaced);
	LabyrintheFiller::placeGuards(this, Environnement::scale);
	LabyrintheFiller::placePicts(this);
	LabyrintheFiller::placeMark(this);

	// delete guard from data
	// We delete the guard so we avoid invisible collision when the guard is moving
	// A better way to do it will be to update the data array by adding a setter
	// inside Environnement class
	for (int i = 0; i < _nguards; i++)
	{
		int x = _guards[i]->_x / Environnement::scale;
		int y = _guards[i]->_y / Environnement::scale;

		_data[x][y] = EMPTY_CELL;
	}
}

/*
 *Destructeur
 */
Labyrinthe::~Labyrinthe()
{
	// Deallocate maze data
	for (int i = 0; i < this->_height; ++i)
		delete[] _data[i];
	delete[] _data;

	for (int i = 0; i < this->_nguards; ++i)
		delete[] this->_guards[i];
	delete[] this->_guards;

	delete[] this->_walls;
	delete[] this->_picts;
	delete[] this->_boxes;
	delete[] this->_marks;
}