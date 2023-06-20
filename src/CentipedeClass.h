#ifndef CENTIPEDECLASS_H_INCLUDED
#define CENTIPEDECLASS_H_INCLUDED
#include <SFML/Graphics.hpp>

/** \file CentipedeClass.h
    \brief Contains code used for the functionality of a centipede part

    This class moves centipede body parts, determines the status of the different body parts,
    and determines the direction of the different body parts

    */

/** \class CentipedeClass
    \brief Contains code used for the functionality of a centipede part
 */
class CentipedeClass
{

public:
     /** \brief a boolean which is used to determine if the centipede is moving right
    */
    bool direction_right;

    /** \fn void makeHead()
    *  \brief This function makes the bodypart into a head

    */
    void makeHead();

    /** \fn void makeTail()
    *  \brief This function makes the bodypart into a tail

    */
    void makeTail();

    /** \fn void moveCentipedeBody()
    *  \brief This function moves the centipede bodypart

    *   \param d This is the change in time from when a new game loop has been run
        \param windowSize Size of the window to ensure that the bug stays inside

    */
    void moveCentipedeBody(float d,const sf::Vector2u &windowSize);

    /** \brief This constructs a centipede bodypart.
    *   \param pos This is the where the centipede bodypart is to be positioned
    */
    CentipedeClass(sf::Vector2f pos);

    /** \brief This creates a built in SFML circle shape to represent a centipede bodypart.
    */
    sf::CircleShape CentipedeSeg;

    /** \fn void moveCentipedeBody_mush_right()
    *  \brief This function moves the centipede bodypart down and then left if it hits a mushroom from the right

    *   \param pos The postion of the centipede body part

    */
    void moveCentipedeBody_mush_right(sf::Vector2f pos);

    /** \fn void moveCentipedeBody_mush_right()
    *  \brief This function moves the centipede bodypart down and then right if it hits a mushroom from the left

    *   \param pos The postion of the centipede body part

    */
    void moveCentipedeBody_mush_left(sf::Vector2f pos);

    /** \fn bool head()
    *  \brief This boolean function determines if the body part is a head

    */
    bool head();

   /** \fn bool taul()
    *  \brief This boolean function determines if the body part is a tail

    */
    bool tail();

private:
    int radius;
    bool isHead;
    bool isTail;
    int centipedeSpeed;
    int right_limit;
    int left_limit;
    bool direction_down;
};



#endif // CENTIPEDECLASS_H_INCLUDED
