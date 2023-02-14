#include "CommandHandler.hpp"

using namespace std;

CommandHandler::CommandHandler()
	: zirax(new Zirax())
{}

void CommandHandler::run() {
	const int COMMAND_TYPE_INDEX = 0;
	string input;
	while (getline(cin, input)) {
		const string commandType = tokenizeInput(input)[COMMAND_TYPE_INDEX];

		if (commandType == ADD_PRINTER)
			cout << add_printer(input) << endl;
		else if (commandType == ADD_ORDER)
			cout << add_order(input) << endl;
		else if (commandType == ADVANCE_TIME) {
			advance_time(input);
			cout << OK_MESSAGE << endl;
		}
		else if (commandType == SHOW_INFO)
			show_info();
	}
}

string CommandHandler::add_printer(string input) {
	const int PRINTER_SPEED = 1;

	vector<string> tokenized_input = tokenizeInput(input);
	zirax->add_printer(stoi(tokenized_input[PRINTER_SPEED]), INK_CAPACITY, PAPER_CAPACITY);
	return ADD_PRINTER_SUCCESSFUL;
}

string CommandHandler::add_order(string input) {
	const int RED_INK_REQUIRED_INDEX = 1;
	const int GREEN_INK_REQUIRED_INDEX = 2;
	const int BLUE_INK_REQUIRED_INDEX = 3;
	const int BLACK_INK_REQUIRED_INDEX = 4;
	const int PAGE_NUMBER_INDEX = 5;
	const int ORDER_TYPE_INDEX = 6;

	vector<string> tokenized_input = tokenizeInput(input);
	map<InkColor, int> required_inks;
	required_inks.insert({ Red, stoi(tokenized_input[RED_INK_REQUIRED_INDEX]) });
	required_inks.insert({ Green, stoi(tokenized_input[GREEN_INK_REQUIRED_INDEX]) });
	required_inks.insert({ Blue, stoi(tokenized_input[BLUE_INK_REQUIRED_INDEX]) });
	required_inks.insert({ Black, stoi(tokenized_input[BLACK_INK_REQUIRED_INDEX]) });
	OrderType order_type = tokenized_input[ORDER_TYPE_INDEX] == REGULAR ? Regular : VIP;
	zirax->add_order(stoi(tokenized_input[PAGE_NUMBER_INDEX]), required_inks, order_type);
	return ADD_ORDER_SUCCESSFUL;
}

void CommandHandler::advance_time(string input) {
	const int TIME_STAPM_INDEX = 1;

	vector<string> tokenized_input = tokenizeInput(input);
	zirax->advance_time_unit(stoi(tokenized_input[TIME_STAPM_INDEX]));
}

void CommandHandler::show_info() {
	zirax->print_info();
}

vector<string> CommandHandler::tokenizeInput(string input) {
	stringstream inputStringStream(input);
	return vector<string>(istream_iterator<string>(inputStringStream),
		istream_iterator<string>());
}

