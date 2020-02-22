//Plugboard class header file 
class Plugboard {
    
    const char* filename ;
    int plug_number_array[13][2]  ;
    int number_of_pairs ;
    int plugboard_status = 0 ; /*Error status whilst instantiating
                                    an instance of the class*/
public:
 
//Plugboard Constructor    
Plugboard(const char *filename);
            
/*Function to return the plugbard from the class (No Input Parameters)
  Inputs - Integers J & I as for the required index of the array */
int get_plugboard(int j, int i);
/*Function to return the number of pairs from the plugboard class
                                        (No Input Parameters) */
int get_plugboard_pairs() ;

/*Function to return the errro (if present) from the constructor
                            (No Input Parameters)*/
int get_plugboard_status() ;
} ;
