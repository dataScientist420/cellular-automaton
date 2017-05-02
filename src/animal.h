/****************************************************************************************
 @file: animal.h
 @description: This file declares the Animal class and it's content.
 @author: Victor Neville
 @date: 19/04/2017
****************************************************************************************/

#ifndef __ANIMAL_H__
#define __ANIMAL_H__

class Animal
{
    public:
        typedef enum { TYPE_FISH, TYPE_SHARK } animal_t;

        /********************************************************************************
         @name: Animal
         @description: constructor of Animal object
         @params:
         - int: x position
         - int: y position
         - int: age
         - int: energy
         - int: gestation
         - animal_t: type
        ********************************************************************************/
        Animal(int, int, int, int, int, animal_t);

        /********************************************************************************
         @name: ~Animal
         @description: destructor of Animal object
        ********************************************************************************/
        virtual ~Animal() {}
        
        /********************************************************************************
         @name: get_position
         @description: getter for an animal position
         @params:
         - int &: x position
         - int &: y position
        ********************************************************************************/
        void get_position(int &, int &) const;
        
        /********************************************************************************
         @name: set_position
         @description: setter for an animal position
         @params:
         - int: x position
         - int: y position
        ********************************************************************************/
        void set_position(int, int);
        
        /********************************************************************************
         @name: get_energy
         @description: getter for an animal energy
         @return: the animal energy
        ********************************************************************************/
        int get_energy() const;
        
        /********************************************************************************
         @name: dec_energy
         @description: decrements the energy of an animal
        ********************************************************************************/
        void dec_energy();

        /********************************************************************************
         @name: kill
         @description: resets the energy of an animal
        ********************************************************************************/
        void kill();

        /********************************************************************************
         @name: get_type
         @description: getter for an animal type
         @return: the animal type
        ********************************************************************************/
        animal_t get_type() const;

        /* pure virtual functions */
        virtual void inc_age() = 0;
        virtual bool puberty_reached() const = 0;
        virtual void reset_gestation() = 0;
        virtual bool is_dead() const = 0;
        virtual void inc_energy() = 0;
    protected:
        /* member variables */
        int posx, posy;
        int age;
        int energy;
        int gestation;
        animal_t type;
};

#endif
