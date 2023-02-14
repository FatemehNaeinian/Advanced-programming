#include "Order.hpp"

using namespace std;

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