/*
 * Constants.h
 * This file contains the constants used in the game
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

const char WALL_CELL = '+';
const char WALL_FILLER = '%';
const char VERTICAL_WALL = '|';
const char HORIZONTAL_WALL = '-';
const char AFFICHE1 = 'a';
const char AFFICHE2 = 'b';
const char GUARDIAN = 'G';
const char CHASSEUR = 'C';
const char MARK_CELL = 'M';
const char BOX_CELL = 'X';
const char HEALTH_BOX_CELL = 'H';

// Fireball HIT RADIUS that means the fireball will hit the chasseur
// if the chasseur is within the radius
const int HIT_RADIUS = 10;

// This constant is used to check how many seconds
// should we wait for a  knockout of the guardian
const int HIT_COOLDOWN = 2;

// This constant is used fixed the limit to start a knockout
const int SUCCESSIVE_HITS_LIMIT = 2;

const int HEALTH_BOX = 6;

const float PATROL_SPEED = 0.2;
const float TRACKING_SPEED = 0.5;

const int LIFE_HUNTER = 5;
const int LIFE_GUARD = 3;
#endif // CONSTANTS_H