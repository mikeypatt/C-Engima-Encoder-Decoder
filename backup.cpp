#include <fstream> 
#include <cstring>
#include "errors.h"
#include <sstream>
#include <iostream>
using namespace std ;

//A class of functions that check whether the inputs to the arrays are allowed
class checkers {
public:
    
    int checker(const char *filename, int array[][2],int& number_counter,int plugboard_checker = 0)
    {
    
        int j=0,i=0, input_number;
        
        string string_group ;
        
        ifstream in_stream ;
        in_stream.open(filename);
        
        if(in_stream.fail())
        {
            cerr<< "There was an error opening: " << filename <<".";
            return ERROR_OPENING_CONFIGURATION_FILE  ; //11
        }
        
        in_stream >> ws ;
        
        in_stream >> string_group ;
        
        while (!in_stream.eof() || !in_stream.fail() )
        {
            for(int k = 0 ; k < int(string_group.length()) ; k++)
            {
                if(!isdigit(string_group[k]))
                {
                    if(plugboard_checker == 0)
                    {
                        cerr << "Theres a non numeric character in the reflector file";
                        return NON_NUMERIC_CHARACTER ;
                    }
                    cerr << "Theres a non numeric character in the plugboard file";
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
                    return INVALID_INDEX ;
                }
                cerr << "Theres an invalid number in the plugboard file";
                return INVALID_INDEX ;
            }
            
            number_counter++ ;
            
            if(number_counter == 27)
            {
                if(plugboard_checker==0)
                {
                    cerr << "There are too many reflector inputs" ;
                    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS ;
                }
                
                cerr << "There are too many plugboard inputs" ;
                return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS ;
            }
            
        
            if(j > 0 && j < 26)
            {
                for (int k = j ; (k >= 0) ; k--)
                {
     
                    if (input_number == array[k][0] || input_number == array[k][1])
                    {
                        
                        return 12  ; //IMPOSSIBLE_PLUGBOARD_CONFIGURATION 5
                    }
                }
            }
            
            if (i == 1 && j < 26)
            {    
                if (input_number == array[j][0])
                {
                    return 12 ; // 5 
                }
            }

            if(j<26)
            {    
                array[j][i] = input_number ;
            }
            
            i++ ;
            
            if (i == 2)
            {
                j++;
                i = 0;
            }
            

            in_stream >> string_group ;
        }
        
        in_stream.close();
        
        if(plugboard_checker == 1)
        {
            if(number_counter%2 != 0)
            {
                cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl ;
                return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS; //INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS 6
            }
            

        }
        
        return NO_ERROR ;
    }
    
    
    int checker(const char *filename, int array[26], int rotor_notch_array[26], int& number_of_notches)
    {

        int j=0 ,input_number;
        string string_group ;
        
        ifstream in_stream ;
        in_stream.open(filename);
        if(in_stream.fail())
            
        {
            cerr << "There was an error opening the "<<filename ;
            return ERROR_OPENING_CONFIGURATION_FILE  ; //ERROR_OPENING_CONFIGURATION_FILE 11
        }
        
        in_stream >> ws ;
        
        in_stream >> string_group;
        
        while (!in_stream.fail() || !in_stream.eof())
        {
            
            for(int k = 0 ; k < int(string_group.length()) ; k++)
            {
                if(!isdigit(string_group[k]))
                {
                    return NON_NUMERIC_CHARACTER ;
                }
            }
        
            stringstream number(string_group);
            number >> input_number ;
            
            if(input_number<0 || input_number > 25)
            {
                return INVALID_INDEX ;
            }
            
            if(j > 0 && j < 26)
            {
                for (int k = j-1 ; (k >= 0) ; k--)
                {
                    if (input_number == array[k])
                    {
                        cerr<< "Invalid mapping of rotor array, digit has been mapped previously" ;
                        return INVALID_ROTOR_MAPPING; //INVALID_ROTOR_MAPPING 7
                    }
                }
            }

            if (j <= 25)
            {
                array[j] = input_number ;
                j++ ;
                
            }else if (j > 25) {
                rotor_notch_array[j-26] = input_number ;
                j++ ;                
            }
            
            in_stream >> ws ;
            
            in_stream >> string_group ;
            
        }
        
        if(j<27)
        {
            cerr << "Not all inputs mapped in rotor file: "<< filename ;
            return INVALID_ROTOR_MAPPING ;
        }
            
        number_of_notches = j-26 ;
        in_stream.close();

        return NO_ERROR  ;
    }
    
