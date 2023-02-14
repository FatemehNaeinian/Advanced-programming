#include "PriorityOrderQueue.hpp"

using namespace std;

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
	for (size_t i = 0; i < max(VIP_orders.size(), regular_orders.size()); i++) {
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