/* This class is responsible for filling the labyrinth with the elements such as walls, posters, boxes, guards, and marks. 
It also contains the logic for placing the elements in the labyrinth. It is a helper class for the Labyrinthe class. */


#include "../include/LabyrintheFiller.h"


bool isWall(char cell)
{
    return (cell == VERTICAL_WALL || cell == HORIZONTAL_WALL || cell == WALL_CELL || cell == AFFICHE1 || cell == AFFICHE2);
}

const char *getChoices()
{
    static const char *choices[] = {"Lezard", "Blade", "Serpent", "Samourai"};
    return choices[rand() % 3];
}

//function to place the vertical walls in the labyrinth
void LabyrintheFiller::placeWallVertical(Labyrinthe *lab, int *wallAlreadyPlaced)
{
    int _width = lab->width();
    int _height = lab->height();

    for (int i = 0; i < _width; i++)
    {
        int j = 0;
        while (j < _height)
        {
            if (lab->data(i, j) == WALL_CELL)
            {
                // Start of a wall
                lab->_walls[*wallAlreadyPlaced]._x1 = i;
                lab->_walls[*wallAlreadyPlaced]._y1 = j;
                lab->_walls[*wallAlreadyPlaced]._ntex = 0;

                // Skip the rest of the wall
                while (j < _height && isWall(lab->data(i, j)))
                {
                    j++;
                }

                // End of a wall
                lab->_walls[*wallAlreadyPlaced]._x2 = i;
                lab->_walls[*wallAlreadyPlaced]._y2 = j - 1;

                (*wallAlreadyPlaced)++; // Increment the wall count
            }
            else
            {
                j++;
            }
        }
    }
}


//function to place the horizontal walls in the labyrinth
void LabyrintheFiller::placeWallHorizontal(Labyrinthe *lab, int *wallAlreadyPlaced)
{
    int _width = lab->width();
    int _height = lab->height();

    for (int j = 0; j < _height; j++)
    {
        int i = 0;
        while (i < _width)
        {
            if (lab->data(i, j) == WALL_CELL)
            {
                // Start of a wall
                lab->_walls[*wallAlreadyPlaced]._x1 = i;
                lab->_walls[*wallAlreadyPlaced]._y1 = j;
                lab->_walls[*wallAlreadyPlaced]._ntex = 0;

                // Skip the rest of the wall
                while (i < _width && isWall(lab->data(i, j)))
                {
                    i++;
                }

                // End of a wall
                lab->_walls[*wallAlreadyPlaced]._x2 = i - 1;
                lab->_walls[*wallAlreadyPlaced]._y2 = j;

                (*wallAlreadyPlaced)++; // Increment the wall count
            }
            else
            {
                i++;
            }
        }
    }
}


//function to place the posters on the vertical walls in the labyrinth
void LabyrintheFiller::placePosterVertical(Labyrinthe *lab, int i, int j, int k)
{
    if (lab->data(i, j + 1) == WALL_CELL)
    {
        // Place before
        lab->_picts[k]._y1 = j - 2;
        lab->_picts[k]._y2 = j;
    }
    else
    {
        lab->_picts[k]._y1 = j + 2;
        lab->_picts[k]._y2 = j;
    }
    lab->_picts[k]._x1 = i;
    lab->_picts[k]._x2 = i;
    char tmp[128];
    if (lab->data(i, j) == AFFICHE1)
        sprintf(tmp, "%s/%s", lab->texture_dir, "affiche.jpg");
    else
        sprintf(tmp, "%s/%s", lab->texture_dir, "voiture.jpg");

    lab->_picts[k]._ntex = lab->wall_texture(tmp);
}


//function to place the posters on the horizontal walls in the labyrinth
void LabyrintheFiller::placePosterHorizontal(Labyrinthe *lab, int i, int j, int k)
{

    if (lab->data(i + 1, j) == WALL_CELL)
    {
        // Place before
        lab->_picts[k]._x1 = i - 2;
        lab->_picts[k]._x2 = i;
    }
    else
    {

        lab->_picts[k]._x1 = i;
        lab->_picts[k]._x2 = i + 2;
    }
    lab->_picts[k]._y1 = j;
    lab->_picts[k]._y2 = j;
    char tmp[128];
    if (lab->data(i, j) == AFFICHE1)
        sprintf(tmp, "%s/%s", lab->texture_dir, "affiche.jpg");
    else
        sprintf(tmp, "%s/%s", lab->texture_dir, "voiture.jpg");

    lab->_picts[k]._ntex = lab->wall_texture(tmp);
}

