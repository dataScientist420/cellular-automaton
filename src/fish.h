/****************************************************************************************
 @file: fish.h
 @description: This file declares the Fish class and it's content.
 @author: Victor Neville
 @date: 20/04/2017
****************************************************************************************/

#ifndef __FISH_H__
#define __FISH_H__

#include "animal.h"

class Fish: public Animal
{
    private:
        /* constants */
        static const int NUM_DAYS_PUBERTY = 30;
        static const int NUM_DAYS_GEST = 15;
        static const int INIT_ENERGY = 3;      
    public:
        /* constants */
        static const int MAX_OBJ = 1000;
        static const int MAX_AGE = 150;         
        
        /********************************************************************************
         @name: Fish
         @description: constructor of Fish object
         @params:
         - int: x position
         - int: y position
         - int: age
        ********************************************************************************/
        Fish(int, int, int = 0);
        
        /********************************************************************************
         @name: ~Fish
         @description: destructor of Fish object
        ********************************************************************************/
        ~Fish();
        
        /********************************************************************************
         @name: inc_age
         @description: increments the age and gestation of a fish
        ********************************************************************************/
        void inc_age();

        /********************************************************************************
         @name: puberty_reached
         @description: indicates if the puberty of a fish has been reached
         @return: true if puberty has been reached, else false
        ********************************************************************************/
        bool puberty_reached() const;

        /********************************************************************************
         @name: reset_gestation
         @description: resets the gestation of a fish
        ********************************************************************************/
        void reset_gestation();

        /********************************************************************************
         @name: is_dead
         @description: indicates the status of a fish
         @return: true if the fish is dead, else false
        ********************************************************************************/
        bool is_dead() const;

        /********************************************************************************
         @name: inc_energy
         @description: increments the energy of a fish
        ********************************************************************************/
        void inc_energy();
};

#endif