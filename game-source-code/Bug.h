#ifndef BUG_H_INCLUDED
#define BUG_H_INCLUDED
#include <SFML/Graphics.hpp>

/** \file Bug.h
    \brief Contains code for constructing a bug

    This class contains code for constructing a bug and a function to move the bug.
    */

using namespace sf;

 /** \class Bug
    \brief Contains code for constructing a bug
 */

class Bug
{
public:

    /** \fn void moveBug(float d, const sf::Vector2u &windowSize)
    *  \brief This function moves the Bug

    *   \param d This is the change in time from when a new game loop has been run
        \param windowSize Size of the window to ensure that the bug stays inside

    */

    void moveBug(float d,const sf::Vector2u &windowSize);

    /** \brief This creates a built in SFML diamond shape to represent a bug.
    */

    sf::ConvexShape bug;

    /** \brief This constructs a bug object.
    */

    Bug();
private:
    float bugSpeed;
    void makeBug();
};


#endif // BUG_H_INCLUDED
