#ifndef MOVER_H
#define MOVER_H

class Labyrinthe; // la (future) votre

#include "FireBall.h"
#include "Environnement.h"

class Mover
{
private:
	static void *init(const char *); // initialise le mod�le md2.
public:
	Environnement *_l; // the labyrinth in which he evolves.
	FireBall *_fb;	   // his fireball.
	float _x, _y;	   // position.
	int _angle;		   // movement/shooting angle.
	void *_model;	   // the graphic model.

	Mover(int x, int y, Labyrinthe *l, const char *modele) : _l((Environnement *)l), _fb(0), _x((float)x), _y((float)y),
															 _angle(0)
	{
		_model = init(modele);
	}
	virtual ~Mover() {}
	void tomber();				   // makes a character (guardian) fall and get up
	void rester_au_sol();		   // causes a character (guardian) to fall and leave him on the ground.
	virtual void update(void) = 0; // makes the character (guardian) 'think'.
	// makes the character's fireball move.
	virtual bool process_fireball(float dx, float dy) = 0;
	// tries to move the character from <dx,dy>.
	virtual bool move(double dx, double dy) = 0;
	// makes the character shoot an enemy (you can ignore the vertical angle).
	virtual void fire(int angle_vertical) = 0;
	// called for guardian 0 (hunter) when the user right-clicks;
	// shift (control) is true if the shift (control) key is pressed.
	virtual void right_click(bool shift, bool control) {}
};

#endif
