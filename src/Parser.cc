/* This class is responsible for parsing the input file and extracting the assets and the maze. 
It is a helper class for the Labyrinthe class.
*/

#include "../include/Parser.h"

//function to parse the assets from the input file
void Parser::parse_assets(const std::vector<std::string> &input)
{
    for (const auto &line : input)
    {
        // Skip comments and empty lines
        auto comment = line.find('#');
        if (comment != std::string::npos || line.empty())
            continue;

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(tokens));
    }
}

//function to parse the maze from the input file
void Parser::parse_maze(const std::vector<std::string> &input, int &_width, int &_height, char **&_data, Box &_treasor)
{
    _height = input.size();
    _width = 0;
    for (const auto &line : input)
    {
        _width = std::max(static_cast<unsigned int>(line.length()), static_cast<unsigned int>(_width));
    }

    _data = new char *[_width];
    for (int i = 0; i < _width; ++i)
    {
        _data[i] = new char[_height];
    }

    for (int x = 0; x < _width; x++)
    {
        for (int y = 0; y < _height; y++)
        {
            if (x < input[y].length())
            {
                _data[x][y] = input[y][x];
                if (input[y][x] == 'T')
                {
                    _treasor._x = x;
                    _treasor._y = y;
                }
            }
            else
            {
                _data[x][y] = WALL_FILLER;
            }
        }
    }
}


//function to read the input file
void Parser::readMaze(std::ifstream &file, std::vector<std::string> &assets, std::vector<std::string> &maze)
{
    if (!file.is_open())
    {
        // message("Error! File cannot be opened");
        return;
    }

    std::string line;
    bool isAsset = true;
    while (std::getline(file, line))
    {
        if (isAsset && line.find('+') != std::string::npos)
            isAsset = false;

        if (isAsset)
            assets.push_back(line);
        else
            maze.push_back(line);
    }
    file.close();
    // message("Read %d asset lines, %d maze lines, first line: %s", assets.size(), maze.size(), maze[0].c_str());
}