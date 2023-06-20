#include "CentipedeBody.h"

/** \file CentipedeBody.cpp
 */

CentipedeBody::CentipedeBody()
{
    bodyParts.reserve(16);
    enoughBodyParts = false;
    length = 11;
    auto spacing =32;
    CentipedeClass Cent (sf::Vector2f(600.f, 15.f)); //initial creation of centipede segments
    bodyParts.push_back(Cent);

    while(bodyParts.size()<length && !enoughBodyParts)
    {
        auto positionC = sf::Vector2f(600.f+ spacing, 15.f); //spacing to place them next to each other
        CentipedeClass Cent(positionC);
        bodyParts.push_back(Cent);
        spacing += 32;
    }
    bodyParts.at(0).makeHead();
    bodyParts.at(length-1).makeTail();
    enoughBodyParts = true;
}

void CentipedeBody::moveCentipede(float d,const sf::Vector2u &windowSize)
{
    for (long long unsigned int i =0; i<bodyParts.size(); i++)
    {
        bodyParts.at(i).moveCentipedeBody(d, windowSize);
    }
}
