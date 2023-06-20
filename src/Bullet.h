#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <SFML/Graphics.hpp>

/** \file Bullet.h
    \brief Contains code for constructing a bullet

    This class makes bullets and shoots the bullets
    */

     /** \class Bullet
    \brief Contains code for constructing a bullet
 */

class Bullet
{
public:
    /** \fn void shootBullet(float d)
    *  \brief This function shoots a bullet

    *   \param d This is the change in time from when a new game loop has been run

    */
    void shootBullet(float d);

    /** \brief This creates a built in SFML circle shape to represent a bullet.
    */
    sf::CircleShape bullet;


    /** \brief This constructs a Bullet at the position of the bug.
        \param p Is the position of the bug at which point the bullet is created.
    */

    Bullet(sf::Vector2f p);

private:
    float bulletSpeed;
    void makeBullet(sf::Vector2f p);
};

#endif // BULLET_H_INCLUDED
