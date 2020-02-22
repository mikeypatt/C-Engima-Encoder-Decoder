//Rotor class header file 
class Rotor {
    
    const char* filename ;
    
    int forward_rotor_array[26] ;
    int reverse_rotor_array[26] ;
    int moving_array[26] ; // **See description below 
    int notch_postion[26]  ;
    int starting_position = 0 ;
    int number_of_notches = 0;
    int rotor_status  ;
    
/* The moving array is the representation of what an
    external viewer would see as the rotor moves from the engima box*/
public:
    
    Rotor(const char *filename,const char* positionfilename, int rotor_number,
                                            int total_number_of_rotors) ;
    //Function to get the starting position of the rotor                                        
    int get_rotor_starting_postion();
    /*Function to get the forward (right to left) prior to reflector mapping
                                for the rotor for letter/index j*/
    int get_forward_rotor_number(int j) ;
    
    /*Function to get the reverse (left to right) after to reflector mapping
                                for the rotor for letter/index j*/
    int get_reverse_rotor_number(int j) ;
    
    /*Function to access the external (visible to user) letter/number of the rotor*/
    int get_moving_array(int j) ;
    
    /*Function to access the notch position(s) of the rotor*/
    int get_notch_position(int j);
    
    /*Function to access the number of notch positions on the rotor*/
    int get_number_of_notches();
    
    /*Function to access the number on the external moving rotor at the
     top position this is the number that the enigma user would see on the interface*/
    int get_top_position() ;
    
    /*Function to return an error(if present) whilst initilasing the
     *                                   instance of the rotor*/ 
    int get_rotor_status() ;
    
    /*Function to turn/rotate the rotor in opposite direction to
     *                       the order of the alphabet*/ 
    void turn_rotor();

    /*Function to turn/rotate the rotor to the
     specified starting position upon initialisation*/ 
    void move_to_starting_position() ;
   
    /*Function to encrypt the letter from right to left before reflector
    through the rotor based on its current postion and starting point*/
    void encryption_rtl(int& input_character);
    
    /*Function to encrypt the letter from left to right (after reflector)
     through the rotor based on its current postion and starting point*/
    void encryption_ltr(int& input_character);
	   
} ;