    int position_checker(const char *filename, int rotor_position, const int total_number, int& starting_position)
    {
        string string_group ;
        int j=0, input_number;
        int array[total_number] ;
        
        ifstream in_stream ;
        in_stream.open(filename);
        
        if(in_stream.fail())
        {
            cerr << "There was an error opening the "<<filename ;
            return ERROR_OPENING_CONFIGURATION_FILE  ; //ERROR_OPENING_CONFIGURATION_FILE 
        }
        
        in_stream >> ws ;
        

        in_stream >> string_group ;

        
        while (!in_stream.fail() || !in_stream.eof())
        {
           for(int k = 0 ; k < int(string_group.length()) ; k++)
            {
                if(!isdigit(string_group[k]))
                {
                    return NON_NUMERIC_CHARACTER ;
                }
            }
        
            stringstream number(string_group);
            number >> input_number ;
            
            if(input_number<0 || input_number > 25)
            {
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
            return NO_ROTOR_STARTING_POSITION ;
        }
    
        starting_position = array[total_number-(rotor_position+1)] ;

        return NO_ERROR  ;
    }
    
};

//Plugboard class
class plugboard {
    
    const char* filename ;
    int plug_number_array[13][2]   ;
    int number_of_pairs ;
        
public:
    
    plugboard(const char *filename) : filename(filename) {
        
        checkers plugboardchecker ;
        
        int status,number_counter = 0;
        
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                plug_number_array[i][j] = 99;
            }
        }
        
        status = plugboardchecker.checker(filename, plug_number_array,number_counter,1) ;
        if(status != 0)
        {
            if(status == 12)
            {
                cerr << "The plugboard is trying to map a number with itself" ;
                status = IMPOSSIBLE_PLUGBOARD_CONFIGURATION ;
            }
            throw status ;
        }
      
        number_of_pairs = number_counter/2 ;
        
}
            
    //Code to get the plugbard from the class
    int get_plugboard(int j, int i) {return plug_number_array[j][i] ;}
    int get_plugboard_pairs() {return number_of_pairs ;}
    
} ;

//Reflector class
class reflector {
    
    const char* filename ;
    int reflect_array[13][2]  ;
    int number_of_pairs ;
    
public:
    
        reflector(const char *filename) : filename(filename) 
    {
        checkers reflectorchecker ;
        
        int status, number_counter = 0 ;
        
        
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                reflect_array[i][j] = 99;
            }
        }
        
        status = reflectorchecker.checker(filename, reflect_array,number_counter) ;
        
        if(status != 0)
        {
            if(status==12)
            {
                cerr << "You are not allowed to map a number to itself" ;
                status = INVALID_REFLECTOR_MAPPING ;
            }
            throw status ;
        }
        
        number_of_pairs = number_counter/2 ;
        if(number_of_pairs !=13)
        {
            cerr << "Incorrect  number of parameters in reflector file reflector.rf" ;
            throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS ;
        }
        
}

        //Code to get the plugbard from the class
    int get_reflector_number(int j, int i) {return reflect_array[j][i] ;}

        
        
} ;   
    
//rotor class
class rotor {
    
    const char* filename ;
    

    int forward_rotor_array[26] ;
    int reverse_rotor_array[26] ;
    int moving_array[26] ;
    int notch_postion[26]  ;
    int starting_position = 0 ;
    int number_of_notches = 0;
    
public:
    
    rotor(const char *filename,const char* positionfilename, int rotor_number,int total_number_of_rotors) : filename(filename) {
        
        
        checkers rotorchecker ;
        int status , position_status ;
        
        status = rotorchecker.checker(filename, forward_rotor_array,notch_postion,number_of_notches) ;
        position_status = rotorchecker.position_checker(positionfilename,rotor_number,total_number_of_rotors,starting_position) ;

        
        
        for(int i=0;i<=25;i++)
        {
            int number = get_forward_rotor_number(i) ;
            reverse_rotor_array[number] = i ;
        }
        
        for(int j = 0 ; j <=25 ; j++)
        {
            moving_array[j] = j;
        }
        
        if(status != 0)
        {
            throw status ;
        }
        
        if(position_status != 0)
        {
            throw position_status ;
        }
        
        
}
   
   int get_rotor_starting_postion() { return starting_position ;}
   int get_forward_rotor_number(int j) { return forward_rotor_array[j] ;}
   int get_reverse_rotor_number(int j) { return reverse_rotor_array[j] ;}
   int get_moving_array(int j) { return moving_array[j];}
   int get_notch_position(int j){ return notch_postion[j] ;}
   int get_number_of_notches() {return number_of_notches ; }
   int get_top_position() {return moving_array[0] ; }
   
