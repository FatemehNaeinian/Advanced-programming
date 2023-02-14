CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR) -g

EXECUTABLE_FILE = zirax.out

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

OBJECTS = \
	$(BUILD_DIR)/Zirax.o \
	$(BUILD_DIR)/PriorityOrderQueue.o \
	$(BUILD_DIR)/Printer.o \
	$(BUILD_DIR)/Order.o \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/Main.o \

$(BUILD_DIR)/Zirax.o: $(SRC_DIR)/Zirax.cpp $(INCLUDE_DIR)/Printer.hpp $(INCLUDE_DIR)/PriorityOrderQueue.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Zirax.cpp -o $(BUILD_DIR)/Zirax.o

$(BUILD_DIR)/PriorityOrderQueue.o: $(SRC_DIR)/PriorityOrderQueue.cpp $(INCLUDE_DIR)/Order.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/PriorityOrderQueue.cpp -o $(BUILD_DIR)/PriorityOrderQueue.o

$(BUILD_DIR)/Printer.o: $(SRC_DIR)/Printer.cpp $(INCLUDE_DIR)/Order.hpp $(INCLUDE_DIR)/Defs.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Printer.cpp -o $(BUILD_DIR)/Printer.o

$(BUILD_DIR)/Order.o: $(SRC_DIR)/Order.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Order.cpp -o $(BUILD_DIR)/Order.o

$(BUILD_DIR)/CommandHandler.o: $(SRC_DIR)/CommandHandler.cpp $(INCLUDE_DIR)/Zirax.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/Main.o: $(SRC_DIR)/Main.cpp $(INCLUDE_DIR)/CommandHandler.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out