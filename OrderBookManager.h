#pragma once
#include <iostream>
#include <fstream>
#include "Definitions.h"
#include <map>
#include <functional>
template<typename compare>
class OrderList
{
private:
    std::multimap<int, Order, compare > list;
public:
    size_t Size(){return list.size();}
    // place the new order into the list in the right place
    void Insert(const Order& order)
    {
        list.insert(std::make_pair(order.Price, order));
    }
    // return the top of the list
    Order* Top()
    {
        if (list.empty())
        {
            return NULL;
        }
        return &list.begin()->second;
    }
    // delete the top, and return the new top
    Order* Pop()
    {
        if(list.empty())
        {
            return NULL;
        }
        auto next = list.erase(list.begin());
        if (next!=list.end())
        {
            return &next->second;
        }
        return NULL;
    }
    bool Empty() const 
    {
        return list.empty();
    }
};

typedef OrderList<std::greater<int>> BuyList;
typedef OrderList<std::less<int>> SellList;

class ITradeReporter
{
public:
    virtual void ReportTrade(const std::string & account1, const std::string & account2, const int& price, const int& Size)=0;
    virtual ~ITradeReporter(){};
};

class OrderBookManager
{
private:
	std::ofstream _myfile;
    BuyList buyList;
    SellList sellList;
    ITradeReporter *reporter;
public:
    explicit OrderBookManager(ITradeReporter* aReporter):reporter(aReporter){}
	void OnNewOrder(const Order& order); //�յ��µ�order
private:
    void OnBuyOrder(const Order& order);
    void OnSellOrder(const Order& order);
};

