#include "Order.h"
#include "OrderBook.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include <iomanip>

int main() {
    OrderBook book;

    book.addOrder(Order(1, OrderSide::Sell, OrderType::Limit, 105.0, 100, 1));

    book.addOrder(Order(2, OrderSide::Buy, OrderType::IOC, 100.0, 50, 2));

    book.printOrderBook();
    book.printTrades();

    return 0;
}