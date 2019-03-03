
#include "OrderBookManager.h"

void OrderBookManager::OnBuyOrder(const Order &order)
{
    Order *top = this->sellList.Top();
    int orderQuantity = order.Quantity;
    while (top && orderQuantity>0)
    {
        if (top->Price <= order.Price)
        {
            int quantityDiff = orderQuantity - top->Quantity;
            int quantity = quantityDiff < 0 ? orderQuantity : top->Quantity;
            if (quantityDiff < 0)
            {
                top->Quantity -= quantity;
                reporter->ReportTrade(order.Account, top->Account, top->Price, quantity);
                return;
            }
            else
            {
                orderQuantity -= quantity;
                reporter->ReportTrade(order.Account, top->Account, top->Price, quantity);
                top = this->sellList.Pop();
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
    Order *top = this->buyList.Top();
    int orderQuantity = order.Quantity;
    while (top && orderQuantity>0)
    {
        if (top->Price >= order.Price)
        {
            int quantityDiff = orderQuantity - top->Quantity;
            int quantity = quantityDiff < 0 ? orderQuantity : top->Quantity;
            if (quantityDiff < 0)
            {
                top->Quantity -= quantity;
                reporter->ReportTrade(order.Account, top->Account, top->Price, quantity);
                return;
            }
            else
            {
                orderQuantity -= quantity;
                reporter->ReportTrade(order.Account, top->Account, top->Price, quantity);
                top = this->buyList.Pop();
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


