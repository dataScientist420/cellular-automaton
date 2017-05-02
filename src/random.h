/****************************************************************************************
 @file: random.h
 @description: TODO
 @author: Victor Neville
 @date: 19/04/2017
****************************************************************************************/

#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random
{
	public:
	    /********************************************************************************
         @name: init_rand
         @description: initializes the random generator
        ********************************************************************************/
		static void init_rand();
		
		/********************************************************************************
         @name: get_rand
         @description: generates a random number between min and max
         @params:
         - int: min number
         - int: max number
         @return: random number
        ********************************************************************************/
		static int get_rand(int, int);
	private:
        /* constructor/destructor are private */
		Random() {}
        ~Random() {}
};

#endif
