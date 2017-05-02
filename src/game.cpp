/****************************************************************************************
 @file: game.cpp
 @description: This file implements the Game class.
 @author: Victor Neville
 @date: 21/04/2017
****************************************************************************************/
#include <iostream>
#include "random.h"
#include "game.h"

using namespace std;

/****************************************************************************************
 Constructor of Game object.
****************************************************************************************/
Game::Game(int length, int width, int num_fishes, int num_sharks)
{   
    ocean = new Ocean<Animal*>(length, width);
    
    Random::init_rand();
    
    for (int i = 0; i < num_fishes; i++) {
        add_animal(Animal::TYPE_FISH);   
    }
    for (int i = 0; i < num_sharks; i++) {
        add_animal(Animal::TYPE_SHARK);   
    }
}

/****************************************************************************************
 Destructor of Game object.
****************************************************************************************/
Game::~Game()
{
    list<Animal*>::iterator animal;
    
    /* delete all dynamic memory allocations */
    for (animal = fishes.begin(); animal != fishes.end(); animal++) {
           delete *animal;
    }
    for (animal = sharks.begin(); animal != sharks.end(); animal++) {
        delete *animal;
    }
    fishes.clear();
    sharks.clear();
    delete ocean;
}

/****************************************************************************************
 Getter of the number of animals.
****************************************************************************************/
void Game::get_num_animals(int &num_fishes, int &num_sharks)  const
{
    num_fishes = fishes.size();
    num_sharks = sharks.size();
}

/****************************************************************************************
 Adds a new animal of type Animal::animal_t.
****************************************************************************************/
void Game::add_animal(Animal::animal_t type)
{
    int x_pos, y_pos;
    Animal *animal = NULL;

    /* get empty random position in the ocean */
    ocean->empty_rand_pos(x_pos, y_pos);

    /* create the right type of animal */    
    switch (type) {
        case Animal::TYPE_FISH:
            animal = new Fish(x_pos, y_pos, Random::get_rand(1, Fish::MAX_AGE));
            fishes.push_back(animal);
            break;
        case Animal::TYPE_SHARK:
            animal = new Shark(x_pos, y_pos, Random::get_rand(1, Shark::MAX_AGE));
            sharks.push_back(animal);
            break;
    }
    /* add the animal to ocean */
    ocean->set_elem(x_pos, y_pos, animal);
}

/****************************************************************************************
 Manages the movement of an animal.
****************************************************************************************/
void Game::move_animal(Animal &animal)
{
    int x_pos, y_pos;

    animal.get_position(x_pos, y_pos);

    /* if the animal has empty neighbors */
    if (ocean->num_neighbors(x_pos, y_pos) > 0) {

        ocean->set_elem(x_pos, y_pos, NULL);

        /* choose a random neighbor */
        ocean->rand_neighbor_pos(x_pos, y_pos);

        /* move the animal at his new position */
        ocean->set_elem(x_pos, y_pos, &animal);

        /* update the animal coordinates */
        animal.set_position(x_pos, y_pos);
    }
}

/****************************************************************************************
 Manages the elimination of a prey. 
****************************************************************************************/
void Game::kill_prey(Animal &animal)
{
    /* only sharks can kill preys */
    if (animal.get_type() == Animal::TYPE_SHARK) {
        int x_pos, y_pos;
        bool killed = false;
        int dir = Ocean<Animal*>::NORTH;

        animal.get_position(x_pos, y_pos);

        /* check neighbors */
        while (dir <= Ocean<Animal*>::NORTH_WEST && !killed) {
            int tmp_x_pos = x_pos;
            int tmp_y_pos = y_pos;

            ocean->neighbor_pos(tmp_x_pos, tmp_y_pos, (Ocean<Animal*>::dir_t)dir);
            Animal &neighbor = *ocean->get_elem(tmp_x_pos, tmp_y_pos);

            /* kill the prey */
            if (&neighbor && neighbor.get_type() == Animal::TYPE_FISH) {            
                neighbor.kill();
                animal.inc_energy();
                killed = true;
            } else {
                dir++;
            }
        }
    }
}

