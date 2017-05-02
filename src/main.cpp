/****************************************************************************************
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 @file: main.cpp
 @description: This file is the entry point of the code. 
               The program implements a cellular automaton.
               Therefore, it simulates the evolution of 
               an ecosystem over time with the prey (fishes) 
               and predator (sharks) model.
                 
 @author: Victor Neville
 @date: 19/04/2017
****************************************************************************************/
#include "game.h"
#include <iostream>
#include <unistd.h>

using namespace std;

/* Constants */
#define DELAY           1000000
#define MAX_TIME        2000
#define OCEAN_LENGTH    20
#define OCEAN_WIDTH     30
#define INIT_NUM_FISHES 100
#define INIT_NUM_SHARKS 5

/****************************************************************************************
                                    Entry Point
****************************************************************************************/
int main()
{   
    int num_fishes, num_sharks, time_iter = 0;
    Game game(OCEAN_LENGTH, OCEAN_WIDTH, INIT_NUM_FISHES, INIT_NUM_SHARKS);

    /* simulate until one of the animal species is dead or MAX_ITERATIONS is reached */
    do {
        system("clear");
        game.simulate();
        game.print();
        game.get_num_animals(num_fishes, num_sharks);

        cout << "time: " << ++time_iter << " sec, ";
        cout << "fishes: " << num_fishes << ", ";
        cout << "sharks: " << num_sharks << endl;
        usleep(DELAY);
        
    } while (time_iter < MAX_TIME && num_fishes > 0 && num_sharks > 0);

    return 0;
}

/***************************************************************************************/
