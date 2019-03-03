#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../OrderBookManager.h"
using namespace testing;
TEST(orderlist,buy_prio)
{
    BuyList list;
    list.Insert(Order{"o1", 5,100,BUY});
    ASSERT_EQ(list.Size(),1);
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,5);

    list.Insert(Order{"o2", 7,100,BUY});
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,5);
    
    list.Insert(Order{"o3", 1,101,BUY});
    ASSERT_EQ(list.Top()->Price,101);
    ASSERT_EQ(list.Top()->Quantity,1);
 
    (void)list.Pop();
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,5);
    (void)list.Pop();
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,7);
    EXPECT_TRUE(list.Pop()==NULL);
    EXPECT_TRUE(list.Pop()==NULL);

}
TEST(orderlist,sell_prio)
{
    SellList list;
    list.Insert(Order{"o1", 5,100,SELL});
    ASSERT_EQ(list.Size(),1);
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,5);

    list.Insert(Order{"o2", 7,100,SELL});
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,5);
    
    list.Insert(Order{"o3", 1,101,SELL});
    list.Insert(Order{"o4", 1,99,SELL});
    ASSERT_EQ(list.Top()->Price,99);
    ASSERT_EQ(list.Top()->Quantity,1);
 
    (void)list.Pop();
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,5);
    (void)list.Pop();
    ASSERT_EQ(list.Top()->Price,100);
    ASSERT_EQ(list.Top()->Quantity,7);
    (void)list.Pop();
    ASSERT_EQ(list.Top()->Price,101);
    ASSERT_EQ(list.Top()->Quantity,1);

}

class MockReporter: public ITradeReporter
{
public:
    MOCK_METHOD4(ReportTrade, void(const std::string & , const std::string &, const int &, const int &));
};

TEST(OrderBookManager,trade)
{
    MockReporter reporter;
    OrderBookManager mgr(&reporter);

    mgr.OnNewOrder(Order{"a1",5,100,BUY});
    mgr.OnNewOrder(Order{"a2",7,100,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    EXPECT_CALL(reporter,ReportTrade("a4","a3",101,1));
    EXPECT_CALL(reporter,ReportTrade("a4","a1",100,5));
    EXPECT_CALL(reporter,ReportTrade("a4","a2",100,4));
    mgr.OnNewOrder(Order{"a4",10,100,SELL});

    EXPECT_CALL(reporter,ReportTrade("a5","a2",100,3));
    mgr.OnNewOrder(Order{"a5",7,100,SELL});

    EXPECT_CALL(reporter,ReportTrade("a7","a6",99,2));
    EXPECT_CALL(reporter,ReportTrade("a7","a5",100,4));
    mgr.OnNewOrder(Order{"a6",2,99,SELL});
    mgr.OnNewOrder(Order{"a7",7,100,BUY});

}

TEST(OrderBookManager,trade_many)
{
    MockReporter reporter;
    OrderBookManager mgr(&reporter);

    mgr.OnNewOrder(Order{"a1",5,100,BUY});
    mgr.OnNewOrder(Order{"a2",7,100,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});
    mgr.OnNewOrder(Order{"a3",1,101,BUY});

    mgr.OnNewOrder(Order{"a4",1,102,SELL});

    EXPECT_CALL(reporter,ReportTrade("a4","a3",101,1)).Times(7);
    mgr.OnNewOrder(Order{"a4",8,101,SELL});

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc,argv);
    testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}