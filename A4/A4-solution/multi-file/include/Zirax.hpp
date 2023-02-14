#ifndef ZIRAX_HPP
#define ZIRAX_HPP

#include <vector>
#include <map>
#include <iostream>

#include "Printer.hpp"
#include "PriorityOrderQueue.hpp"

typedef std::vector<Printer*> Printers;

class Zirax {
private:
	Printers printers;
	PriorityOrderQueue* order_queue;
	int last_printer_id;
	int last_order_id;
	int passed_time;
	std::vector<std::pair<int, int>> finished_orders;
	void advance_one_time_unit();
	void dispatch_new_orders();
	void get_finished_orders();
	void update_status_of_printers();
	void set_printers_to_print();
	void print_printer_info(Printer* printer);

public:
	Zirax();
	void add_printer(int printing_speed, int ink_capacity, int paper_capacity);
	void add_order(int number_of_pages, std::map<InkColor, int> required_inks, OrderType order_type);
	void advance_time_unit(int number_of_time_units);
	void print_info();

};

#endif