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

bool OrderBook::cancelOrder(std::uint64_t orderId) {
     // Search Buy Book
    for (auto priceIt = buyOrders.begin(); priceIt != buyOrders.end(); ++priceIt) {
        auto& orders = priceIt->second;
 
        for (auto orderIt = orders.begin(); orderIt != orders.end(); ++orderIt) {
            if (orderIt->getOrderId() == orderId) {
                orders.erase(orderIt);
 
                if (orders.empty()) {
                    buyOrders.erase(priceIt);
                }
 
                return true;
            }
        }
    }
 
    // Search Sell Book
    for (auto priceIt = sellOrders.begin(); priceIt != sellOrders.end(); ++priceIt) {
        std::deque<Order>& orders = priceIt->second;
 
        for (auto orderIt = orders.begin(); orderIt != orders.end(); ++orderIt) {
            if (orderIt->getOrderId() == orderId) {
                orders.erase(orderIt);
 
                if (orders.empty()) {
                    sellOrders.erase(priceIt);
                }
 
                return true;
            }
        }
    }
 
    // Not found in either book
    return false;
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