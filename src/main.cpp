#include "Order.h"

int main() {
    //id,side,type,price,quantity,timestamp
    Order buyOrder(1, OrderSide::Buy, OrderType::Limit, 101.50, 100, 1690000000);
    Order sellOrder(2, OrderSide::Sell, OrderType::Market, 102.75, 50, 1690000000);

    buyOrder.display();
    sellOrder.display();

    return 0;
}