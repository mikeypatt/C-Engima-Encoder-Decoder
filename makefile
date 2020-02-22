enigma: main.o enigma.o checkers.o plugboard.o reflector.o rotors.o 
	g++ main.o enigma.o checkers.o plugboard.o reflector.o rotors.o -o enigma

main.o: main.cpp errors.h enigma.h 
	g++ -Wall -g -c -O3 main.cpp
	
checkers.o: checkers.cpp checkers.h errors.h
	g++ -Wall -g -c -O3 checkers.cpp
	
enigma.o: enigma.cpp enigma.h errors.h
	g++ -Wall -g -c -O3 enigma.cpp

plugboard.o: checkers.h plugboard.cpp  plugboard.h errors.h 
	g++ -Wall -g -c -O3 plugboard.cpp
	
reflector.o: reflector.cpp reflector.h errors.h checkers.h
	g++ -Wall -g -c -O3 reflector.cpp

rotors.o: rotors.cpp rotors.h errors.h checkers.h
	g++ -Wall -g -c -O3 rotors.cpp
	
clean:
	rm -f *.o enigma
