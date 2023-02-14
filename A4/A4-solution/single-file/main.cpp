#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

#define PAPER_CAPACITY 100
#define INK_CAPACITY 1000
#define PAPER_REFILLING_TIME 5
#define INK_REFILLING_TIME 10

#define ADD_PRINTER "add_printer"
#define ADD_ORDER "add_order"
#define ADVANCE_TIME "advance_time"
#define SHOW_INFO "show_press_info"

#define REGULAR "regular"

#define OK_MESSAGE "ok"
#define ADD_PRINTER_SUCCESSFUL "printer added successfully"
#define ADD_ORDER_SUCCESSFUL "order added successfully"

#define BUSY "busy"
#define IDLE "idle"
#define NOT_AVAILABLE "not_available"

enum InkColor {
	Black,
	Red,
	Blue,
	Green,
};
typedef vector<InkColor> InkColors;

enum OrderType {
	Regular,
	VIP
};

enum PrinterStatus {
	ReadyToWork,
	NeedPaper,
	NeedInk
};


class Order {
private:
	int id;
	int number_of_pages;
	OrderType order_type;
	map<InkColor, int> required_inks;

public:
	Order(int id, int number_of_pages, map<InkColor, int> required_inks, OrderType order_type);
	int get_id();
	map<InkColor, int> get_required_inks();
	int get_number_of_pages();
	OrderType get_order_type();
};
typedef queue<Order*> OrderQueue;

Order::Order(int id, int number_of_pages, map<InkColor, int> required_inks, OrderType order_type) {
	this->id = id;
	this->number_of_pages = number_of_pages;
	this->required_inks = required_inks;
	this->order_type = order_type;
}

int Order::get_id() { return id; }

map<InkColor, int> Order::get_required_inks() { return required_inks; }

int Order::get_number_of_pages() { return number_of_pages; }

OrderType Order::get_order_type() { return order_type; }


class PriorityOrderQueue {
private:
	OrderQueue regular_orders;
	OrderQueue VIP_orders;

public:
	Order* pop_order();
	void push_order(Order* order);
	vector<vector<pair<int, int> > > get_orders();
	bool is_empty();
};

Order* PriorityOrderQueue::pop_order() {
	Order* next_order = nullptr;
	if (VIP_orders.size() != 0) {
		next_order = VIP_orders.front();
		VIP_orders.pop();
	}
	else if (regular_orders.size() != 0) {
		next_order = regular_orders.front();
		regular_orders.pop();
	}
	return next_order;
}

void PriorityOrderQueue::push_order(Order* order) {
	OrderType order_type = order->get_order_type();
	switch (order_type)
	{
	case Regular:
		regular_orders.push(order);
		break;

	case VIP:
		VIP_orders.push(order);
		break;
	}
}

vector<vector<pair<int, int> > > PriorityOrderQueue::get_orders() {
	vector<vector<pair<int, int> > > orders;
	orders.push_back({});
	orders.push_back({});
	for (int i = 0; i < max(VIP_orders.size(), regular_orders.size()); i++) {
		if (i < VIP_orders.size()) {
			orders[0].push_back(
				make_pair(VIP_orders.front()->get_id(), VIP_orders.front()->get_number_of_pages())
			);
			VIP_orders.push(VIP_orders.front());
			VIP_orders.pop();
		}
		if (i < regular_orders.size()) {
			orders[1].push_back(
				make_pair(regular_orders.front()->get_id(), regular_orders.front()->get_number_of_pages())
			);
			regular_orders.push(regular_orders.front());
			regular_orders.pop();
		}
	}

	return orders;
}

bool PriorityOrderQueue::is_empty() {
	return (VIP_orders.size() == 0 && regular_orders.size() == 0);
}


typedef struct printer_info
{
	int printer_id;
	int order_id;
	string printer_status;
	unsigned int remaining_pages_to_finish_current_order;
	map<InkColor, int>* ink_left;
	int papers_left;
} PrinterInfo;

class Printer {
private:
	int id;
	int remaining_papers;
	int paper_capacity;
	int ink_capacity;
	map<InkColor, int> ink_supply;
	int printing_speed;
	unsigned int remaining_pages_to_finish_current_order;
	unsigned int remaining_time_to_start_working;
	Order* current_order;
	PrinterStatus status;
	int time_passed_from_starting_order;

