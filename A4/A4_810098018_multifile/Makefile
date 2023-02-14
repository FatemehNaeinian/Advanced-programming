all: a.out

a.out: main.o Order.o Printer.o Press.o InkStore.o
	g++ -std=c++11 main.o Order.o Printer.o Press.o InkStore.o

main.o: main.cpp Press.hpp
	g++ -std=c++11 -c main.cpp

Press.o: Press.cpp Press.hpp Order.hpp Printer.hpp InkStore.hpp
	g++ -std=c++11 -c Press.cpp

Order.o: Order.cpp Order.hpp InkStore.hpp
	g++ -std=c++11 -c Order.cpp

Printer.o: Printer.hpp Printer.cpp Order.hpp InkStore.hpp
	g++ -std=c++11 -c Printer.cpp

InkStore.o: InkStore.hpp InkStore.cpp
	g++ -std=c++11 -c InkStore.cpp

clean:
	rm *.o
	rm *.out