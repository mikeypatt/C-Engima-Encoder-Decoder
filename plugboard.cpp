//Definition (.cpp) file for the plugboard class linking to plugbloard.h
#include <iostream>
#include "errors.h"
#include "plugboard.h"
#include "checkers.h"

using namespace std ;

Plugboard::Plugboard(const char *filename) : filename(filename) {
        
        Checkers plugboardchecker ;
        
        int status,number_counter = 0;
        
        /*Initialises the plugboard array with an illegal number (99) to ensure
        the checker function does not throw an error unnecessarily. */
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                plug_number_array[i][j] = 99;
            }
        }
        status = plugboardchecker.checker(filename, plug_number_array,
                                            number_counter,1) ;
                                            
        /*If the file was not well formed set the member status checker to display
                                                        the error number*/
        if(status != 0)
        {
            if(status == SHARED_ERROR) /*Plugboard constructor changes shared error
                                                            the revelent one. */
            {
                cerr << "The is more than one instance of a number in the" ;
                cerr << " plugboard file" << endl;
                status = IMPOSSIBLE_PLUGBOARD_CONFIGURATION ;
            }
            plugboard_status = status ;
        }
        number_of_pairs = number_counter/2 ;
}
//Functions to access the various members of the plugboard class.
int Plugboard::get_plugboard(int j, int i) {return plug_number_array[j][i] ;}
int Plugboard::get_plugboard_pairs() {return number_of_pairs ;}
int Plugboard::get_plugboard_status(){return plugboard_status ;}   


