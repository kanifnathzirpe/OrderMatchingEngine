#include "OrderBook.h"
#include <iostream>
void OrderBook::addOrder(const Order& order) {
    const double price = order.getPrice();
    if(order.getSide() == OrderSide::Buy) {
        buyOrders[price].push_back(order);
        return;
    }
    sellOrders[price].push_back(order);
    
}

void OrderBook::printBuyBook() const {
    std::cout << "----- Buy Book -----" << std::endl;
    for(const auto& [price,orders] : buyOrders) {
        std::cout << "Price: " << price << std::endl;
        for(const auto& order : orders) {
            order.display();
        }
    }
}

void OrderBook::printSellBook() const {
    std::cout << "----- Sell Book -----" << std::endl;
    for(const auto& [price,orders] : sellOrders) {
        std::cout << "Price: " << price << std::endl;
        for(const auto& order : orders) {
            order.display();
        }
    }
}

void OrderBook::printOrderBook() const {
    printBuyBook();
    printSellBook();
}