   void turn_rotor_right(){
   
       int temp = moving_array[25] ;
       for(int i = 24 ; i>= 0 ; i--)
       {
          moving_array[i+1] = moving_array[i] ;
       }
       moving_array[0] = temp ;
   }
      

   void turn_rotor_left(){
   
       int temp = moving_array[0] ;
       for(int i = 0 ; i<=24 ; i++)
       {
          moving_array[i] = moving_array[i+1] ;
       }
       moving_array[25] = temp ;
   }
       

   void move_to_starting_position() {
       
       int number_of_turns ;
       while (get_top_position()!= starting_position)
       {
           turn_rotor_left() ;
           number_of_turns++;
           
       }
       number_of_turns = 0 ;
   }
   
   void  encryption_rtl(int& input_character)
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

   void  encryption_ltr(int& input_character){

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
	   
} ;



int main (int argc ,char* argv[])
{
    
    
    //Minimum number of input parameters
    if (argc < 3)
    {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" ;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS ;
    }


    ofstream out_stream ;
    
    int input ;
    char letter ;
    cin >> ws ;


    //Selects an initialises the plugboard 
    plugboard* selected_plugboard ;
       
    try{    
        selected_plugboard = new plugboard(argv[1]) ;
    } catch (int error_code ) {
        

        return error_code ;
    }


    //Selects and initilises a reflector
    reflector* selected_reflector ;
    try{
        selected_reflector = new reflector(argv[2]) ;
    } catch(int error_code){
        
        
        return error_code ;
    }

    
    //write the file to an ouput
    out_stream.open("Enigma_Output.txt") ;
    
    //gets number of rotors and position filename 
    int number_of_rotors = argc - 4 ;
    rotor* rotorPtr[number_of_rotors] ; //creates group of pointers to the rotor object - we dont know how many yet

    
    for(int i = 0 ; i < number_of_rotors ; i++)
    {
        try{
        rotorPtr[i] = new rotor(argv[argc-2-i],argv[argc-1],i,number_of_rotors) ;
        }catch(int error_code){
            return error_code ;
        }
        rotorPtr[i]->move_to_starting_position() ;                                                                            
    }
    
    // ENIGMA STARTSSSSS
    //starts converting the input numbers to through the plugboard
    
    while(cin >> ws >>letter)
    {
        if((letter<65||letter>90) && static_cast<int>(letter) >0)
        {
            cerr<< letter << " is not a valid input character (input characters must be upper case letters A-Z)!" ;
            return INVALID_INPUT_CHARACTER ;
        }
        if(static_cast<int>(letter) == -1)
        {
            break ;
        }
        input = static_cast<int>(letter - 'A') ;
//        input_character_array[character_counter] = input ;
//        character_counter++ ;



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
        
        
        //for every input character turn the right most rotor once to the right
        rotorPtr[0]->turn_rotor_left() ;
        
        for(int j = 0 ; j<(number_of_rotors-1) ; j++) // this is like this to not include the left most rotor so if there are 2 rotors it will only apply the for loop to the first (rotorPtr[0])
        {
            for ( int q = 0 ; q < rotorPtr[j]->get_number_of_notches() ; q++)
            {
                //if the right most rotor gets to its notch position move the next rotor by one
                if(rotorPtr[j]->get_top_position() == rotorPtr[j]->get_notch_position(q))
                {
                    rotorPtr[j+1]->turn_rotor_left() ;
                }
            }
        }
        
        //putting the character through both of the rotors
        for(int j = 0 ; j<(number_of_rotors) ; j++)
        {
            
            //will put the character through the first rotor so if the character is A (0) it will go to index (0) and change it for the value at that index for the rotor
            rotorPtr[j]->encryption_rtl(input) ;
        }
        
        //putting the character through the reflector
        for(int j = 0 ; j<=12 ; j++) // it for j untill it is smaller than 13 and not equal to as theres 13 pairs but it starts index at 0 so its only to 12
        {
            if(selected_reflector->get_reflector_number(j,0)==input)
            {
                input = selected_reflector->get_reflector_number(j,1);
                
            }else if (selected_reflector->get_reflector_number(j,1)==input)
            { 
                input = selected_reflector->get_reflector_number(j,0);
            }
        }

        //putting the character through both of the rotors on the way back
        for(int j = (number_of_rotors-1) ; j>= 0 ; j--)
        {
            
            //will put the character through the first rotor so if the character is A (0) it will go to index (0) and change it for the value at that index for the rotor
            rotorPtr[j]->encryption_ltr(input) ;
        }

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
        
        
        cout << static_cast<char>(input+'A') ;
        out_stream << static_cast<char>(input+'A') ;
        
    }
  


    return 0 ;
}

