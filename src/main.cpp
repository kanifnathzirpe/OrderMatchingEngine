#include "Order.h"
#include "OrderBook.h"


int main() {
    OrderBook book;
    //id,side,type,price,quantity,timestamp
    Order buyOrder1(1, OrderSide::Buy, OrderType::Limit, 101.50, 100, 1690000000);
    Order buyOrder2(2, OrderSide::Buy, OrderType::Limit, 102.00, 50, 1690000001);
    Order buyOrder3(3, OrderSide::Buy, OrderType::Limit, 101.50, 25, 1690000002);
 
    Order sellOrder1(4, OrderSide::Sell, OrderType::Limit, 100.00, 75, 1690000003);
    Order sellOrder2(5, OrderSide::Sell, OrderType::Market, 102.75, 50, 1690000004);
    Order sellOrder3(6, OrderSide::Sell, OrderType::Limit, 101.00, 20, 1690000005);
 
    book.addOrder(buyOrder1);
    book.addOrder(sellOrder1);
    book.addOrder(buyOrder2);
    book.addOrder(buyOrder3);
    book.addOrder(sellOrder2);
    book.addOrder(sellOrder3);
    book.cancelOrder(2);
    book.printOrderBook();

    
    book.printTrades();

    return 0;
}