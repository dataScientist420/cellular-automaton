/****************************************************************************************
 @file: fish.cpp
 @description: This file implements the Fish class.
 @author: Victor Neville
 @date: 20/04/2017
****************************************************************************************/
#include "fish.h"

/****************************************************************************************
 Constructor of Fish object.
****************************************************************************************/
Fish::Fish(int px, int py, int age): 
Animal(px, py, age, Fish::INIT_ENERGY, 0, Animal::TYPE_FISH) {}

/****************************************************************************************
 Destructor of Fish object.
****************************************************************************************/
Fish::~Fish() {}

/****************************************************************************************
 Increments the age and gestation of a fish.
****************************************************************************************/
void Fish::inc_age()
{
    if (++age > Fish::NUM_DAYS_PUBERTY)
        gestation++;
}

/****************************************************************************************
 Indicates if the puberty of a fish has been reached.
****************************************************************************************/
bool Fish::puberty_reached() const
{
    return (age >= Fish::NUM_DAYS_PUBERTY && gestation > Fish::NUM_DAYS_GEST);
}

/****************************************************************************************
 Resets the gestation of a fish.
****************************************************************************************/
void Fish::reset_gestation()
{ 
    gestation = -Fish::NUM_DAYS_GEST; 
}

/****************************************************************************************
 Indicates the status of a fish.
****************************************************************************************/
bool Fish::is_dead() const
{
    return (age > Fish::MAX_AGE || energy <= 0);
}

/****************************************************************************************
 Increments the energy of a fish.
****************************************************************************************/
void Fish::inc_energy() {}

/***************************************************************************************/