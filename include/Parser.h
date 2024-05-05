/*
 *this class is used to parse the input file and extract the data from it
 *We will use the three functions to parse the input file and extract the data from it
 *ïnside labyrinthe constructor
 */
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <sstream>
#include "Constants.h"
#include "Environnement.h"
#include <fstream>
#include <vector>
#include <iterator>

class Parser
{
public:
    Parser(){};
    ~Parser(){};

    void parse_assets(const std::vector<std::string> &input);
    void parse_maze(const std::vector<std::string> &input, int &_width, int &_height, char **&_data, Box &_treasor);
    void readMaze(std::ifstream &file, std::vector<std::string> &assets, std::vector<std::string> &maze);
};

#endif // PARSER_H
