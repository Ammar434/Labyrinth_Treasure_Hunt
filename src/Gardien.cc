/* This class is used to implement all the functionalities related to the Gardien.
 It is responsible for the movement of the Gardien, the attack and the damage
 it can take. It also handles the fireball and the collision with the chasseur
 It also handles the gardien's health and the cooldown for the gardien to get
 up after being knocked out. It also handles the line of sight of the gardien
 and the patrol movement of the gardien. It also handles the error rate of the
gardien based on its health. 
*/


#include "../include/Gardien.h"

/* We define chasseur health here since we cannot access it directly
from Chasseur.h of course a better way would be to use a getter but we are not allowed to modify Mover.h. */
int chasseur_health = LIFE_HUNTER; // life of the chasseur (player) is 5

//The following function helps ensure that the fireball travels only through unobstructed paths within the game environment.
bool Gardien::can_move_fireball(float delta_x, float delta_y)
{
    return EMPTY_CELL == _l->data(static_cast<int>((_fb->get_x() + delta_x) / Environnement::scale),
                                  static_cast<int>((_fb->get_y() + delta_y) / Environnement::scale)) ||
           MARK_CELL == _l->data(static_cast<int>((_fb->get_x() + delta_x) / Environnement::scale),
                                 static_cast<int>((_fb->get_y() + delta_y) / Environnement::scale));
}

//The following function is used to handle the collision of the fireball with the chasseur or the wall.
void Gardien::handle_collision(float dist2, bool chasseur_hit)
{
    _fireball_active = false;
    if (chasseur_hit)
    {
        // TODO:message not display at the correct moment
        message("You have %d health left…", chasseur_health - 1);

        chasseur_health--;
        if (chasseur_health == 0)
        {
            partie_terminee(false);
        }
        _hunter_hit->play(1. - dist2 / dmax2);
    }
    else
    {
        _wall_hit->play(1. - dist2 / dmax2);
    }
}

/* This function is called periodically to update the state of the Gardien. It calculates the angle towards the player character,
 checks for line of sight, and decides whether to pursue the player or patrol based on the available information.*/
void Gardien::update(void)
{

    getDamage();

    if (_health < 0 || isKnockout)
        return;

    float playerX = _l->_guards[0]->_x; // x position of the player
    float playerY = _l->_guards[0]->_y; // y position of the player

    float distanceX = playerX - _x; // distance between the player and the gardien in the x axis
    float distanceY = playerY - _y; // distance between the player and the gardien in the y axis

    _angle = -atan2(distanceX, distanceY) * (180 / M_PI) + errorRateBasedOnLife();
    moving_angle = atan2(distanceY, distanceX) * (180 / M_PI);

    _angle = fmod(_angle, 360);
    moving_angle = fmod(moving_angle, 360);

    has_LOS = line_of_sight(playerX, playerY, _x, _y, Environnement::scale, _l);

    if (has_LOS > 0)
    {
        last_chasseur_x = playerX;
        last_chasseur_y = playerY;
        float nextX = cos(moving_angle * M_PI / 180) * TRACKING_SPEED; // next x position of the gardien
        float nextY = sin(moving_angle * M_PI / 180) * TRACKING_SPEED; // next y position of the gardien

        if (has_LOS > min_fire_distance)
            move_aux(nextX, nextY);

        try_attack();
    }
    else
    {
        float distanceToLastKnownPositionX = (last_chasseur_x - _x) / Environnement::scale; // distance between the last known position of the player and the gardien in the x axis
        float distanceToLastKnownPositionY = (last_chasseur_y - _y) / Environnement::scale; // distance between the last known position of the player and the gardien in the y axis
        float distance = calculateDistance(0, 0, distanceToLastKnownPositionX, distanceToLastKnownPositionY);

        if (distance < 15 || (last_chasseur_x == 0 && last_chasseur_y == 0))
        {
            patrol();
        }
        else
        {
            float nextX = distanceToLastKnownPositionX / distance * TRACKING_SPEED; // next x position of the gardien
            float nextY = distanceToLastKnownPositionY / distance * TRACKING_SPEED; // next y position of the gardien
            move_aux(nextX, nextY);
        }
    }
}


/* This function is responsible for moving the Gardien to a new position 
if the target position is unobstructed by walls or obstacles. */
bool Gardien::move_aux(double dx, double dy)
{
    if (EMPTY_CELL == _l->data((int)((_x + dx) / Environnement::scale), (int)((_y + dy) / Environnement::scale)))
    {
        _x += dx;
        _y += dy;
        return true;
    }
    return false;
}

