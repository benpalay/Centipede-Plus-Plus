#ifndef CENTIPEDE_H_INCLUDED
#define CENTIPEDE_H_INCLUDED

/** \file Game.h
    \brief Contains all the main code for presentation and game play

    This class initializes all the game objects, initializes game variables,
    renders the window, and calls functions for game play
 */

/** \class Game
   \brief Contains all the main code for presentation and game play
*/
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Bug.h"
#include "Bullet.h"
#include "CentipedeBody.h"
#include "MushroomField.h"
#include "Collisions.h"

using namespace sf;

class Game
{
public:

    /** \fn void playGame()
     *  \brief This function provides the implementation of the game

      The window is rendered, events are polled,
      the function for implementing game play is called: this is where the object interact.
      The objects are drawn and the window is displayed.

     */
    void playGame();


    /** \brief This constructs a game object

        Game variables, font and text are initialized in the constructor

    */
    Game();

private:
    void initializeVars();
    void initializeFont();
    void initializeText();
    void  initializeWindow();
    Clock clock;
    Clock timer;
    Time timing;
    sf::Font font;
    sf::Text message;
    sf::Text score;
    Bug bug;
    std::list<Bullet> bullets;
    CentipedeBody centBody;
    MushroomField mushroomField;
    bool playing;
    float deltaTime;
    int pointCounter;
    void play(sf::Vector2u windowSize);
    void make_bullet();
    void shoot_bullets (float deltaTime);
    void drawing(sf::RenderTarget& x, bool playing);
    sf::RenderWindow window;
};

#endif // CENTIPEDE_H_INCLUDED
