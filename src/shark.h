/****************************************************************************************
 @file: shark.h
 @description: This file declares the Shark class and it's content.
 @author: Victor Neville
 @date: 20/04/2017
****************************************************************************************/

#ifndef __SHARK_H__
#define __SHARK_H__

#include "animal.h"

class Shark: public Animal
{
    private:
        /* constants */
        static const int NUM_DAYS_DIGESTION = 10;
        static const int NUM_DAYS_PUBERTY = 90;
        static const int NUM_DAYS_GEST = 30;
        static const int INIT_ENERGY = 15;    
    public:
        /* constants */
        static const int MAX_AGE = 1500;         
        
        /********************************************************************************
         @name: Shark
         @description: constructor of Shark object
         @params:
         - int: x position
         - int: y position
         - int: age
        ********************************************************************************/
        Shark(int, int, int = 0);
        
        /********************************************************************************
         @name: ~Shark
         @description: destructor of Shark object
        ********************************************************************************/
        ~Shark();
        
        /********************************************************************************
         @name: inc_age
         @description: increments the age and gestation of a shark
        ********************************************************************************/
        void inc_age();

        /********************************************************************************
         @name: puberty_reached
         @description: indicates if the puberty of a shark has been reached
         @return: true if puberty has been reached, else false
        ********************************************************************************/
        bool puberty_reached() const;

        /********************************************************************************
         @name: reset_gestation
         @description: resets the gestation of a shark
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
