//Rotor class definition file (For full function descriptions see rotors.h)

#include "rotors.h"
#include "checkers.h"

using namespace std ;
    
Rotor::Rotor(const char* filename,const char* positionfilename, int rotor_number,
                            int total_number_of_rotors) : filename(filename) {
        
    Checkers rotorchecker ;
    int status ,    position_status ;
    
    status = rotorchecker.rotor_checker(filename, forward_rotor_array,
                                notch_postion,number_of_notches) ;
    if(status != 0)
    {
        rotor_status = status ;
    }
    
    /*Check to see if an error was first thrown in the main file
     before preceding*/
    if (rotor_status == 0)
    {
        position_status = rotorchecker.position_checker(positionfilename,
                rotor_number,total_number_of_rotors,starting_position) ;
                
        if(position_status != 0)
        {
            rotor_status =  position_status ;
        }
    }
    /*Check to see if an error was thrown in the position file
     before preceding*/
    if (rotor_status == 0)
    {
        for(int i=0;i<=25;i++)
        {
            int number = get_forward_rotor_number(i) ;
            reverse_rotor_array[number] = i ;
        }
        
    /*Moving array creation - the moving array is the representation
     of what an external viewer would see as the rotor moves from the engigma
     box*/
        for(int j = 0 ; j <=25 ; j++)
        {
            moving_array[j] = j;
        }
    }
}
   
int Rotor::get_rotor_starting_postion() { return starting_position ;}
int Rotor::get_forward_rotor_number(int j) { return forward_rotor_array[j] ;}
int Rotor::get_reverse_rotor_number(int j) { return reverse_rotor_array[j] ;}
int Rotor::get_moving_array(int j) { return moving_array[j];}
int Rotor::get_notch_position(int j){ return notch_postion[j] ;}
int Rotor::get_number_of_notches() {return number_of_notches ; }
int Rotor::get_top_position() {return moving_array[0] ; }
int Rotor::get_rotor_status() {return rotor_status ; }
   

void Rotor::turn_rotor(){

    int temp = moving_array[0] ; 
    for(int i = 0 ; i<=24 ; i++)
    {
        moving_array[i] = moving_array[i+1] ;
    }
    moving_array[25] = temp ;
}
    

void Rotor::move_to_starting_position() {
    
    int number_of_turns ;
    while (get_top_position()!= starting_position)
    {
        turn_rotor() ;
        number_of_turns++;
        
    }
    number_of_turns = 0 ;
}

void Rotor::encryption_rtl(int& input_character)
{
    int temp_1,temp_2;
    temp_1 = moving_array[input_character] ;
    temp_2 = forward_rotor_array[temp_1];
    for(int j = 0 ; j <=25 ; j++)
    {
        if(moving_array[j] == temp_2)
        {
            input_character = j ;
            break ;
        }
        
    }
}

void Rotor::encryption_ltr(int& input_character){

    int temp_1,temp_2;
    temp_1 = moving_array[input_character] ;
    temp_2 = reverse_rotor_array[temp_1];
    for(int j = 0 ; j <=25 ; j++)
    {
        if(moving_array[j] == temp_2)
        {
            input_character = j ;
            break ;
        }
        
    }
}
    
