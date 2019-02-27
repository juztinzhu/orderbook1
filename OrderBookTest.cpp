#include "CSVIterator.h"
#include "Definitions.h"
#include "OrderBookManager.h"
void LoadOrders()
{
	OrderBookManager orderBook;
	std::ifstream file("Orders.txt");
	if (!file.is_open())
	{
		std::cout << "ERROR: Could not open Orders.csv" << std::endl;
		exit(1);
		return;
	}
	for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
	{
		Order newOrder;
		newOrder.Account = (*loop)[0];
		newOrder.Price = atoi((*loop)[1].c_str());
		newOrder.Quantity = atoi((*loop)[2].c_str());
		newOrder.Side = (OrderSide)atoi((*loop)[3].c_str());
		orderBook.OnNewOrder(newOrder);
	}
}

int main()
{
	LoadOrders();
    return 0;
}


