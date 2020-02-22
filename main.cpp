#include <iostream>

#include "errors.h"
#include "enigma.h"

using namespace std ;

int main (int argc ,char* argv[])
{
    //Minimum number of input parameters
    if (argc < 3)
    {
        cerr << "usage: enigma plugboard-file" ;
        cerr<< " reflector-file (<rotor-file>)* rotor-positions" << endl ;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS ;
    }
    
    Enigma* selected_enigma ;
    selected_enigma = new Enigma(argc,argv) ;
    int setup_status = 0 ;
    setup_status = selected_enigma->get_setup_status() ;
    if(setup_status!= 0)
    {
        return setup_status ;
    }
    int input ;
    char letter ;
    cin >> ws ;
    
    while(cin >> ws >>letter)
    {
        if((letter<65||letter>90) && static_cast<int>(letter) >0)
        {
            cerr<< letter << " is not a valid input character (input characters must";
            cerr<< " be upper case letters A-Z)!" << endl ;
            return INVALID_INPUT_CHARACTER ;
        }
        if(static_cast<int>(letter) == -1)
        {
            break ;
        }
        input = static_cast<int>(letter - 'A') ;
        selected_enigma->encrypt_letter(input) ;
        cout << static_cast<char>(input+'A') ;
    }
    
    return NO_ERROR ;
}
