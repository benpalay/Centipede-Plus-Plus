
/** \file Collisions.cpp
 */

#include "Collisions.h"

Collisions::Collisions(std::list<Bullet>& Bullet, std::list<Mushroom>& Mushroom,std::vector<CentipedeClass>& bodyParts,int &pointC)
{
    bullet_mush_or_cent(Bullet,Mushroom, bodyParts, pointC);
    mush_cent( Mushroom, bodyParts);
}

//checks if bullet hits mushroom or centipede
void Collisions::bullet_mush_or_cent(std::list<Bullet>& bullets, std::list<Mushroom>& mushrooms, std::vector<CentipedeClass>& bodyParts, int &pointC)
{

    for (auto it2 = begin(bullets); it2!=end(bullets); it2++)
    {
        auto i2 = *it2;
        for (auto it = begin(mushrooms); it!=end(mushrooms); it++)
        {
            auto i =*it;

            if(i.mushroom.getGlobalBounds().intersects(i2.bullet.getGlobalBounds()))
            {
                it->isHit();
                it->mushroom.setSize(sf::Vector2f (20, 20 - (35/((it->getHealth()))) )); //if hit, mushroom shrinks
                it->mushroom.setOutlineThickness(5 - (5/((it->getHealth()))));//if hit, changes outline thickness
                bullets.erase(it2--);


                if(it->getHealth() == 1) //4 shots to destroy a mushroom (health_ initialized to 5)
                {
                    mushrooms.erase(it--); //post decrement to get iterator correctly
                    pointC = pointC +1;
                }
            }
        }
        for (long long unsigned int c = 0; c<bodyParts.size(); c++)
        {

            if(bodyParts.at(c).CentipedeSeg.getGlobalBounds().intersects(i2.bullet.getGlobalBounds()))//check if centipedeSegment hit
            {
                auto new_mush_position = bodyParts.at(c).CentipedeSeg.getPosition();
                Mushroom mush(new_mush_position); //turn shot segment into mushroom
                mushrooms.push_front(mush);
                bullets.erase(it2--);

                if(bodyParts.size() ==1)
                {
                    bodyParts.erase(begin(bodyParts));
                    pointC = pointC +100;
                    break;
                }
                if(c == bodyParts.size()-1) //last one
                {
                    bodyParts.erase(begin(bodyParts)+c);
                    pointC = pointC +100;    //adding points
                    break;

                }
                if(bodyParts.at(c).head())
                {
                    bodyParts.erase(begin(bodyParts)+c);
                    bodyParts.at(c).makeHead();
                    pointC = pointC +100;
                    break;
                }
                if(!bodyParts.at(c).tail() && !bodyParts.at(c).head())
                {
                    if(c!=0)
                    {
                        bodyParts.at(c-1).makeTail();
                    }
                    pointC = pointC +10;
                    bodyParts.erase(begin(bodyParts)+c);
                    bodyParts.at(c).makeHead();
                    break;
                }
                if(bodyParts.at(c).tail())
                {
                    bodyParts.erase(begin(bodyParts)+c);
                    pointC = pointC +10;
                    break;
                }
            }
        }
    }
}


//check if centipede collides with mushroom
void Collisions::mush_cent(std::list<Mushroom>& mushrooms,std::vector<CentipedeClass>& bodyParts)
{

    for (auto it = begin(mushrooms); it!=end(mushrooms); it++)
    {
        auto i =*it;
        for (long long unsigned int c = 0; c<bodyParts.size(); c++)
        {
            {
                if(i.mushroom.getGlobalBounds().intersects(bodyParts.at(c).CentipedeSeg.getGlobalBounds()))
                {
                    auto pos = sf::Vector2f(bodyParts.at(c).CentipedeSeg.getPosition().x, bodyParts.at(c).CentipedeSeg.getPosition().y);
                    if(bodyParts.at(c).direction_right)
                    {
                        bodyParts.at(c).moveCentipedeBody_mush_left(pos);
                    }
                    else
                    {
                        bodyParts.at(c).moveCentipedeBody_mush_right(pos);
                    }
                }

            }
        }
    }
}

//check if centipede hits bug
bool Collisions::cent_bug(std::vector<CentipedeClass>& bodyParts, Bug &bug)
{
    for (long long unsigned int c = 0; c<bodyParts.size(); c++)
    {
        if(bodyParts.at(c).CentipedeSeg.getGlobalBounds().intersects(bug.bug.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

