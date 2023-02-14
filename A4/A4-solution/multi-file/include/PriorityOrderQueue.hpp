#ifndef PRIORITY_ORDER_QUEUE_HPP
#define PRIORITY_ORDER_QUEUE_HPP

#include <vector>
#include <queue>

#include "Order.hpp"

typedef std::queue<Order*> OrderQueue;

class PriorityOrderQueue {
private:
	OrderQueue regular_orders;
	OrderQueue VIP_orders;

public:
	Order* pop_order();
	void push_order(Order* order);
	std::vector<std::vector<std::pair<int, int> > > get_orders();
	bool is_empty();
};

#endif