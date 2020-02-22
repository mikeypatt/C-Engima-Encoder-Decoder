//Reflector class header file

class Reflector {
    
    const char* filename ;
    int reflect_array[13][2]  ;
    int number_of_pairs ;
    int reflector_status ; /*Error status whilst instantiating
                                    an instance of the class*/
    
public:
    
    Reflector(const char *filename);
    
/*Function to return the plugbard from the class (No Input Parameters)
  Inputs - Integers J & I as for the required index of the array */
    int get_reflector_number(int j, int i) ;
/*Function to return the error (if present) from the constructor
                            (No Input Parameters)*/    
    int get_reflector_status() ;
} ;

        
