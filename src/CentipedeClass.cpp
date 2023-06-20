#include "CentipedeClass.h"

/** \file CentipedeClass.cpp
 */

CentipedeClass::CentipedeClass(sf::Vector2f pos)
{
    radius = 15;
    centipedeSpeed = 1200.f;
    direction_right = false;
    direction_down =true;
    isHead = false;
    isTail = false;
    left_limit = 5; //limits of the screen
    right_limit = 1500;
    CentipedeSeg.setFillColor(sf::Color::Green);
    CentipedeSeg.setPosition(pos);
    CentipedeSeg.setRadius(radius);
}

void CentipedeClass::makeHead()
{
    isHead = true;
    isTail = false;
    CentipedeSeg.setFillColor(sf::Color::Cyan); //to see visually where a new head is
}

void CentipedeClass::makeTail()
{
    isTail = true;
}

void CentipedeClass::moveCentipedeBody(float d, const sf::Vector2u &windowSize)
{
    if(direction_right) //move right until screen boundary
    {
        CentipedeSeg.move(centipedeSpeed*d, 0.f);
    }
    if( !direction_right)
    {
        CentipedeSeg.move(-centipedeSpeed*d, 0.f); //move left until screen boundary
    }
    if( CentipedeSeg.getPosition().x >right_limit && direction_right)
    {
        direction_right =false;
        if(direction_down)
        {
            CentipedeSeg.setPosition(right_limit+1, CentipedeSeg.getPosition().y + 2*radius);
        } //if at screen boundary, move down
        else if(!direction_down)
        {
            CentipedeSeg.setPosition(right_limit+1, CentipedeSeg.getPosition().y - 2*radius);
        }
    }
    if(CentipedeSeg.getPosition().x <left_limit && !direction_right)
    {
        direction_right =true;
        if(direction_down)
        {
            CentipedeSeg.setPosition(left_limit+1, CentipedeSeg.getPosition().y + 2*radius);   //if at screen boundary, move down
        }
        else if(!direction_down)
        {
            CentipedeSeg.setPosition(left_limit+1, CentipedeSeg.getPosition().y - 2*radius);
        }
    }
    if(CentipedeSeg.getPosition().y>windowSize.y - 3*radius)
    {
        direction_down = false;   //moves upwards after reaching the bottom of the screen
    }
    if(CentipedeSeg.getPosition().y< 3*radius && !direction_down)
    {
        direction_down = true;   //moves upwards after reaching the bottom of the screen
    }
}


void CentipedeClass::moveCentipedeBody_mush_left(sf::Vector2f pos) //for collision with mushroom from the right
{
    direction_right = false;
    if(direction_down)
    {
        CentipedeSeg.setPosition(pos.x, pos.y + 2*radius);
    }
    else if(!direction_down)
    {
        CentipedeSeg.setPosition(pos.x, pos.y - 2*radius); //move up if direction is up and hit mushroom
    }
}

void CentipedeClass::moveCentipedeBody_mush_right(sf::Vector2f pos)  //for collision with mushroom from the left
{
    direction_right = true;
    if(direction_down)
    {
        CentipedeSeg.setPosition(pos.x, pos.y + 2*radius);
    }
    else if(!direction_down)
    {
        CentipedeSeg.setPosition(pos.x, pos.y - 2*radius);
    }
}

bool CentipedeClass::head()
{
    return isHead;
}

bool CentipedeClass::tail()
{
    return isTail;
}
