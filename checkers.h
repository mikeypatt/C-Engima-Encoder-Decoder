/*The header file for a class of functions that check whether the various files
                are well formed (conatain no non-numeric characters etc) */
class Checkers {
public:
    
    /*Checker function to ensure that both the plugboard and\
                     the reflector files are well formed.
    Inputs: filename - the filename of the file to be inputed
            array - the array to be filled with the file contents
            number_counter - passed by reference to count the number of integers added
            plugboard_checker - switch to turn on the extra functionality required for
                                                                plugboard. */
    int checker(const char *filename, int array[][2],int& number_counter,
                                        int plugboard_checker = 0) ;
                                        
    /*Checker function to ensure that rotor mapping file is well formed
    Inputs: filename - the filename of the file to be inputed
            array - the array to be filled with the file contents
            rotor_notch_array - array for the position of the notches on the given rotor
            number_of_notches - passed by reference to count the number of notch positions for the rotor */
    int rotor_checker(const char *filename, int array[26], int rotor_notch_array[26],
                                           int& number_of_notches) ;
    
    /*Checker function to ensure that rotor starting position file is well formed
    Inputs: filename - the filename of the file to be inputed
            rotor_position - the postion of the rotor in the enigma
            total_number - the total number of rotors in the enigma setup
            starting_position - the subsequent starting position of the current rotor */                                        
    int position_checker(const char *filename, int rotor_position, const int total_number,
                                           int& starting_position) ;
} ;



