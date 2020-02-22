
#include "checkers.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotors.h"

//Enigma Class header file
class Enigma {
    
    Plugboard* selected_plugboard ;
    Reflector* selected_reflector ;
    int setup_status = 0 ;
    int number_of_rotors = 0 ;
    Rotor* rotorPtr[] ;
    
public:
    
    /*The constructor of the engima class intantiates the whole engima and all of
    its class components*/
    Enigma(int x , char* y[]) ;
    
    /*Function returns the setup status of engima for main to return*/
    int get_setup_status() ;
    
    /*Function representing the functionality of the engima machine
     the input letter (int) is fed through the different components
     and is modified  along the way*/
    void encrypt_letter(int& input) ;
    
    /*The destructor of the engima class deletes the class components
     from the heap/dynamic memory*/
    ~Enigma() ;

} ;


   

    
