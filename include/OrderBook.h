#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Order.h"
#include <deque>
#include <map>
#include <functional>

class OrderBook {
    private:
        std::map<double, std::deque<Order>, std::greater<double>> buyOrders;
        std::map<double, std::deque<Order>> sellOrders;
    public:
        void addOrder(const Order& order);
        void printBuyBook() const;
        void printSellBook() const;
        void printOrderBook() const;

};

#endif