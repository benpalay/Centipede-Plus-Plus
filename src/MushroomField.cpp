#include "MushroomField.h"

/** \file MushroomField.cpp
 */
MushroomField::MushroomField()
{
    enoughMushrooms = false;
    max_mushrooms =28;
}

void MushroomField::Make_mushrooms(const sf::Vector2u &windowSize)
{
    while (mushrooms.size()<max_mushrooms && !enoughMushrooms)
    {
        auto positionM = sf::Vector2f(rand()% (windowSize.x -40), (rand()% (windowSize.y-150)) +50 );
        Mushroom mushroom(positionM);
        mushrooms.push_front(mushroom);
    }
    enoughMushrooms = true;
}
