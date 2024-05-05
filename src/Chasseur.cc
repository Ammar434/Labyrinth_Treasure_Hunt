/* This class is responsible for all the functionalities of the Chasseur.
It is reponsible for making the Chasseur move, update its health level, teleport, 
to make it fire (at a Gardien or wall), and to add an error to the accuracy of the hunter's attack 
on the gardien based on its health level.*/ 



#include "../include/Chasseur.h"

/* This function is called periodically to update the state of the Chasseur.
It is responsible for moving the Chasseur to a new position if the target position is unobstructed by walls or obstacles.
It also checks if the Chasseur is near a health box and increase the health of the Chasseur by 1. 
It also checks if the Chasseur is near a mark and teleport the Chasseur to the other mark if the Chasseur is near a mark.
It also is responsible for the winning condition of the game, which is when the Chasseur finds the treasure and is near it. */

bool Chasseur::move_aux(double dx, double dy)
{
	const int scale = Environnement::scale;

	int chasseur_next_x = static_cast<int>((_x + dx) / scale); // next x position of the chasseur
	int chasseur_next_y = static_cast<int>((_y + dy) / scale); // next y position of the chasseur

	// Check if we are near a health box
	for (int i = 0; i < HEALTH_BOX; i++)
	{
		if (calculateDistance(_l->_boxes[i]._x, _l->_boxes[i]._y, _x / scale, _y / scale) < 1)
		{
			_l->_boxes[i]._x = _l->height();
			_l->_boxes[i]._y = _l->height();
			chasseur_health++;
			message("Chasseur health increase by 1 health: %d ", chasseur_health);
		}
	}

	// Check if can teleport
	if (calculateDistance(_l->_marks[0]._x, _l->_marks[0]._y, _x / scale, _y / scale) < 1)
	{
		_x = (_l->_marks[1]._x + 1) * scale;
		_y = (_l->_marks[1]._y + 1) * scale;
		return true;
	}

	if (calculateDistance(_l->_marks[1]._x, _l->_marks[1]._y, _x / scale, _y / scale) < 1)
	{
		_x = (_l->_marks[0]._x + 1) * scale;
		_y = (_l->_marks[0]._y + 1) * scale;
		return true;
	}

	char next_cell = _l->data(chasseur_next_x, chasseur_next_y);
	if (next_cell == EMPTY_CELL || next_cell == MARK_CELL)
	{
		_x += dx;
		_y += dy;

		return true;
	}

	if (calculateDistance(_l->_treasor._x, _l->_treasor._y, _x / scale, _y / scale) < 1)
	{
		partie_terminee(true);
	}

	return false;
}

/*
 *	Chasseur Constructeur class
 */

Chasseur::Chasseur(Labyrinthe *l) : Mover(10, 10, l, 0)
{
	_fireball_active = false;

	// initialise les sons.
	_guard_fire = new Sound("sons/guard_fire.wav"); // sound of the guard's weapon.
	_guard_hit = new Sound("sons/guard_hit.wav");  // cry of the guard touched.
	if (_wall_hit == 0)
		_wall_hit = new Sound("sons/hit_wall.wav"); // we hit a wall.

	// We compute the max distance of the labyrinthe only one time
	//  instead of computing at each fireball proccess/
	dmax2 = (_l->width()) * (_l->width()) + (_l->height()) * (_l->height());
}

/* The following function is used to handle the collision of the fireball fired by the Chasseur with the Gardien or the wall.*/
bool Chasseur::process_fireball(float dx, float dy)
{
	// calculer la distance entre le chasseur et le lieu de l'explosion.
	float x = (_x - _fb->get_x()) / Environnement::scale; // position x du chasseur
	float y = (_y - _fb->get_y()) / Environnement::scale; // position y du chasseur
	float dist2 = x * x + y * y;
	// on bouge que dans le vide!
	char next_position = _l->data((int)((_fb->get_x() + dx) / Environnement::scale),
								  (int)((_fb->get_y() + dy) / Environnement::scale)); // next position of the fireball

	bool isGuardianHit = isAGuardianHit(); // check if the fireball hit the guardian
	message("guardian is hit %d", isGuardianHit);
	if ((EMPTY_CELL == next_position ||
		 MARK_CELL == next_position || BOX_CELL == next_position) &&
		isGuardianHit == false)
	{
		message("Woooshh ..... %d", (int)dist2);
		// il y a la place.
		return true;
	}
	// we init again the fireball to inflige dommage only one time
	_fb->init(0, 0, 0, 0, 0);

	// collision...
	if (isGuardianHit)
		_guard_hit->play(1.);
	else
	{
		// calculer la distance maximum en ligne droite.
		float dmax2 = (_l->width()) * (_l->width()) + (_l->height()) * (_l->height());
		// faire exploser la boule de feu avec un bruit fonction de la distance.
		_fireball_active = false;
		_wall_hit->play(1. - dist2 / dmax2);
	}

	return false;
}

/* The following function is used to check if the fireball fired by the Chasseur hits the Gardien or not. */

bool Chasseur::isAGuardianHit()
{

	// Check for collision for all the guardian
	for (int i = 1; i < _l->_nguards; i++)
	{
		float dx = _l->_guards[i]->_x - _fb->get_x(); // distance between the guardian and the fireball in the x axis
		float dy = _l->_guards[i]->_y - _fb->get_y(); // distance between the guardian and the fireball in the y axis

		double distance = sqrt(dx * dx + dy * dy);

		if (distance < HIT_RADIUS)
		{
			_guard_hit->play(1. - distance / dmax2);
			_fireball_active = false;
			return true;
		}
	}
	return false;
}

/* The following function is used to fire a fireball from the Chasseur. */
void Chasseur::fire(int angle_vertical)
{
	_angle += errorRateBasedOnLife();
	if (_fb && _fireball_active == false)
	{
		_fireball_active = true;
		_fb->init(/* position initiale de la boule */ _x, _y, 10.,
				  /* angles de vis�e */ angle_vertical, _angle);
	}
}

/*
 *	Clic droit: par d�faut fait tomber le premier gardien.
 *
 *	Inutile dans le vrai jeu, mais c'est juste pour montrer
 *	une utilisation des fonctions � tomber � et � rester_au_sol �
 */

void Chasseur::right_click(bool shift, bool control)
{

	if (shift)
		_l->_guards[1]->rester_au_sol();
	else
		_l->_guards[1]->tomber();
}

/*This function is used to add an error to the Hunter's attack based on its health.*/
float Chasseur::errorRateBasedOnLife()
{
	if (chasseur_health == LIFE_HUNTER)
		return 0;
	// 10% chance to miss target return a random error
	if (chasseur_health < LIFE_HUNTER * 0.7 && rand() % 100 < 10)
		return rand() % 15;

	// 15% chance to miss target if life less than 50%
	else if (chasseur_health < LIFE_HUNTER * 0.5 && rand() % 100 < 15)
		return rand() % 20;

	return 0;
}