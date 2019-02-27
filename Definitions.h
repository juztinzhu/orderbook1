#pragma once
#include <string>

enum OrderSide {
	BUY = 1,	//��
	SELL = 2	//��
};

struct Order {
	std::string Account; //�˻�
	int Quantity;        //��
	int Price;           //��Ǯ
	OrderSide Side;      //������
};