/* It controls the Gardien's patrolling behavior by determining the next movement direction. 
If the next position is blocked by a wall or obstacle, it changes the patrol angle to navigate around it.*/
void Gardien::patrol()
{
    double dx = cos(patrol_angle * M_PI / 180) * PATROL_SPEED; // next x position of the gardien based on the patrol angle
    double dy = sin(patrol_angle * M_PI / 180) * PATROL_SPEED; // next y position of the gardien based on the patrol angle

    // Check if the next position is out of bounds or a wall
    // If it's out of bounds or a wall, change the angle
    if (!move_aux(dx, dy))
    {
        patrol_angle += rand() % 180;
        patrol_angle = fmod(patrol_angle, 360.0);
    }
}

/*It manages the Gardien's health and reaction to damage. It detects if the Gardien is hit by the player's fireball, 
reduces its health, and triggers specific actions such as knockout or remaining on the ground based on the severity of the damage.*/
void Gardien::getDamage()
{
    auto now = std::chrono::steady_clock::now();
    auto time_since_last_hit = std::chrono::duration_cast<std::chrono::seconds>(now - last_time_being_hit); // time since the last hit

    if (time_since_last_hit.count() >= HIT_COOLDOWN)
    {
        successive_hit = 0;
        isKnockout = false;
    }

    if (time_since_last_hit.count() < HIT_COOLDOWN &&
        successive_hit == SUCCESSIVE_HITS_LIMIT)
    {
        tomber();
        isKnockout = true;
        return;
    }

    if (_health < 0)
    {

        rester_au_sol();
        return;
    }

    int chasseur_fireball_x = static_cast<int>(_l->_guards[0]->_fb->get_x()); // x position of the chasseur's fireball
    int chasseur_fireball_y = static_cast<int>(_l->_guards[0]->_fb->get_y()); // y position of the chasseur's fireball

    int current_x = static_cast<int>(_x); // x position of the gardien
    int current_y = static_cast<int>(_y); // y position of the gardien

    if (calculateDistance(chasseur_fireball_x, chasseur_fireball_y, current_x, current_y) < HIT_RADIUS)
    {
        _health -= 1;
        last_time_being_hit = now;
        successive_hit++;
    }
}


/*This function is responsible for determining when the Gardien should attempt to attack the player character (Chasseur) 
by firing a fireball projectile. */
void Gardien::try_attack()
{
    auto now = std::chrono::steady_clock::now();
    auto time_since_last_shot = std::chrono::duration_cast<std::chrono::seconds>(now - last_shot); // time since the last shot
    int random_time = rand() % 10 + 3;                                                           // random time to wait before firing again

    if (time_since_last_shot.count() >= random_time)
    {
        fire(0);
        last_shot = now;
    }
}

/* It handles the movement and collision of the fireball projectile launched by the Gardien. 
It checks if the fireball can move to the next position without obstruction and handles collisions with walls or 
the player character, applying damage if necessary.*/
bool Gardien::process_fireball(float delta_x, float delta_y)
{
    float chasseur_x = _l->_guards[0]->_x; // x position of the player
    float chasseur_y = _l->_guards[0]->_y; // y position of the player

    float dist2 = calculateDistance(_x, _y, chasseur_x, chasseur_y); // distance between the gardien and the player

    bool chasseur_hit = isChasseurHit(); // check if the player is hit by the fireball

    if (can_move_fireball(delta_x, delta_y) && !chasseur_hit)
    {
        return true;
    }

    handle_collision(dist2, chasseur_hit);

    return false;
}

/* It determines if the player character is hit by the Gardien's fireball projectile based on their proximity to each other.*/
bool Gardien::isChasseurHit()
{
    float chasseur_x = _l->_guards[0]->_x; 
    float chasseur_y = _l->_guards[0]->_y;

    return calculateDistance(chasseur_x, chasseur_y, _fb->get_x(), _fb->get_y()) < HIT_RADIUS;
}

/*This function is used to add an error to the Gardien's attack based on its health.*/
float Gardien::errorRateBasedOnLife()
{
    if (_health == LIFE_GUARD)
        return 0;
    // 10% chance to miss target return a random error
    if (_health < LIFE_GUARD * 0.7 && rand() % 100 < 10)
        return rand() % 15;

    // 15% chance to miss target if life less than 50%
    else if (_health < LIFE_GUARD * 0.5 && rand() % 100 < 15)
        return rand() % 20;

    return 0;
}