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

    book.addOrder(Order(1, OrderSide::Buy, OrderType::Limit, 100.0, 10, 1));
    book.addOrder(Order(2, OrderSide::Sell, OrderType::Limit, 105.0, 5, 2));

    std::cout << "===== BEFORE MODIFY =====\n";
    book.printOrderBook();

    bool modified = book.modifyOrder(999, 100, 10);

    std::cout << "\nModify Success: "
              << (modified ? "YES" : "NO")
              << "\n\n";

    std::cout << "===== AFTER MODIFY =====\n";
    book.printOrderBook();

    std::cout << "\n";
    book.printTrades();


    return 0;
}