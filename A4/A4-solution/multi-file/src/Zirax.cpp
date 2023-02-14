#include "Zirax.hpp"

using namespace std;

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
	for (size_t i = 0; i < orders[0].size(); i++)
		cout << orders[0][i].first << " " << orders[0][i].second << endl;

    cout << endl;

	cout << "regular orders queue: " << endl;
	for (size_t i = 0; i < orders[1].size(); i++)
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