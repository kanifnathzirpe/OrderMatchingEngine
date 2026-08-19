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

    book.addOrder(Order(1, OrderSide::Sell, OrderType::Limit, 100, 20, 1));
    book.addOrder(Order(2, OrderSide::Sell, OrderType::Limit, 101, 30, 2));

    book.addOrder(Order(3, OrderSide::Buy, OrderType::FOK, 0, 50, 3));

    book.printOrderBook();
    book.printTrades();

    return 0;
}