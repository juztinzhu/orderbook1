
#include "OrderBookManager.h"


OrderBookManager::OrderBookManager()
{
	_myfile.open("Trades.txt", std::ios::out);
	if (!_myfile.is_open())
	{
		std::cout << "Trades.txt cannot be opened" << std::endl;
	}
}


OrderBookManager::~OrderBookManager()
{
	_myfile.close();
}

void OrderBookManager::OnBuyOrder(const Order &order)
{
    Order *front = this->sellList.Front();
    int orderQuantity = Order.Quantity;
    while (front)
    {
        if (front->Price <= order.Price)
        {
            int quantityDiff = orderQuantity - front->Quantity;
            int quantity = quantityDiff > 0 ? orderQuantity : front->Quantity;
            if (quantityDiff < 0)
            {
                front.Quantity -= quantityDiff;
                this.ReportTrade(order.Account, front.Account, front->Price, quantity);
                break;
            }
            else
            {
                front = this->sellList.Next();
                orderQuantity -= quantity;
                this.ReportTrade(order.Account, front.Account, front->Price, quantity);
                continue;
            }
        }
        break;
    }
    if (orderQuantity>0)
    {
        Order buyorder = order;
        buyorder.Quantity=orderQuantity;
        buyList.Insert(buyorder);
    }
}

void OrderBookManager::OnSellOrder(const Order& order)
{
    Order *front = this->buyList.Front();
    int orderQuantity = Order.Quantity;
    while (front)
    {
        if (front->Price >= order.Price)
        {
            int quantityDiff = orderQuantity - front->Quantity;
            int quantity = quantityDiff > 0 ? orderQuantity : front->Quantity;
            if (quantityDiff < 0)
            {
                front.Quantity -= quantityDiff;
                this.ReportTrade(order.Account, front.Account, front->Price, quantity);
                break;
            }
            else
            {
                front = this->buyList.Next();
                orderQuantity -= quantity;
                this.ReportTrade(order.Account, front.Account, front->Price, quantity);
                continue;
            }
        }
        break;
    }
    if (orderQuantity>0)
    {
        Order sellorder = order;
        sellorder.Quantity=orderQuantity;
        sellList.Insert(sellorder);
    }    
}

void OrderBookManager::OnNewOrder(const Order& order)
{
    if(order.Side==BUY)
    {
        OnBuyOrder(order);
    }
    else
    {
        OnSellOrder(order);
    }
}


void OrderBookManager::ReportTrade(const std::string & account1, const std::string & account2, const int & price, const int & size)
{
	_myfile << account1 << "," << account2 << "," << size << "," << price << std::endl;
	_myfile.flush();
}