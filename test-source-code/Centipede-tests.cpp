
#include "../game-source-code/Game.h"
#include "../game-source-code/Bug.h"
#include "../game-source-code/Bullet.h"
#include "../game-source-code/CentipedeClass.h"
#include "../game-source-code/MushroomField.h"

#include <SFML/Graphics.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace sf;


// ///////////////******BUG MOVEMENT*********//////////////////////

TEST_CASE("bug position changes right when bug moved right")
{
    Bug bug;
    auto x = bug.bug.getPosition().x;
    bug.bug.move(20.f,0.f); //cannot simulate right key press, therefore simply testing that it moves the way it should.
    auto x2 = bug.bug.getPosition().x;

    CHECK(x<x2);

}

TEST_CASE("bug position changes left when bug moved left")
{
    Bug bug;
    auto x = bug.bug.getPosition().x;
    bug.bug.move(-20.f,0.f);
    auto x2 = bug.bug.getPosition().x;

    CHECK(x>x2);
}

TEST_CASE("bug position changes up when bug moved up")
{
    Bug bug;
    auto y = bug.bug.getPosition().y;
    bug.bug.move(0.f,20.f);
    auto y2 = bug.bug.getPosition().y;

    CHECK(y<y2);
}

TEST_CASE("bug position changes down when bug moved down")
{
    Bug bug;
    auto y = bug.bug.getPosition().y;
    bug.bug.move(0.f,-20.f);
    auto y2 = bug.bug.getPosition().y;

    CHECK(y>y2);
}

TEST_CASE("bug position changes down when bug moved down")
{
    Bug bug;
    auto y = bug.bug.getPosition().y;
    bug.bug.move(0.f,20.f);
    auto y2 = bug.bug.getPosition().y;

    CHECK(y<y2);
}


///////*********Bullets**************/////


TEST_CASE("Bullet moves up when shot")
{
    Bug bug;
    Bullet bullet(bug.bug.getPosition());
    auto y = bullet.bullet.getPosition().y;
    bullet.shootBullet(-100);
    auto y2 = bullet.bullet.getPosition().y;

    CHECK(y2>y);
}

TEST_CASE("Bullet can be created at the position of the bug")
{
    Bug bug;
    Bullet bullet(bug.bug.getPosition());
    auto x = bullet.bullet.getPosition();
    auto x2 = bullet.bullet.getPosition();

    CHECK(x==x2);
}


///////*********Centipede**************/////

TEST_CASE("Centipede is created and starts by moving left")
{
    CentipedeClass Cent(sf::Vector2f(600.f, 100.f));
    auto x1 =  Cent.CentipedeSeg.getPosition().x;
    Cent.moveCentipedeBody(100, sf::Vector2u (1500,800));
    auto x2 = Cent.CentipedeSeg.getPosition().x;

    CHECK(x2<x1);
}

TEST_CASE("Centipede moves right after it reaches the left window boundary ")
{
    CentipedeClass Cent(sf::Vector2f(7, 100.f)); //left limit set at 6.f
    auto x1 =  Cent.CentipedeSeg.getPosition().x;
    Cent.moveCentipedeBody(0.1, sf::Vector2u (1500,800)); // move left,set direction to right
    auto x2 = Cent.CentipedeSeg.getPosition().x;
    CHECK(x2<x1);//moved left past screen limit
    Cent.moveCentipedeBody(0.1, sf::Vector2u (1500,800)); // now move right
    auto x3 = Cent.CentipedeSeg.getPosition().x;

    CHECK(x3>x2);
}

TEST_CASE("Centipede moves down after it reaches the left window boundary")
{
    CentipedeClass Cent(sf::Vector2f(7, 100.f));
    auto y1 =  Cent.CentipedeSeg.getPosition().y;
    Cent.moveCentipedeBody(0.1, sf::Vector2u (1500,800));
    auto y2 = Cent.CentipedeSeg.getPosition().y;

    CHECK(y2>y1);
}

TEST_CASE("Centipede moves down after it reaches the right window boundary")
{
    CentipedeClass Cent(sf::Vector2f(1502, 100.f));
    auto y1 =  Cent.CentipedeSeg.getPosition().y;
    Cent.moveCentipedeBody(100, sf::Vector2u (1500,800));
    auto y2 = Cent.CentipedeSeg.getPosition().y;

    CHECK(y2>y1);

}