	bool is_out_of_order();
	bool does_require_paper_refill();
	bool does_require_ink_refill();
	void paper_refill();
	void ink_refill();

public:
	Printer(int id, int printing_speed, int ink_capacity, int paper_capacity);
	int get_id();
	PrinterInfo get_info();
	void add_order(Order* order);
	void update_printer_status();
    void print_for_one_time_unit();
	bool is_idle();
    string get_status();
	pair<int, int> get_finished_order();

};
typedef vector<Printer*> Printers;

pair<int, int> Printer::get_finished_order() { 
	if (current_order && remaining_pages_to_finish_current_order == 0)
		return make_pair(current_order->get_id(), time_passed_from_starting_order);
	return make_pair(-1, -1);
}

void Printer::add_order(Order* order) {
	current_order = order;
	remaining_pages_to_finish_current_order = order->get_number_of_pages();
	time_passed_from_starting_order = 0;
}

bool Printer::is_idle() { return current_order == nullptr; }

bool Printer::is_out_of_order() {
    if (remaining_time_to_start_working > 0)
        return true;
    return false;
}

bool Printer::does_require_paper_refill() {
	return (remaining_papers < printing_speed && remaining_papers < remaining_pages_to_finish_current_order);
}

bool Printer::does_require_ink_refill() {
    if(is_idle())
        return false;
    
	for (auto i : current_order->get_required_inks()) {
		if (ink_supply[i.first] < i.second * printing_speed && ink_supply[i.first] < remaining_pages_to_finish_current_order * i.second)
			return true;
	}
	return false;
}

void Printer::paper_refill() { remaining_papers = paper_capacity; }

void Printer::ink_refill() {
	ink_supply[Red] = ink_capacity;
	ink_supply[Green] = ink_capacity;
	ink_supply[Blue] = ink_capacity;
	ink_supply[Black] = ink_capacity;
}

void Printer::print_for_one_time_unit() {
	if(is_idle())
        return;

    time_passed_from_starting_order += 1;
	if(is_out_of_order())
        return;
    
    int papers_printed_in_iter = (remaining_pages_to_finish_current_order <= printing_speed) ? remaining_pages_to_finish_current_order : printing_speed;

	remaining_pages_to_finish_current_order -= papers_printed_in_iter;
	remaining_papers -= papers_printed_in_iter;
	for (auto ink : current_order->get_required_inks()) {
		ink_supply[ink.first] -= ink.second * papers_printed_in_iter;
	}
}

Printer::Printer(int id, int printing_speed, int ink_capacity, int paper_capacity) {
	this->id = id;
	this->ink_capacity = ink_capacity;
	this->paper_capacity = paper_capacity;
	this->paper_refill();
	this->ink_refill();
	this->printing_speed = printing_speed;
	this->remaining_pages_to_finish_current_order = 0;
	this->remaining_time_to_start_working = 0;
	this->current_order = nullptr;
	this->status = ReadyToWork;
}

int Printer::get_id() { return id; }

string Printer::get_status() {
    if(current_order == nullptr)
        return IDLE;
    else if(remaining_time_to_start_working != 0)
        return NOT_AVAILABLE;
    else
        return BUSY;
}

PrinterInfo Printer::get_info() {
	string printer_status[3] = { BUSY, IDLE, NOT_AVAILABLE };

	return{ id,
		(current_order == nullptr) ? -1 : current_order->get_id(),
		get_status(),
		remaining_pages_to_finish_current_order,
		&ink_supply,
		remaining_papers
	};
}

void Printer::update_printer_status() {
    if(remaining_pages_to_finish_current_order == 0) {
		current_order = nullptr;
	}

    if(is_out_of_order()) {
        remaining_time_to_start_working -= 1;
        if(remaining_time_to_start_working == 0) {
            if(status == NeedInk)
				ink_refill();
			else
            	paper_refill();
			status = ReadyToWork;
        }
        return;
    }
    
    if (does_require_paper_refill()) {
		remaining_time_to_start_working = PAPER_REFILLING_TIME;
		status = NeedPaper;
		return;
	}

	if (does_require_ink_refill()) {
		remaining_time_to_start_working = INK_REFILLING_TIME;
		status = NeedInk;
		return;
	}

}


