/* This class is used to define the hunter's behavior and attributes. It contains the declaration of the Chasseur class.
*/

#ifndef CHASSEUR_H
#define CHASSEUR_H

#include <stdio.h>
#include "../include/Mover.h"
#include "../include/Sound.h"
#include "../include/Constants.h"
#include "Helper.h"
#include <chrono>

#include <iostream>
extern int chasseur_health;

class Labyrinthe;

class Chasseur : public Mover
{
private:
	bool move_aux(double dx, double dy); // move the hunter
	bool _fireball_active; // is the fireball active
	float dmax2; // max distance of the labyrinthe

	// We will use this variable to teleport after a certain amount of time only

public:
	// les sons.
	static Sound *_guard_fire; // sound of the guard's weapon.
	static Sound *_guard_hit;  // cry of the guard touched.
	static Sound *_wall_hit;   // we hit a wall.

	// constructeur.
	Chasseur(Labyrinthe *l);
	// only move in an empty square (we 'slide' along obstacles)
	bool move(double dx, double dy)
	{
		return move_aux(dx, dy) || move_aux(dx, 0.0) || move_aux(0.0, dy);
	}
	// le chasseur ne pense pas!
	void update(void){};
	// makes the fireball move (this is an example, it's up to you to deal with specific collisions...)
	bool process_fireball(float dx, float dy);
	bool isAGuardianHit(); // check if the guardian is hit
	// shoot an enemy.
	void fire(int angle_vertical);
	// right click.
	void right_click(bool shift, bool control);
	float errorRateBasedOnLife(); // error rate based on life of the hunter
};

#endif