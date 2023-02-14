#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <map>
#include <string>

#include "Order.hpp"
#include "Defs.hpp"

#define BUSY "busy"
#define IDLE "idle"
#define NOT_AVAILABLE "not_available"

enum PrinterStatus {
	ReadyToWork,
	NeedPaper,
	NeedInk
};

typedef struct printer_info
{
	int printer_id;
	int order_id;
	std::string printer_status;
	unsigned int remaining_pages_to_finish_current_order;
	std::map<InkColor, int>* ink_left;
	int papers_left;
} PrinterInfo;

class Printer {
private:
	int id;
	int remaining_papers;
	int paper_capacity;
	int ink_capacity;
	std::map<InkColor, int> ink_supply;
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
    std::string get_status();
	std::pair<int, int> get_finished_order();

};

#endif