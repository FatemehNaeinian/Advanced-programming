CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR) -g

EXECUTABLE_FILE = quizMaker

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

OBJECTS = \
	$(BUILD_DIR)/Question.o \
	$(BUILD_DIR)/ShortAnswerQuestion.o \
	$(BUILD_DIR)/SingleAnswerMultipleChoiceQuestion.o \
	$(BUILD_DIR)/MultipleAnswerMultipleChoiceQuestion.o \
	$(BUILD_DIR)/QuestionReader.o \
	$(BUILD_DIR)/QuizHandler.o \
	$(BUILD_DIR)/Util.o \
	$(BUILD_DIR)/Main.o \

$(BUILD_DIR)/Util.o: $(SRC_DIR)/Util.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Util.cpp -o $(BUILD_DIR)/Util.o

$(BUILD_DIR)/QuizHandler.o: $(SRC_DIR)/QuizHandler.cpp \
							$(INCLUDE_DIR)/Question.hpp \
							$(INCLUDE_DIR)/Util.hpp \
							$(INCLUDE_DIR)/QuestionReader.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/QuizHandler.cpp -o $(BUILD_DIR)/QuizHandler.o

$(BUILD_DIR)/Question.o: $(SRC_DIR)/Question.cpp $(INCLUDE_DIR)/Question.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Question.cpp -o $(BUILD_DIR)/Question.o

$(BUILD_DIR)/ShortAnswerQuestion.o: $(SRC_DIR)/ShortAnswerQuestion.cpp $(INCLUDE_DIR)/Question.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ShortAnswerQuestion.cpp -o $(BUILD_DIR)/ShortAnswerQuestion.o

$(BUILD_DIR)/SingleAnswerMultipleChoiceQuestion.o: $(SRC_DIR)/SingleAnswerMultipleChoiceQuestion.cpp $(INCLUDE_DIR)/Question.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/SingleAnswerMultipleChoiceQuestion.cpp -o $(BUILD_DIR)/SingleAnswerMultipleChoiceQuestion.o

$(BUILD_DIR)/MultipleAnswerMultipleChoiceQuestion.o: $(SRC_DIR)/MultipleAnswerMultipleChoiceQuestion.cpp $(INCLUDE_DIR)/Question.hpp $(INCLUDE_DIR)/Util.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MultipleAnswerMultipleChoiceQuestion.cpp -o $(BUILD_DIR)/MultipleAnswerMultipleChoiceQuestion.o

$(BUILD_DIR)/QuestionReader.o: $(SRC_DIR)/QuestionReader.cpp \
							   $(INCLUDE_DIR)/Question.hpp \
							   $(INCLUDE_DIR)/ShortAnswerQuestion.hpp \
							   $(INCLUDE_DIR)/SingleAnswerMultipleChoiceQuestion.hpp \
							   $(INCLUDE_DIR)/MultipleAnswerMultipleChoiceQuestion.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/QuestionReader.cpp -o $(BUILD_DIR)/QuestionReader.o

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.cpp $(INCLUDE_DIR)/QuizHandler.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out