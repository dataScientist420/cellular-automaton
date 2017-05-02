/****************************************************************************************
 @file: ocean.h
 @description: This file implements the Ocean generic class.
 @author: Victor Neville
 @date: 19/04/2017
****************************************************************************************/

#ifndef __OCEAN_H__
#define __OCEAN_H__

#include <vector>
#include <cstdlib>
#include "random.h"

using namespace std;

template <class T> class Ocean
{
     public:
        /* Enumerated type for the eight directions */
        typedef enum {NORTH, NORTH_EAST, EAST, SOUTH_EAST, 
                        SOUTH, SOUTH_WEST, WEST, NORTH_WEST} dir_t;
        
        /********************************************************************************
         @name: Ocean
         @description: constructor of Ocean object that initializes the 2D vector
         @params:
         - int: vector length
         - int: vector width
        ********************************************************************************/
        Ocean<T>(int length=0, int width=0)
        {
            this->length = length;
            this->width = width;
            
            for (int i=0; i<length; i++) {
            
                /* new vector filled with NULLs */
                vector<T> array(width, NULL); 
                
                /* add new vector to the water (2D vector) */
                water.push_back(array);
            }
        }
        
        /********************************************************************************
         @name: ~Ocean
         @description: destructor of Ocean object that clears the 2D vector
        ********************************************************************************/
        virtual ~Ocean<T>()
        {
            for (int i=0; i<(int)water.size(); i++) {
                water[i].clear();
            }
        }
        
        /********************************************************************************
         @name: get_elem
         @description: getter which gets the element T at the position (x, y)
         @params:
         - int: x position
         - int: y position
         @return: the element at the position (x, y)
        ********************************************************************************/
        T get_elem(int x_pos, int y_pos) const { return water[y_pos][x_pos]; }
        
        /********************************************************************************
         @name: set_elem
         @description: setter which sets the element at the position (x, y) to val
         @params:
         - int: x position
         - int: y position
         - T: value to be set
        ********************************************************************************/
        void set_elem(int x_pos, int y_pos, T val) { water[y_pos][x_pos] = val; }
        
        /********************************************************************************
         @name: empty_rand_pos
         @description: generates an empty random position
         @params:
         - int &: x position
         - int &: y position
        ********************************************************************************/
        void empty_rand_pos(int &x_pos, int &y_pos) const
        {
            do {
                x_pos = Random::get_rand(0, width-1);
                y_pos = Random::get_rand(0, length-1);
            } while (water[y_pos][x_pos] != NULL);
        }

        /********************************************************************************
         @name: neighbor_pos
         @description: gets the coordinates (x, y) of the desired direction (dir)
         @params:
         - int &: x position
         - int &: y position
         - dir_t: direction
        ********************************************************************************/
        void neighbor_pos(int &x_pos, int &y_pos, dir_t dir) const
        {
			switch (dir) {
		        case NORTH:      y_pos-=1; break;
		        case NORTH_EAST: x_pos+=1; y_pos-=1; break;
		        case EAST:       x_pos+=1; break;
		        case SOUTH_EAST: x_pos+=1; y_pos+=1; break;
		        case SOUTH:      y_pos+=1; break;
		        case SOUTH_WEST: x_pos-=1; y_pos+=1; break;
		        case WEST:       x_pos-=1; break;
		        case NORTH_WEST: x_pos-=1; y_pos-=1; break; 
	        }

	        /* verify screen limits */
	        if (x_pos >= this->width)
		        x_pos = 0;
	        else if (x_pos < 0)
		        x_pos = this->width-1;
	        if (y_pos >= this->length)
		        y_pos = this->length-1;
	        else if (y_pos < 0)
		        y_pos = 0;
        }
        
        /********************************************************************************
         @name: rand_neighbor_pos
         @description: gets the coordinates (x, y) of an empty random neighbor
         @params: 
         - int: position x
         - int: position y
        ********************************************************************************/
        void rand_neighbor_pos(int &x_pos, int &y_pos) const
        { 
            dir_t direction;
	        int tmp_x_pos, tmp_y_pos;

	        do {
		        tmp_x_pos = x_pos;
		        tmp_y_pos = y_pos;
		        direction = (dir_t)Random::get_rand(NORTH, NORTH_WEST);
		        neighbor_pos(tmp_x_pos, tmp_y_pos, direction);
		
	        } while (water[tmp_y_pos][tmp_x_pos] != NULL);

	        x_pos = tmp_x_pos;
	        y_pos = tmp_y_pos;   
        }
        
        /********************************************************************************
         @name: num_neighbors
         @description: computes the number of neighbors of coordinates (x, y) 
         @params: 
         - int: position x
         - int: position y
         @return: number of neighbors
        ********************************************************************************/
        int num_neighbors(int x_pos, int y_pos) const
        {
            int val = 0;

	        for (int dir = NORTH; dir <= NORTH_WEST; dir++) {
		        int tmp_x = x_pos;
		        int tmp_y = y_pos;
		        neighbor_pos(tmp_x, tmp_y, (dir_t)dir);

		        if (!water[tmp_y][tmp_x])
			        val++;
	        }
	        return val;   
        }

        /********************************************************************************
         @name: get_length
         @description: getter which returns the 2D vector length
         @return: length
        ********************************************************************************/
        int get_length() const { return length; }

        /********************************************************************************
         @name: get_width
         @description: getter which returns the 2D vector width
         @return: width
        ********************************************************************************/
        int get_width() const { return width; }
    private:
        /* member variables */
        int length;
        int width;
        vector<vector<T> > water;
};

#endif
