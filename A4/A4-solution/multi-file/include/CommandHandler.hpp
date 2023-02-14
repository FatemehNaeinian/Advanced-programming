#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <sstream>

#include "Zirax.hpp"

class CommandHandler {

public:
	CommandHandler();
	void run();

private:
	std::vector<std::string> tokenizeInput(std::string input);
	std::string add_printer(std::string input);
	std::string add_order(std::string input);
	void advance_time(std::string input);
	void show_info();

	Zirax* zirax;
};

#endif