//function to place the posters on the walls in the labyrinth
void LabyrintheFiller::placePicts(Labyrinthe *lab)
{
    int _width = lab->width();
    int _height = lab->height();

    int i = 0;
    int j = 0;
    int k = 0;

    for (j = 0; j < _height; j++)
    {
        for (i = 0; i < _width; i++)
        {
            if (lab->data(i, j) == AFFICHE1 || lab->data(i, j) == AFFICHE2)
            {
                if (lab->data(i, j + 1) == VERTICAL_WALL || lab->data(i, j + 1) == WALL_CELL)
                    placePosterVertical(lab, i, j, k);
                if (lab->data(i + 1, j) == HORIZONTAL_WALL || lab->data(i + 1, j) == WALL_CELL)
                    placePosterHorizontal(lab, i, j, k);
                k++;
            }
        }
    }
}

//function to place the boxes in the labyrinth
void LabyrintheFiller::placeBoxes(Labyrinthe *lab)
{
    int boxAlreadyPlaced = HEALTH_BOX;
    int _width = lab->width();
    int _height = lab->height();

    for (int i = 0; i < _height; i++)
    {
        int j = 0;

        while (j < _width)
        {
            if (lab->data(j, i) == BOX_CELL)
            {
                // Start of a box

                lab->_boxes[boxAlreadyPlaced]._x = j;
                lab->_boxes[boxAlreadyPlaced]._y = i;
                char tmp3[128];
                sprintf(tmp3, "%s/%s", lab->texture_dir, "caisse.jpg");
                lab->_boxes[boxAlreadyPlaced]._ntex = lab->wall_texture(tmp3);

                j++;

                boxAlreadyPlaced++;
            }

            else
            {
                j++;
            }
        }
    }
}

//function to place the health boxes in the labyrinth
void LabyrintheFiller::placeHealthBoxes(Labyrinthe *lab)
{
    int boxAlreadyPlaced = 0;
    int _width = lab->width();
    int _height = lab->height();

    for (int i = 0; i < _height; i++)
    {
        int j = 0;

        while (j < _width)
        {
            if (lab->data(j, i) == HEALTH_BOX_CELL)
            {
                lab->_boxes[boxAlreadyPlaced]._x = j;
                lab->_boxes[boxAlreadyPlaced]._y = i;
                char tmp3[128];
                sprintf(tmp3, "%s/%s", lab->texture_dir, "boite-2.jpg");
                lab->_boxes[boxAlreadyPlaced]._ntex = lab->wall_texture(tmp3);


                j++;

                boxAlreadyPlaced++;
            }
            else
            {
                j++;
            }
        }
    }
}

//function to place the guards in the labyrinth
void LabyrintheFiller::placeGuards(Labyrinthe *lab, int scale)
{
    int _width = lab->width();
    int _height = lab->height();

    int i = 0;
    int j = 0;
    int k = 1;

    for (i = 0; i < _width; i++)
    {
        for (j = 0; j < _height; j++)
        {
            if (lab->data(i, j) == CHASSEUR)
            {
                lab->_guards[0] = new Chasseur(lab);
                lab->_guards[0]->_x = i * scale;
                lab->_guards[0]->_y = j * scale;

                // _data[i][j] = EMPTY_CELL;
            }
            if (lab->data(i, j) == GUARDIAN)
            {

                lab->_guards[k] = new Gardien(lab, getChoices());
                lab->_guards[k]->_x = i * scale;
                lab->_guards[k]->_y = j * scale;

                // _data[i][j] = EMPTY_CELL;
                k++;
            }
        }
    }
}


//function to place the marks in the labyrinth
void LabyrintheFiller::placeMark(Labyrinthe *lab)
{
    int _width = lab->width();
    int _height = lab->height();

    int i = 0;
    int j = 0;
    int flag = 0;
    for (i = 0; i < _width; i++)
    {
        for (j = 0; j < _height; j++)
        {
            if (lab->data(i, j) == MARK_CELL)
            {
                if (flag == 0)
                {
                    lab->_marks[0]._x = i;
                    lab->_marks[0]._y = j;
                    char tmp3[128];
                    sprintf(tmp3, "%s/%s", lab->texture_dir, "p3.gif");
                    lab->_marks[0]._ntex = lab->wall_texture(tmp3);
                    flag = 1;
                }
                else
                {
                    lab->_marks[1]._x = i;
                    lab->_marks[1]._y = j;
                    char tmp3[128];
                    sprintf(tmp3, "%s/%s", lab->texture_dir, "p4.gif");

                    lab->_marks[1]._ntex = lab->wall_texture(tmp3);
                    break;
                }
            }
        }
    }
}