#ifndef MUSHROOMFIELD_H_INCLUDED
#define MUSHROOMFIELD_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Mushroom.h"
#include <list>

/** \file MushroomField.h
    \brief Contains code for constructing a field of mushrooms
    This class can construct a list of randomly placed mushrooms within the window
 */
/** \class MushroomField
   \brief Contains code for constructing a field of randomly placed mushrooms
*/

class MushroomField
{
public:


    /** \brief Constructor for the number of mushrooms
    */
    MushroomField();

    /** \fn void Make_mushrooms()
    *  \brief This function creates a field of randomly placed mushrooms
    * \param windowSize Is the size of the window (1500,800) so that all mushrooms are created within the screen
    */
    void Make_mushrooms(const sf::Vector2u &windowSize);

    /** \brief This is a list of mushroooms for easy insertion and deletion
     */
    std::list<Mushroom>mushrooms;

private:
    bool enoughMushrooms;
    long long unsigned int max_mushrooms;
};

#endif // MUSHROOMFIELD_H_INCLUDED
