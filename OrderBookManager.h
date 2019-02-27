#pragma once
#include <iostream>
#include <fstream>
#include "Definitions.h"

class OrderList
{
public:
    // place the new order into the list in the right place
    void Insert(const Order& order);
    // return the top of the list
    Order* Front();
    // delete the top, and return the new top
    Order* Next();
    bool Empty();
};

class OrderBookManager
{
private:
	std::ofstream _myfile;
    OrderList buyList;
    OrderList sellList;
public:
	OrderBookManager();
	virtual ~OrderBookManager();

	void OnNewOrder(const Order& order); //�յ��µ�order

	void ReportTrade(const std::string & account1, const std::string & account2, const int& price, const int& size);  //����ɽ�
private:
    void OnBuyOrder(const Order& order);
    void OnSellOrder(const Order& order);
};

