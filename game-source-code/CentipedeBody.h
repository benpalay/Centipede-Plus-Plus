#ifndef CENTIPEDEBODY_H_INCLUDED
#define CENTIPEDEBODY_H_INCLUDED
#include "CentipedeClass.h"

/** \file CentipedeBody.h
    \brief Contains code for constructing a centipede

    This class constructs a centipede and moves the centipede
    */

/** \class CentipedeBody
    \brief Contains code for constructing a centipede
 */

class CentipedeBody
{
public:
    /** \fn void moveCentipede()
    *  \brief This function moves the centipede

    *   \param d This is the change in time from when a new game loop has been run
        \param windowSize Size of the window to ensure that the bug stays inside

    */
    void moveCentipede(float d,const sf::Vector2u &windowSize);
    /** \brief This constructs a centipede body by creating each segment individually and then spreading it out.
    */
    CentipedeBody();

    /** \brief This is a vector of bullets for easy insertion,deletion and internal changes
    */
    std::vector<CentipedeClass>bodyParts;

private:
    long long unsigned int length;
    bool enoughBodyParts;
    bool direction_right;
    int radius;
};

#endif // CENTIPEDEBODY_H_INCLUDED
