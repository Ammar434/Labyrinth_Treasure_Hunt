// This class is a helper class to help fill the labyrinth
// We will call the all the function of this class inside Labyrinthe constructor

#ifndef LABYRINTHE_FILLER_H
#define LABYRINTHE_FILLER_H

#include "Labyrinthe.h"
#include "../include/Chasseur.h"
#include "../include/Gardien.h"
#include "../include/Environnement.h"

class LabyrintheFiller
{
public:
    // This function will place the vertical walls in the labyrinthe
    static void placeWallVertical(Labyrinthe *lab, int *wallAlreadyPlaced);

    // This function will place the horizontal walls in the labyrinthe
    static void placeWallHorizontal(Labyrinthe *lab, int *wallAlreadyPlaced);

    // This function will place the posters in the labyrinthe
    static void placePicts(Labyrinthe *lab);

    // This function will place the boxes in the labyrinthe
    static void placeBoxes(Labyrinthe *lab);

    // This function will place the health boxes in the labyrinthe
    static void placeHealthBoxes(Labyrinthe *lab);

    // This function will place the guardians in the labyrinthe
    static void placeGuards(Labyrinthe *lab, int scale);

    // This function will place the marks in the labyrinthe
    static void placeMark(Labyrinthe *lab);

    // This function will place the horizontal posters in the labyrinthe
    static void placePosterHorizontal(Labyrinthe *lab, int i, int j, int k);

    // This function will place the vertical posters in the labyrinthe
    static void placePosterVertical(Labyrinthe *lab, int i, int j, int k);
};

#endif