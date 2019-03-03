#include "CSVIterator.h"
#include "Definitions.h"
#include "OrderBookManager.h"


class TradeReporter:public ITradeReporter
{
private:
    std::ofstream _myfile;
public:
    TradeReporter();
    virtual ~TradeReporter();
    virtual void ReportTrade(const std::string & account1, const std::string & account2, const int& price, const int& Size);
};

void LoadOrders()
{
	TradeReporter reporter;
	OrderBookManager orderBook(&reporter);
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

void TradeReporter::ReportTrade(const std::string & account1, const std::string & account2, const int & price, const int & size)
{
	_myfile << account1 << "," << account2 << "," << size << "," << price << std::endl;
	_myfile.flush();
}


TradeReporter::TradeReporter()
{
	_myfile.open("Trades.txt", std::ios::out);
	if (!_myfile.is_open())
	{
		std::cout << "Trades.txt cannot be opened" << std::endl;
	}
}


TradeReporter::~TradeReporter()
{
	_myfile.close();
}


int main()
{
	LoadOrders();
    return 0;
}