class Zirax {
private:
	Printers printers;
	PriorityOrderQueue* order_queue;
	int last_printer_id;
	int last_order_id;
	int passed_time;
	vector<pair<int, int>> finished_orders;
	void advance_one_time_unit();
	void dispatch_new_orders();
	void get_finished_orders();
	void update_status_of_printers();
	void set_printers_to_print();
	void print_printer_info(Printer* printer);

public:
	Zirax();
	void add_printer(int printing_speed, int ink_capacity, int paper_capacity);
	void add_order(int number_of_pages, map<InkColor, int> required_inks, OrderType order_type);
	void advance_time_unit(int number_of_time_units);
	void print_info();

};

Zirax::Zirax() {
	this->order_queue = new PriorityOrderQueue();
	this->last_order_id = 1;
	this->last_printer_id = 1;
	this->passed_time = 0;

}

void Zirax::add_printer(int printing_speed, int ink_capacity, int paper_capacity) {
	printers.push_back(new Printer(last_printer_id++, printing_speed, ink_capacity, paper_capacity));
}

void Zirax::add_order(int number_of_pages, map<InkColor, int> required_inks, OrderType order_type) {
	order_queue->push_order(new Order(last_order_id++, number_of_pages, required_inks, order_type));
}

void Zirax::get_finished_orders() {
	for (auto printer : printers) {
		pair<int, int> recently_finished_order = printer->get_finished_order();
		if (recently_finished_order.first != -1)
			finished_orders.push_back(recently_finished_order);
	}
}

void Zirax::update_status_of_printers() {
	for (auto printer : printers)
        printer->update_printer_status();
}

void Zirax::set_printers_to_print() {
	for (auto printer : printers)
		printer->print_for_one_time_unit();
}


void Zirax::advance_one_time_unit() {
	update_status_of_printers();
    dispatch_new_orders();
	set_printers_to_print();
	get_finished_orders();
	
    passed_time++;
}

void Zirax::advance_time_unit(int number_of_time_units) {
	for (int i = 0; i < number_of_time_units; i++) 
		advance_one_time_unit();
}

void Zirax::dispatch_new_orders() {
	for (auto printer : printers)
		if (printer->is_idle() && !order_queue->is_empty())
			printer->add_order(order_queue->pop_order());
}

void Zirax::print_printer_info(Printer* printer) {
	PrinterInfo printer_info = printer->get_info();
	cout << "printer ID: " << printer_info.printer_id << endl;
	cout << "status: " << printer_info.printer_status << endl;
	if(printer_info.order_id != -1)
		cout << "current order: " << printer_info.order_id 
		<< " " << printer_info.remaining_pages_to_finish_current_order << endl;
	cout << "ink left:" << endl;
	cout << "red: " << printer_info.ink_left->find(Red)->second << endl;
	cout << "green: " << printer_info.ink_left->find(Green)->second << endl;
	cout << "blue: " << printer_info.ink_left->find(Blue)->second << endl;
	cout << "black: " << printer_info.ink_left->find(Black)->second << endl;
	cout << "papers left: " << printer_info.papers_left << endl;
	cout << endl;
}

void Zirax::print_info() {
	string colors[4] = {"red", "green", "blue", "black"};

	cout << "passed time: " << passed_time << endl;

	vector<vector<pair<int, int> > > orders = order_queue->get_orders();
	cout << "VIP orders queue: " << endl;
	for (int i = 0; i < orders[0].size(); i++)
		cout << orders[0][i].first << " " << orders[0][i].second << endl;

    cout << endl;

	cout << "regular orders queue: " << endl;
	for (int i = 0; i < orders[1].size(); i++)
		cout << orders[1][i].first << " " << orders[1][i].second << endl;

    cout << endl;

	cout << "printers:" << endl;
	for (auto printer : printers) {
		print_printer_info(printer);
	}

	cout << "orders finished: " << endl;
	for(auto finished_order : finished_orders)
		cout << finished_order.first << " " << finished_order.second << endl;
	cout << endl;

}

class CommandHandler {

public:
	CommandHandler();
	void run();

private:
	vector<string> tokenizeInput(string input);
	string add_printer(string input);
	string add_order(string input);
	void advance_time(string input);
	void show_info();

	Zirax* zirax;
};


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
	const int INK_CAP = 2;
	const int PAPER_CAP = 3;

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


int main() {
	CommandHandler commandHandler = CommandHandler();
	commandHandler.run();
	return 0;
}
