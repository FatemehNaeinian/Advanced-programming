#include "Printer.hpp"

using namespace std;

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
	return (remaining_papers < printing_speed && (unsigned)remaining_papers < remaining_pages_to_finish_current_order);
}

bool Printer::does_require_ink_refill() {
    if(is_idle())
	{
		return false;
	}
    
	for (auto i : current_order->get_required_inks()) {
		if (ink_supply[i.first] < i.second * printing_speed && (unsigned)ink_supply[i.first] < remaining_pages_to_finish_current_order * i.second)
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
    
    int papers_printed_in_iter = (remaining_pages_to_finish_current_order <= (unsigned)printing_speed) ? remaining_pages_to_finish_current_order : printing_speed;

	remaining_pages_to_finish_current_order -= papers_printed_in_iter;
	remaining_papers -= papers_printed_in_iter;
	for (auto ink : current_order->get_required_inks()) {
		ink_supply[ink.first] -= ink.second * papers_printed_in_iter;
	}
}

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