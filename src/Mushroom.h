#ifndef MUSHROOM_H_INCLUDED
#define MUSHROOM_H_INCLUDED
#include <SFML/Graphics.hpp>

/** \file Mushroom.h
    \brief Contains code for constructing a mushroom

    This class can construct a mushroom, decrease and provide its health.
 */

 /** \class Mushroom
    \brief Contains code for constructing a mushroom
 */

class Mushroom
{
public:

      /** \brief This creates a built in SFML rectangle shape to represent a mushroom.
    */

    sf::RectangleShape mushroom;


    /** \brief This constructs a mushroom object at a random position.
        \param position_rand Is a random point within the screen limits
    */

    Mushroom(sf::Vector2f position_rand);


    /** \fn int getHealth()
     *  \brief This function provides the number of times a mushroom can be hit (-1) before being destroyed
     *  \return health of a mushroom
     */

    int getHealth();

    /** \fn int isHit()
    *  \brief This function decreases the health of a mushroom when it is hit by a bullet

    */
    void isHit();

private:
    int health_;

};
#endif // MUSHROOM_H_INCLUDED
