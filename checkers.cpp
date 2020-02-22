/*The cpp file for a class of functions that check whether the various files
                are well formed (conatain no non-numeric characters etc) */
#include <iostream> 
#include <fstream> 
#include "checkers.h"
#include "errors.h"
#include <sstream>

using namespace std;

int Checkers::checker(const char *filename, int array[][2],int& number_counter
                                            ,int plugboard_checker)
{
    
    int j=0,i=0, input_number;
    
    //Create a string to be filled from the input file stream
    string string_group ;
    
    //Open the input file stream
    ifstream in_stream ;
    in_stream.open(filename);
    
    //Check errors in opening the file
    if(in_stream.fail())
    {
        cerr<< "There was an error opening: " << filename <<".";
        cerr << endl ;
        return ERROR_OPENING_CONFIGURATION_FILE  ; //11
    }
    
    in_stream >> ws ;
    in_stream >> string_group ;
    
    //Loop through file untill error or end of file
    while (!in_stream.eof() || !in_stream.fail() )
    {
        for(int k = 0 ; k < int(string_group.length()) ; k++)
        {
            if(!isdigit(string_group[k]))
            {
                if(plugboard_checker == 0)
                {
                    cerr << "Theres a non numeric character in the reflector file";
                    cerr << endl ;
                    return NON_NUMERIC_CHARACTER ;
                }
                cerr << "Theres a non numeric character in the plugboard file";
                cerr << endl ;
                return NON_NUMERIC_CHARACTER ;
            }
        }
    
        stringstream number(string_group);
        number >> input_number ;
        
        if(input_number<0 || input_number > 25)
        {
            if(plugboard_checker == 0)
            {
                cerr << "Theres an invalid number in the reflector file";
                cerr << endl ;
                return INVALID_INDEX ;
            }
            cerr << "Theres an invalid number in the plugboard file";
            cerr << endl ;
            return INVALID_INDEX ;
        }
        number_counter++ ;
        
        if(number_counter == 27)
        {
            if(plugboard_checker==0)
            {
                cerr << "There are too many reflector inputs" ;
                cerr << endl ;
                return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS ;
            }
            cerr << "There are too many plugboard inputs" ;
            cerr << endl ;
            return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS ;
        }
        /*Check to ensure the number has not appeared yet in the file
                                        and not mapped to itself */
        if(j > 0 && j < 26)
        {
            for (int k = j ; (k >= 0) ; k--)
            {
                if (input_number == array[k][0] || input_number == array[k][1])
                {
                    return SHARED_ERROR  ; /*Returns a shared error
                                        for the reflector/plugboard constructor
                                            to handle appropriately */
                }
            }
        }
        //Check to ensure the number is not being mapped to itself
        if (i == 1 && j < 26)
        {    
            if (input_number == array[j][0])
            {
                return SHARED_ERROR ; /*Returns a shared error
                                        for the reflector/plugboard constructor
                                            to handle appropriately*/
            }
        }
        /*If the number is valid and there has been less than 26 input
                                            it into the array. */
        if(j<26)
        {    
            array[j][i] = input_number ;
        }
        i++ ;
        //Iterates to a new row in the input array
        if (i == 2)
        {
            j++;
            i = 0;
        }
        in_stream >> string_group ;
    }
    in_stream.close();
    /*Error check specifucally for the pluboard to ensure
            there is not an uneven amount of mappings*/
    if(plugboard_checker == 1)
    {
        if(number_counter%2 != 0)
        {
            cerr << "Incorrect number of parameters in plugboard file plugboard.pb";
            cerr << endl ;
            return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        }
    }
    return NO_ERROR ;
}
    
int Checkers::rotor_checker(const char *filename, int array[26],
            int rotor_notch_array[26],int& number_of_notches)
{
    int j=0 ,input_number;
    
    //Create a string to be filled from the input file stream
    string string_group ;
    
    ifstream in_stream ;
    in_stream.open(filename);
    
    //Check errors in opening the file
    if(in_stream.fail())
    {
        cerr << "There was an error opening the "<<filename ;
        cerr << endl ;
        return ERROR_OPENING_CONFIGURATION_FILE  ; 
    }
    
    in_stream >> ws;
    in_stream >> string_group;
    
    
    //Loop through file untill error or end of file
    while (!in_stream.fail() || !in_stream.eof())
    {
        for(int k = 0 ; k < int(string_group.length()) ; k++)
        {
            if(!isdigit(string_group[k]))
            {
                cerr<< "There was a non-numeric character in the rotor file" ;
                cerr << endl ;
                return NON_NUMERIC_CHARACTER ;
            }
        }
        stringstream number(string_group);
        number >> input_number ;
        
        if(input_number<0 || input_number > 25)
        {
            cerr<< "The numbers in the rotor file must be between 0-25" ;
            cerr << endl ;
            return INVALID_INDEX ;
        }
        
        if(j > 0 && j < 26)
        {
            for (int k = j-1 ; (k >= 0) ; k--)
            {
                if (input_number == array[k])
                {
                    cerr<< "Invalid mapping of rotor array, digit has been mapped previously";
                    cerr << endl ;
                    return INVALID_ROTOR_MAPPING; 
                }
            }
        }
        //If the number is valid and less than 26 input it to the main array
        if (j <= 25)
        {
            array[j] = input_number ;
            j++ ;
          
        //If the number is valid and greater than 26 input it to the notch array   
        }else if (j > 25) {
            rotor_notch_array[j-26] = input_number ;
            j++ ;                
        }
        
        in_stream >> ws ;
        in_stream >> string_group ;
    }
    //If the number of inputs is smaller than at 25 inputs & at least 1 notch
    if(j<27)
    {
        cerr << "Not all inputs mapped in rotor file: "<< filename ;
        cerr << endl ;
        return INVALID_ROTOR_MAPPING ;
    }
        
    number_of_notches = j-26 ;
    in_stream.close();

    return NO_ERROR  ;
}

int Checkers::position_checker(const char *filename, int rotor_position,
                    const int total_number, int& starting_position)
{
    //Create a string to be filled from the input file stream
    string string_group ;
    
    int j=0, input_number;
    int array[total_number] ;
    
    ifstream in_stream ;
    in_stream.open(filename);
    
    if(in_stream.fail())
    {
        cerr << "There was an error opening the "<<filename ;
        cerr << endl ;
        return ERROR_OPENING_CONFIGURATION_FILE  ; 
    }
    
    in_stream >> ws ;
    in_stream >> string_group ;

    while (!in_stream.fail() || !in_stream.eof())
    {
        for(int k = 0 ; k < int(string_group.length()) ; k++)
        {
            if(!isdigit(string_group[k]))
            {
                cerr << "There is an non numeric character in the positions file";
                cerr << endl ;
                return NON_NUMERIC_CHARACTER ;
            }
        }

        stringstream number(string_group);
        number >> input_number ;
        
        if(input_number<0 || input_number > 25)
        {
            cerr << "The number in the position file needs to be between 0-25";
            cerr << endl ;
            return INVALID_INDEX ;
        }

        array[j] = input_number ;
        j++ ;

        in_stream >> ws ;
        in_stream >> string_group ;
    }
    
    in_stream.close();

    if(j<(total_number))
    {
        cerr << "There is an unequal amount of rotor postions to rotors" ;
        cerr << endl ;
        return NO_ROTOR_STARTING_POSITION ;
    }
    starting_position = array[total_number-(rotor_position+1)] ;
    
    return NO_ERROR  ;
}
    

