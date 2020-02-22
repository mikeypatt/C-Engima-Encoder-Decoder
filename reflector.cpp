//Reflector class definition file (.cpp) linking to reflector.h

#include <iostream>
#include "reflector.h"
#include "checkers.h"
#include "errors.h"

using namespace std ;
    
Reflector::Reflector(const char *filename) : filename(filename) 
{
    Checkers reflectorchecker ;
    
    int status, number_counter = 0 ;
    
    /*Initialises the reflector array with an illegal number (99) to ensure
    the checker function does not throw an error unnecessarily. */
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            reflect_array[i][j] = 99;
        }
    }
    
    status = reflectorchecker.checker(filename, reflect_array,number_counter);
    /*If the file was not well formed set the member status checker to display
                                                        the error number*/
    if(status != 0)
    {
        if(status==SHARED_ERROR)
        {
            cerr << "You are not allowed to map a number to itself" ;
            status = INVALID_REFLECTOR_MAPPING ;
        }
        reflector_status = status ;
    }
    
    number_of_pairs = number_counter/2 ;
    
    if(reflector_status == 0)
    {
        if(number_of_pairs !=13)
        {
            cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf";
            status = INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS ;
        }
        reflector_status = status ;
    }
}

//Functions to access the various members of the reflector class (See reflector.h)
int Reflector::get_reflector_number(int j, int i) {return reflect_array[j][i] ;}
int Reflector::get_reflector_status() {return reflector_status ;}
