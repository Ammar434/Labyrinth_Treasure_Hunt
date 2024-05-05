/* This file is the header file for the Gardien class. It contains the declaration of the Gardien class.
*/


#ifndef GARDIEN_H
#define GARDIEN_H

#include "Mover.h"
#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include "Constants.h"
#include "Helper.h"
#include <chrono>

extern int chasseur_health;

using namespace std::chrono;

class Labyrinthe;

class Gardien : public Mover
{
private:
	int _health = LIFE_GUARD; // health of the guardian
	bool _fireball_active; // is the fireball active
	int min_fire_distance; // min distance to fire
	float last_chasseur_x = 0; // last chasseur x position
	float last_chasseur_y = 0; // last chasseur y position

	float has_LOS = 0; // if the Gardien has line of sight to the chasseur
	bool isKnockout = false; // if the Gardien is knockout
	int successive_hit = 0; // number of successive hit

	float moving_angle = 0; // angle of the guardian
	float patrol_angle = 0; // angle of the guardian when patrolling

	steady_clock::time_point last_shot; // last time the guardian shot
	steady_clock::time_point last_time_being_hit; // last time the guardian was hit
	float dmax2; // max distance of the labyrinthe

public:
	static Sound *_hunter_fire; // sound of the hunter's weapon.
	static Sound *_hunter_hit;	// cry of the guard touched.
	static Sound *_wall_hit;	// we hit a wall.

	Gardien(Labyrinthe *l, const char *modele) : Mover(120, 80, l, modele)
	{
		last_shot = std::chrono::steady_clock::now();

		// Random value so each guardian can fire at different min distance
		min_fire_distance = 30 - rand() % 10;

		// We compute the max distance of the labyrinthe only one time
		// instead of computing at each fireball proccess
		dmax2 = (_l->width()) * (_l->width()) + (_l->height()) * (_l->height());
		_fireball_active = false;
		_hunter_fire = new Sound("sons/hunter_fire.wav"); // sound of the hunter's weapon.
		_hunter_hit = new Sound("sons/hunter_hit.wav");  // cry of the hunter touched.
		if (_wall_hit == 0)
			_wall_hit = new Sound("sons/hit_wall.wav"); // we hit a wall.
	}

	// my guardian thinks very badly!
	void update(void) override; // update the guardian

	void try_attack(); // try to attack the chasseur
	bool move_aux(double dx, double dy); // move the guardian
	bool move(double dx, double dy) override 
	{

		return move_aux(dx, dy) || move_aux(dx, 0.0) || move_aux(0.0, dy);
		return false;
	}

	// shoot the chasseur
	void fire(int angle_vertical) override
	{
		float chasseur_x = _l->_guards[0]->_x;
		float chasseur_y = _l->_guards[0]->_y;

		float dx = (chasseur_x - _x);
		float dy = (chasseur_y - _y);

		double angle_horizontal = atan2(dx, dy) * (180 / M_PI);
		if (_fb && !_fireball_active)
		{
			_fb->init(/* position initiale de la boule */ _x, _y, 10.,
					  /* angles de visee */ angle_vertical, angle_horizontal);
			_fireball_active = true;
		}
	}

	bool process_fireball(float dx, float dy) override; // process the fireball
	bool can_move_fireball(float delta_x, float delta_y); // can move the fireball
	void handle_collision(float dist2, bool chasseur_hit); // handle the collision
	void patrol(); // patrol the guardian
	bool isChasseurHit(); // if the chasseur is hit
	void getDamage(); // get damage from the chasseur
	float errorRateBasedOnLife(); // error rate based on life of the guardian
};

#endif