/****************************************************************************************
 Manages the birth of a new baby.
****************************************************************************************/
void Game::give_birth(Animal &mother)
{
    int x_pos, y_pos;

	mother.get_position(x_pos, y_pos);

    /* reset fish gestation if miscarriage or if max number of fish has been reached */
    /* 33% chance of fish having a miscarriage */
    if (mother.get_type() == Animal::TYPE_FISH && (fishes.size() >= Fish::MAX_OBJ || 
        !(rand()%3))) {
        mother.reset_gestation();

    /* add new baby to the list when there is neighbors */ 
    } else if (ocean->num_neighbors(x_pos, y_pos) > 0) {
        ocean->rand_neighbor_pos(x_pos, y_pos);
        Animal *baby = NULL;
                    
        switch (mother.get_type()) {
            case Animal::TYPE_FISH:
                baby = new Fish(x_pos, y_pos);
                fishes.push_back(baby);
                break;
            case Animal::TYPE_SHARK:
                baby = new Shark(x_pos, y_pos);
                sharks.push_back(baby);
                break;
        }
        ocean->set_elem(x_pos, y_pos, baby);
        
        /* adjust mother's parameters after birth */  
        mother.reset_gestation();       
        mother.dec_energy();            
    }
}

/****************************************************************************************
 Manages the evolution of the animals of type Animal::animal_t.
****************************************************************************************/
void Game::evolve(Animal::animal_t type)
{
    list<Animal*>::iterator iter;
    list<Animal*> *animals;

    /* point to the correct type of animals */
    switch (type) {
        case Animal::TYPE_FISH:
            animals = &fishes;
            break;
        case Animal::TYPE_SHARK:
            animals = &sharks;
            break;
    }
    /* animals movement, birth and killing management */
    for (iter = animals->begin(); iter != animals->end(); iter++) {
        Animal &animal = **iter;
        animal.inc_age();

        if (animal.get_type() == Animal::TYPE_SHARK)
            animal.dec_energy();

        if (animal.puberty_reached()) {           
            give_birth(animal);
        } else {
            if (animal.get_type() == Animal::TYPE_SHARK) {
                kill_prey(animal);
            }
            move_animal(animal);
        }                          
    }
}

/****************************************************************************************
 Removes all dead animals of type Animal::animal_t.
****************************************************************************************/
void Game::remove_dead(Animal::animal_t type)
{ 
    list<Animal*>::iterator iter;
    list<Animal*> *animals = NULL;

    /* point to the correct type of animals */
    switch (type) {
        case Animal::TYPE_FISH:
            animals = &fishes;
            break;
        case Animal::TYPE_SHARK:
            animals = &sharks;
            break;
    }
    iter = animals->begin();

    /* browse list and remove the dead */
    while (iter != animals->end()) {
        Animal &animal = **iter;

        if (animal.is_dead()) {
            int x_pos, y_pos;

            /* remove the animal from list and ocean */
            animal.get_position(x_pos, y_pos);
			ocean->set_elem(x_pos, y_pos, NULL);
            iter = animals->erase(iter);
            delete &animal;
        } else { 
            iter++;
        }                           
    } 
}

/****************************************************************************************
 Simulates one iteration of a cellular automaton.
****************************************************************************************/
void Game::simulate()
{
    /* manage animals evolution */
    evolve(Animal::TYPE_FISH);
    evolve(Animal::TYPE_SHARK);

    /* remove dead animals */
    remove_dead(Animal::TYPE_FISH);
    remove_dead(Animal::TYPE_SHARK);
}

/****************************************************************************************
 Prints the content of the ocean.
****************************************************************************************/
void Game::print() const
{
    int length = ocean->get_length();
    int width = ocean->get_width();

    /* display all elements in the ocean */
    for (int y_pos = 0; y_pos < length; y_pos++) {
        for (int x_pos = 0; x_pos < width; x_pos++) {
            Animal &ref = *ocean->get_elem(x_pos, y_pos);

            if (!&ref)
                cout << " .";
            else if (ref.get_type() == Animal::TYPE_FISH)
                cout << " F";
            else if (ref.get_type() == Animal::TYPE_SHARK) 
                cout << " S";
        }
        cout << endl;
    }
    cout << endl;
}

/***************************************************************************************/
