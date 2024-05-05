#ifndef HELPER_H
#define HELPER_H
#include "math.h"
#include "Labyrinthe.h"
#include "Constants.h"
#include "Environnement.h"

/*
 * Calculate the distance between two points
 * @return the euclidian distance between the two points
 */
float calculateDistance(float x1, float y1, float x2, float y2);

/*
 * Will calculate the visible distance between a target and the guard position
 * Visible distance means no wall of box blocking the vision
 * @return the distance between the guard and the target
 */
float line_of_sight(float target_x, float target_y, float _x, float _y, int scale, Environnement *lab);

#endif // HELPER_H