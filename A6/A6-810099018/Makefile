CC := g++

all: quizMaker

quizMaker: main.o answer.o quiz.o questions.o
	$(CC)  main.o answer.o quiz.o questions.o -o quizMaker

main.o: ca6.cpp quiz.hpp questions.hpp answer.hpp
	$(CC) -c ca6.cpp  -o main.o

quiz.o: quiz.cpp quiz.hpp questions.hpp answer.hpp
	$(CC) -c quiz.cpp -o quiz.o

questions.o: questions.cpp questions.hpp
	$(CC) -c questions.cpp -o questions.o

answer.o: answer.cpp answer.hpp
	$(CC) -c answer.cpp -o answer.o

.PHONY: clean
clean:
	rm -r *.o