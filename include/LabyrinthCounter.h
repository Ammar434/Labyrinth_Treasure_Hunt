// This class is just a helper class that will help to count the
// number of walls, guardians, boxes and posters in the labyrinthe.
// We will use this all the functions in this class to allocate only the necessary items

#include "Constants.h"

class LabyrinthCounter
{
public:
    // This function will count the number of walls in the labyrinthe the number of walls in the labyrinthe
    static int countWallVertical(char **_data, int _width, int _height)
    {
        int _nwall = 0;
        for (int i = 0; i < _width; i++)
        {
            int j = 0;
            while (j < _height)
            {
                if (_data[i][j] == WALL_CELL)
                {
                    // Start of a wall
                    j++;

                    // Skip the rest of the wall
                    while (j < _height && (_data[i][j] == VERTICAL_WALL || _data[i][j] == WALL_CELL || _data[i][j] == AFFICHE1 || _data[i][j] == AFFICHE2))
                    {
                        j++;
                    }

                    _nwall++; // Increment the wall count
                }
                else
                {
                    j++;
                }
            }
        }
        return _nwall;
    }

    // This function will count the number of guardians in the labyrinthe
    static int countGuardians(char **_data, int _width, int _height)
    {
        int _nguards = 0;
        for (int i = 0; i < _width; i++)
        {
            for (int j = 0; j < _height; j++)
            {
                if (_data[i][j] == GUARDIAN || _data[i][j] == CHASSEUR)
                {
                    _nguards++;
                }
            }
        }
        return _nguards;
    }

    // This function will count the number of horizontal walls in the labyrinthe
    static int countWallHorizontal(char **_data, int _width, int _height)
    {
        int _nwall = 0;
        for (int i = 0; i < _height; i++)
        {
            int j = 0;

            while (j < _width)
            {
                if (_data[j][i] == WALL_CELL)
                {
                    // Start of a wall

                    j++;

                    // Skip the rest of the wall
                    while (j < _width && (_data[j][i] == HORIZONTAL_WALL || _data[j][i] == WALL_CELL || _data[j][i] == AFFICHE1 || _data[j][i] == AFFICHE2))
                    {
                        j++;
                    }
                    _nwall++; // Increment the wall count
                }
                else
                {
                    j++;
                }
            }
        }
        return _nwall;
    }

    // This function will count the number of boxes(regular and health boxes) in the labyrinthe
    static int countBoxes(char **_data, int _width, int _height)
    {
        int _nboxes = 0;
        for (int i = 0; i < _height; i++)
        {
            int j = 0;

            while (j < _width)
            {
                if (_data[j][i] == BOX_CELL || _data[j][i] == HEALTH_BOX_CELL)
                {
                    // Start of a box
                    j++;
                    _nboxes++;
                }
                else
                {
                    j++;
                }
            }
        }
        return _nboxes;
    }

    // This function will count the number of posters in the labyrinthe
    static int countPosters(char **_data, int _width, int _height)
    {
        int _npicts = 0;
        for (int i = 0; i < _height; i++)
        {
            int j = 0;

            while (j < _width)
            {
                if (_data[j][i] == AFFICHE1 || _data[j][i] == AFFICHE2)
                {
                    // Start of a poster

                    j++;

                    // Skip the rest of the poster
                    while (j < _width && (_data[j][i] == AFFICHE1 || _data[j][i] == AFFICHE2))
                    {
                        j++;
                    }
                    _npicts++; // Increment the poster count
                }
                else
                {
                    j++;
                }
            }
        }
        return _npicts;
    }
};