#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
#include "CentipedeClass.h"
#include "Mushroom.h"
#include "Bug.h"
#include <vector>
#include <list>
/** \file Collisions.h
    \brief Contains functions for collisions between game objects

    This class checks for collisions between the bug, the centipede parts, the bullets and the mushrooms.
    It also modifies the Centipede, mushrooms and bullets based on their different types of collisions.

 */

/** \class Collisions
   \brief Contains functions for collisions between game objects
*/
using namespace sf;

class Collisions
{
public:

    /**  \brief This accepts game objects and calls specific collision fucntions for two or three types at a time

     *  This accepts game objects by reference and calls specific collision functions
     that check for a collision and then modify the object/vector/list.
     If a bullet hits a centipede part, the centipede part is destroyed,a mushroom is created in that position.
     If the centipede collides with a mushroom, it reverses dreciton and moves down.

     */

    Collisions(std::list<Bullet>& Bullet, std::list<Mushroom>& Mushroom,std::vector<CentipedeClass>& bodyParts,int &pointC);

   /** \fn bool cent_bug()

     *  \brief This function checks if the centipede and bug have collided

     *  \return true if the bug and centipede collide

     */
    bool cent_bug(std::vector<CentipedeClass>& bodyParts, Bug &bug);

private:
    void bullet_mush_or_cent(std::list<Bullet>& Bullet, std::list<Mushroom>& Mushroom,std::vector<CentipedeClass>& bodyParts,int &pointC);
    void mush_cent(std::list<Mushroom>& Mushroom,std::vector<CentipedeClass>& bodyParts);
};

#endif // COLLISIONS_H_INCLUDED
