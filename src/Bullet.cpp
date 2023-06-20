#include "Bullet.h"

/** \file Bullet.cpp
 */

using namespace sf;
void Bullet::makeBullet(sf::Vector2f p)
{
    bullet.setPosition(p); //sets the bullets at the position of the bug
    bullet.setFillColor(sf::Color::White);
    bullet.setRadius(10.f);
}

void Bullet::shootBullet(float d)
{
    bullet.move(0.f, -bulletSpeed*d);
}

Bullet::Bullet(sf::Vector2f p)
{
    bulletSpeed = 800.f;
    makeBullet(p);
}
