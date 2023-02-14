CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: minigolf.out


minigolf.out:ca5.o rsdl.o readinput.o Ball.o playground.o
	$(CC) ca5.o rsdl.o readinput.o Ball.o playground.o $(CCFLAGS) -o minigolf.out 

ca5.o: RSDL/src/rsdl.hpp ca5.cpp readinput.hpp Ball.hpp playground.hpp 
	$(CC) -c ca5.cpp -o ca5.o

rsdl.o: RSDL/src/rsdl.hpp RSDL/src/rsdl.cpp
	$(CC) -c RSDL/src/rsdl.cpp -o rsdl.o

readinput.o: readinput.cpp readinput.hpp Ball.o playground.o
	$(CC) -c readinput.cpp -o readinput.o


Ball.o: Ball.cpp Ball.hpp
	$(CC) -c Ball.cpp -o Ball.o

playground.o: playground.hpp playground.cpp
	$(CC) -c playground.cpp -o playground.o

.PHONY: clean
clean:
	rm -r *.o