/****************************************************************************************
 @file: simulation.h
 @description: This file declares the Simulation class and it's content.
 @author: Victor Neville
 @date: 21/04/2017
****************************************************************************************/

#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <list>
#include "fish.h"
#include "shark.h"
#include "ocean.h"

class Simulation
{
    public:
        /********************************************************************************
         @name: Simulation
         @description: constructor of Simulation object
         @params:
         - int: length of ocean
         - int: width of ocean
         - int: the initial number of fishes
         - int: the initial number of fishes
        ********************************************************************************/ 
        Simulation(int, int, int, int);
        
        /********************************************************************************
         @name: ~Simulation
         @description: destructor of Simulation object
        ********************************************************************************/
        virtual ~Simulation();

        /********************************************************************************
         @name: get_num_animals
         @description: getter of the number of animals
         @params:
         - int &: number of fishes
         - int &: number of sharks
        ********************************************************************************/
        void get_num_animals(int &, int &) const;

        /********************************************************************************
         @name: run
         @description: simulates one iteration of a cellular automaton
        ********************************************************************************/
        void run();

        /********************************************************************************
         @name: print
         @description: prints the content of the ocean
        ********************************************************************************/
        void print() const;
    private:
        /* member variables */
        list<Animal*> fishes; 
        list<Animal*> sharks;
        Ocean<Animal*> *ocean;

        /********************************************************************************
         @name: add_animal
         @description: adds a new animal of type Animal::animal_t
         @params:
         - Animal::animal_t: type of animal
        ********************************************************************************/
        void add_animal(Animal::animal_t);

        /********************************************************************************
         @name: remove_dead
         @description: removes all dead animals of type Animal::animal_t
         @params:
         - Animal::animal_t: type of animal
        ********************************************************************************/
        void remove_dead(Animal::animal_t);

        /********************************************************************************
         @name: kill_prey
         @description: manages the elimination of a prey
         @params:
         - Animal &: the animal that kills the prey
        ********************************************************************************/
        void kill_prey(Animal&);

        /********************************************************************************
         @name: give_birth
         @description: manages the birth of a new baby
         @params:
         - Animal &: the animal that gives birth
        ********************************************************************************/
        void give_birth(Animal&);

        /********************************************************************************
         @name: move_animal
         @description: manages the movement of an animal
         @params:
         - Animal &: the animal that has to be moved
        ********************************************************************************/
        void move_animal(Animal&);

        /********************************************************************************
         @name: evolve
         @description: manages the evolution of the animals of type Animal::animal_t
         @params:
         - Animal::animal_t: type of animal
        ********************************************************************************/
        void evolve(Animal::animal_t);
};

#endif
