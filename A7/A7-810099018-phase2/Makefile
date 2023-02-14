CC := g++

all: utravel.out

utravel.out: main.o utravel.o flight.o date.o person.o filter.o ticket.o compare.o
	$(CC)  main.o utravel.o flight.o date.o person.o filter.o ticket.o compare.o -o utravel.out

main.o: main.cpp utravel.hpp flight.hpp date.hpp person.hpp filter.hpp ticket.hpp compare.hpp
	$(CC) -c main.cpp  -o main.o

utravel.o: utravel.cpp utravel.hpp flight.hpp date.hpp person.hpp filter.hpp ticket.hpp compare.hpp
	$(CC) -c utravel.cpp -o utravel.o

flight.o: flight.cpp flight.hpp date.hpp
	$(CC) -c flight.cpp -o flight.o

date.o: date.cpp date.hpp
	$(CC) -c date.cpp -o date.o

person.o: person.cpp person.hpp ticket.hpp
	$(CC) -c person.cpp -o person.o

filter.o: filter.cpp filter.hpp flight.hpp
	$(CC) -c filter.cpp -o filter.o

ticket.o: ticket.cpp ticket.hpp flight.hpp
	$(CC) -c ticket.cpp -o ticket.o

compare.o: compare.cpp compare.hpp
	$(CC) -c compare.cpp -o compare.o


.PHONY: clean
clean:
	rm -r *.o