TEST_CASE("Centipede moves left after it reaches the right window boundary ")
{
    CentipedeClass Cent(sf::Vector2f(700, 100.f)); //set in the middle
    auto x1 =  Cent.CentipedeSeg.getPosition().x;

    while( Cent.CentipedeSeg.getPosition().x<1501.f)
    {
        Cent.moveCentipedeBody(100, sf::Vector2u (1500,800));//move until at right limit
    }
    Cent.moveCentipedeBody(0.1, sf::Vector2u (1500,800)); // now move left
    auto x2 = Cent.CentipedeSeg.getPosition().x;

    CHECK(x2<1501.f);

}

TEST_CASE("Centipede moves up after it reaches the bottom window boundary ")
{
    auto windowSize = sf::Vector2u(1500,800);
    CentipedeClass Cent(sf::Vector2f(700, 790));
    auto y1 =  Cent.CentipedeSeg.getPosition().y;
    Cent.moveCentipedeBody(100, windowSize);//move down,set direction to up
    auto y2 = Cent.CentipedeSeg.getPosition().y;
    CHECK(y2>y1);
    Cent.moveCentipedeBody(100, windowSize); //move up
    auto y3 = Cent.CentipedeSeg.getPosition().y;

    CHECK(y3<y2);

}

///////*********Mushrooms**************/////

TEST_CASE("Mushrooms created in different positions on the screen ")
{
    auto windowSize = sf::Vector2u(1500,800); //mushrooms need to be contained within some limit
    MushroomField mushField;
    mushField.Make_mushrooms(windowSize);
    auto it = begin(mushField.mushrooms);
    auto i =*it;
    auto pos1x = i.mushroom.getPosition().x; //first mushroom created in list
    auto pos1y = i.mushroom.getPosition().y;
    it++;
    i = *it;
    auto pos2x = i.mushroom.getPosition().x; //second mushroom created in list
    auto pos2y = i.mushroom.getPosition().y;

    CHECK_FALSE(pos1x==pos2x);
    CHECK_FALSE(pos1y==pos2y);
}


///////*********Collisions**************/////


TEST_CASE("When bullet hits centipede segment, segment is destroyed")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Bullet bullet(sf::Vector2f(600, 15));//create bullet at starting point of centipede
    bullets.push_front(bullet);
    CentipedeBody bodyParts;
    auto num1 = bodyParts.bodyParts.size();
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    auto num2 = bodyParts.bodyParts.size();
    auto x = bodyParts.bodyParts.at(0).CentipedeSeg.getPosition();

    CHECK(num1-1 == num2);  //vector size decreased by 1
    CHECK_FALSE(x == sf::Vector2f(600, 15)); //new position of first segment has changed
}

TEST_CASE("When bullet hits centipede segment, mushroom created in that position")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Bullet bullet(sf::Vector2f(600, 15));//create bullet at starting point of centipede
    bullets.push_front(bullet);
    CentipedeBody bodyParts;
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    auto it =end(mushField.mushrooms); //mushroom added to back of list
    it--;
    auto x = it->mushroom.getPosition();

    CHECK(x == sf::Vector2f(600, 15)); //position of mushroom in same position as hit segment
}

TEST_CASE("When bullet hits centipede segment, next segment becomes a head")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Bullet bullet(sf::Vector2f(600, 15));//create bullet at starting point of centipede
    bullets.push_front(bullet);
    CentipedeBody bodyParts;
    auto x = bodyParts.bodyParts.at(1).head();
    CHECK_FALSE(x);
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    x = bodyParts.bodyParts.at(0).head();

    CHECK(x);
}

TEST_CASE("When centipede segment hits mushroom, changes direction")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Mushroom mush(sf::Vector2f(559,15)); //create mushroom on left of centipede
    mushField.mushrooms.push_front(mush);
    Bullet bullet(sf::Vector2f(bug.bug.getPosition()));//create bullet at starting point of centipede
    bullets.push_front(bullet);
    auto windowSize = sf::Vector2u(1500,800);
    CentipedeBody bodyParts;
    auto x = bodyParts.bodyParts.at(0).CentipedeSeg.getPosition().x;
    bodyParts.bodyParts.at(0).moveCentipedeBody(0.1,windowSize); //move left until mushroom
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    bodyParts.bodyParts.at(0).moveCentipedeBody(1,windowSize); //now move right
    auto x1 = bodyParts.bodyParts.at(0).CentipedeSeg.getPosition().x;

    CHECK(x1>x);
}

