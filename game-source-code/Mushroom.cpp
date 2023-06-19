#include "Mushroom.h"

/** \file Mushroom.cpp
 */
using namespace sf;

Mushroom::Mushroom(sf::Vector2f position_rand)
{
    mushroom.setPosition(position_rand);
    mushroom.setFillColor(sf::Color::Yellow);
    mushroom.setOutlineColor(sf::Color::Red);
    mushroom.setOutlineThickness(5);
    mushroom.setSize(sf::Vector2f(20, 20));
    health_ = 5;
}

int Mushroom::getHealth()
{
    return health_;
}

void Mushroom::isHit()
{
    health_--;
}

