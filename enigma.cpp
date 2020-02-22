#include <iostream>
#include <fstream> 
#include <cstring>

#include "errors.h"
#include "enigma.h"

using namespace std ;

    
Enigma::Enigma(int x , char* y[])
{
    //Instantiates a plugboard
    selected_plugboard = new Plugboard(y[1]) ;
    int plugboard_status = selected_plugboard->get_plugboard_status() ;
    if(plugboard_status!=0)
    {
        setup_status = plugboard_status ;
    }
    
    //Only continues with "setting up the enigma if the plugboard is well formed
    if(setup_status == 0)
    {
        //Instantiates a reflector
        selected_reflector = new Reflector(y[2]) ;
        int reflector_status = selected_reflector->get_reflector_status() ;
        if(reflector_status!= 0)
        {
            setup_status = reflector_status ;
        }
    }
    

    /*Only continues with "setting up the enigma if the plugboard & reflector
    are well formed*/
    if(setup_status == 0)
    {
        number_of_rotors = x - 4 ;
        
        if(number_of_rotors > 0)
        {
            
    /*Sets up each rotor for the number of rotors specified by initialsing a rotor
    and then moving the rotor the required starting position */
            for(int i = 0 ; i < number_of_rotors ; i++)
            {
                rotorPtr[i] = new Rotor(y[x-2-i],x[y-1],i,number_of_rotors) ;
                int rotor_status = rotorPtr[i]->get_rotor_status();
                if(rotor_status!=0)
                {
                    setup_status = rotor_status ;
                    break ;
                }
                
                rotorPtr[i]->move_to_starting_position() ;                                                                            
            }
        }
    }
}
    
int Enigma::get_setup_status() { return setup_status ; }
    
void Enigma::encrypt_letter(int& input)
{
    //Putting the character through the plugboard (right to left).
    for(int j = 0 ; j<selected_plugboard->get_plugboard_pairs();j++)
    {
        if(selected_plugboard->get_plugboard(j,0)==input)
        {
            input  = selected_plugboard->get_plugboard(j,1);
        }else if (selected_plugboard->get_plugboard(j,1)==input)
        {
            input = selected_plugboard->get_plugboard(j,0);
        }
    }
    
    if(number_of_rotors > 0)
    {   
    
        //For every input character turn the right most rotor once
        rotorPtr[0]->turn_rotor() ;
    
        //If the current rotor gets to its notch position(s) move the next rotor by one
        for(int j = 0 ; j<(number_of_rotors-1) ; j++)
        {
            for ( int q = 0 ; q < rotorPtr[j]->get_number_of_notches() ; q++)
            {
                
                if(rotorPtr[j]->get_top_position() == rotorPtr[j]->get_notch_position(q))
                {
                    rotorPtr[j+1]->turn_rotor() ;
                }
            }
        }
    

        //Putting the character through the rotors right to left (before the reflector).
        for(int j = 0 ; j<(number_of_rotors) ; j++)
        {
            rotorPtr[j]->encryption_rtl(input) ;
        }
    }
    
    //Putting the character through the reflector
    for(int j = 0 ; j<=12 ; j++) 
    {
        if(selected_reflector->get_reflector_number(j,0)==input)
        {
            input = selected_reflector->get_reflector_number(j,1);
            
        }else if (selected_reflector->get_reflector_number(j,1)==input)
        { 
            input = selected_reflector->get_reflector_number(j,0);
        }
    }
    
    if(number_of_rotors > 0)
    {
        //Putting the character through the rotors left to right (after the reflector).
        for(int j = (number_of_rotors-1) ; j>= 0 ; j--)
        {
            rotorPtr[j]->encryption_ltr(input) ;
        }
    }
    
    //Putting the character through the plugboard (left to right).
    for(int j = 0 ; j<selected_plugboard->get_plugboard_pairs();j++)
    {
        if(selected_plugboard->get_plugboard(j,0)==input)
        {
            input = selected_plugboard->get_plugboard(j,1);
        }else if (selected_plugboard->get_plugboard(j,1)==input)
        {
            input = selected_plugboard->get_plugboard(j,0);
        }
    }
}

Enigma::~Enigma(){
    
    delete selected_plugboard ;
    selected_plugboard = NULL ;
    delete selected_reflector ;
    selected_reflector = NULL ;
    if(number_of_rotors > 0)
    {
        for(int i = 0 ; i < number_of_rotors ; i++)
        {
            delete rotorPtr[i] ;
            rotorPtr[i] = NULL ;
        }
    }
    
    delete this ;

}