TEST_CASE("When centipede segment hits mushroom, segment moves down")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Mushroom mush(sf::Vector2f(559,15)); //create mushroom on left of centipede
    mushField.mushrooms.push_front(mush);
    Bullet bullet(sf::Vector2f(bug.bug.getPosition()));//create bullet at starting point of centipede
    bullets.push_front(bullet);
    auto windowSize = sf::Vector2u(1500,800);
    CentipedeBody bodyParts;
    auto y = bodyParts.bodyParts.at(0).CentipedeSeg.getPosition().y;
    bodyParts.bodyParts.at(0).moveCentipedeBody(0.1,windowSize); //move left until mushroom
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    bodyParts.bodyParts.at(0).moveCentipedeBody(1,windowSize); //now move right
    auto  y1 = bodyParts.bodyParts.at(0).CentipedeSeg.getPosition().y;

    CHECK(y1>y);
}


TEST_CASE("When bullet hits mushroom, mushroom decreases in size")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    CentipedeBody bodyParts;
    MushroomField mushField;
    Mushroom mush(sf::Vector2f(559,15)); //create mushroom on left of centipede
    mushField.mushrooms.push_front(mush);
    auto it =end(mushField.mushrooms); //mushroom added to back of list
    it--;
    auto s = it->mushroom.getSize().y;
    Bullet bullet(sf::Vector2f(sf::Vector2f(559,15)));//create bullets at mushroom position
    bullets.push_front(bullet);
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    auto s1 = it->mushroom.getSize().y;

    CHECK(s1<s);

}

TEST_CASE("When bullet hits mushroom 4 times, mushroom is destroyed")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    CentipedeBody bodyParts;
    MushroomField mushField;
    Mushroom mush(sf::Vector2f(559,15)); //create mushroom on left of centipede
    mushField.mushrooms.push_front(mush); //make list have only 1 ,mushroom
    auto num1 = mushField.mushrooms.size();
    for(auto b=0; b<4; b++)
    {
        Bullet bullet(sf::Vector2f(sf::Vector2f(559,15)));//create bullets at mushroom position
        bullets.push_front(bullet);
    }
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    auto num2 = mushField.mushrooms.size();
    CHECK(num1-1 == num2);

}

TEST_CASE("When centipede hits bug, true returned")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    CentipedeBody bodyParts;
    MushroomField mushField;
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    bodyParts.bodyParts.at(0).CentipedeSeg.setPosition(600.f,800.f);
    bool x = col.cent_bug(bodyParts.bodyParts, bug); //if true, game class knows and can end the game.
    CHECK(x);

}

///////*********Points**************/////


TEST_CASE("When mushroom is destroyed, points increase by 1")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    CentipedeBody bodyParts;
    MushroomField mushField;
    Mushroom mush(sf::Vector2f(559,15)); //create mushroom on left of centipede
    mushField.mushrooms.push_front(mush); //make list have only 1 ,mushroom
    for(auto b=0; b<4; b++)
    {
        Bullet bullet(sf::Vector2f(sf::Vector2f(559,15)));//create bullets at mushroom position
        bullets.push_front(bullet);
    }
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    CHECK(pointC ==1 );
}

TEST_CASE("When bullet hits centipede head, points increased by 100")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Bullet bullet(sf::Vector2f(600, 15));//create bullet at starting point of centipede
    bullets.push_front(bullet);
    CentipedeBody bodyParts;
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    CHECK(pointC == 100);
}

TEST_CASE("When bullet hits a non-head centipede segment, points increased by 10")
{
    auto pointC = 0;
    Bug bug;
    std::list<Bullet> bullets;
    MushroomField mushField;
    Bullet bullet(sf::Vector2f(640, 15));
    bullets.push_front(bullet);
    CentipedeBody bodyParts;
    Collisions col(bullets, mushField.mushrooms, bodyParts.bodyParts, pointC );
    CHECK(pointC == 10);
}

system("pause");
