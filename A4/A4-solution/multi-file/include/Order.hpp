#ifndef ORDER_HPP
#define ORDER_HPP

#include <map>

enum InkColor {
	Black,
	Red,
	Blue,
	Green,
};

enum OrderType {
	Regular,
	VIP
};

class Order {
private:
	int id;
	int number_of_pages;
	OrderType order_type;
	std::map<InkColor, int> required_inks;

public:
	Order(int id, int number_of_pages, std::map<InkColor, int> required_inks, OrderType order_type);
	int get_id();
	std::map<InkColor, int> get_required_inks();
	int get_number_of_pages();
	OrderType get_order_type();
};


#endif