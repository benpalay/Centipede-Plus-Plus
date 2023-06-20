#include "Bug.h"

/** \file Bug.cpp
 */

void Bug::makeBug()
{
    bug.setPointCount(12);
    bug.setPoint(0, sf::Vector2f(0.f, 0));
    bug.setPoint(1, sf::Vector2f( 2.f,0.f));
    bug.setPoint(2, sf::Vector2f( 2.f, -2.f));
    bug.setPoint(3, sf::Vector2f(15.f, -15.f));
    bug.setPoint(4, sf::Vector2f( 15.f, -30.f));
    bug.setPoint(5, sf::Vector2f( 2.f, -44.f));
    bug.setPoint(6, sf::Vector2f( 2.f, -45.f));
    bug.setPoint(7, sf::Vector2f( 0.f, -45.f));
    bug.setPoint(8, sf::Vector2f( 0.f, -44.f));
    bug.setPoint(9, sf::Vector2f( -15.f, -30.f));
    bug.setPoint(10, sf::Vector2f( -15.f, -15.f));
    bug.setPoint(11, sf::Vector2f( 0.f, -2.f));

    bug.setPosition(600.f, 800.f);
    bug.setFillColor(sf::Color::White);
    bug.setOutlineColor(sf::Color::Red);
    bug.setOutlineThickness(2);
}

void Bug::moveBug(float d, const sf::Vector2u &windowSize)
{

        if( bug.getPosition().x<=(windowSize.x - 22.f) && Keyboard::isKeyPressed(Keyboard::Right)) //keeps bug within screensize
        {
            bug.move(bugSpeed*d, 0.f);
        }
        if(bug.getPosition().x>22.f && Keyboard::isKeyPressed(Keyboard::Left))
        {
            bug.move(-bugSpeed*d, 0.f);
        }
        if(bug.getPosition().y>=4*windowSize.y/5  && Keyboard::isKeyPressed(Keyboard::Up)) //keeps in bottom quarter of screen
        {
            bug.move(0.f,-bugSpeed*d);
        }
        if(bug.getPosition().y<=windowSize.y && Keyboard::isKeyPressed(Keyboard::Down))
        {
            bug.move(0.f,bugSpeed*d);
        }
}


Bug::Bug()
{
    bugSpeed = 700.f;
    makeBug();
}
