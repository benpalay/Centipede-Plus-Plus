#include "Game.h"
#include <sstream>
using namespace sf;

/** \file Game.cpp
 */
void Game::initializeVars()
{
    timing= seconds(0.1f);
    playing=false;
    pointCounter = 0;
}

void Game::initializeFont()
{
    if(!font.loadFromFile("resources/sansation.ttf"))
        exit(EXIT_FAILURE);
}

void Game::initializeText()
{
    message.setFont(font);
    message.setCharacterSize(30);
    message.setPosition(300.f, 300.f);
    message.setFillColor(Color::White);
    message.setString("Welcome to CENTIPEDE!\nIf the Centipede gets you, you lose!\nIf you shoot it in time, you win!\n\nUse arrow keys to move the bug\nPress B to shoot a bullet\nPress space to start\n\nPoints: Mushroom: 1(4 hits), Centipede Part: 10, Centipede Head: 100");
    score.setFont(font);
    score.setCharacterSize(45);
    score.setPosition(1200.f, 20.f);
    score.setFillColor(Color::White);
}


Game::Game()
{
    initializeVars();
    initializeFont();
    initializeText();
}


void Game::playGame()
{
    RenderWindow window(VideoMode(1500,800), "CENTIPEDE++", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    auto    w = window.getSize();
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if((event.type == Event::Closed) ||
                    ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
            {
                window.close();
                break;
            }
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space))
            {
                //start the game
                if(!playing)
                {
                    playing = true;
                    clock.restart();
                }
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
            {
                make_bullet();
            }
        }

        play(w);  //game implementation
        drawing(window,playing); //rendering objects on the screen
        window.display();
    }
}


void Game::play(sf::Vector2u windowSize)
{
    if(playing)
    {
        deltaTime = clock.restart().asSeconds();
        bug.moveBug(deltaTime,windowSize);
        centBody.moveCentipede(deltaTime,windowSize);
        shoot_bullets(deltaTime);
        mushroomField.Make_mushrooms(windowSize);
        Collisions col(bullets, mushroomField.mushrooms, centBody.bodyParts, pointCounter); //can change to passing in just the object, make vectors private
        if(col.cent_bug(centBody.bodyParts, bug) || centBody.bodyParts.size() == 0)
        {
            playing = false; // bug hit or centipede destroyed, game over/life lost?, need to replay
        }
    }
    if(timer.getElapsedTime() > timing)
    {
        timer.restart();
    }
}

void Game::make_bullet()
{
    if(bullets.size()<4)
    {
        Bullet bullet(bug.bug.getPosition());//create bullet at bug's position
        bullets.push_front(bullet); //need to do here for 1 shot at a time ease
    }
}

void Game::shoot_bullets (float deltaTime)
{
    for (auto it = begin(bullets); it!=end(bullets); it++)
    {
        auto i = *it;
        it->shootBullet(deltaTime);
        if(i.bullet.getPosition().y<0.f)
        {
            bullets.erase(it--); //if bullet goes out of screen,  erase
        }
    }
}


void Game::drawing(sf::RenderTarget& x,bool playing)
{
    x.clear(Color(0, 0, 0));
    if(playing)
    {
        x.draw(bug.bug);
        std::stringstream instring;
        instring << pointCounter;
        score.setString("Score: " +instring.str());
        x.draw(score);
        for (long long unsigned int i =0; i<centBody.bodyParts.size(); i++)
        {
            //x.draw(centBody.bodyParts.at(i).CentipedeHead);
            x.draw(centBody.bodyParts.at(i).CentipedeSeg);
        }
        for (auto it = begin(bullets); it!=end(bullets); it++)
        {
            auto i = *it;
            x.draw(i.bullet);
        }
        for (auto it = begin(mushroomField.mushrooms); it!=end(mushroomField.mushrooms); it++)
        {
            auto i =*it;
            x.draw(i.mushroom);
        }
    }
    else
    {
        x.draw(message);
        x.draw(score);
    }
}
