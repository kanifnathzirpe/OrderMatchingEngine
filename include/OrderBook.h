#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Order.h"
#include "Trade.h"
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>


struct OrderLocation { 
    double price;
    OrderSide side;
};

class OrderBook {
    private:
        std::map<double, std::deque<Order>, std::greater<double>> buyOrders;
        std::map<double, std::deque<Order>> sellOrders;
        std::unordered_map<std::uint64_t, OrderLocation> orderIndex;
        std::vector<Trade> trades;

    public:
        void addOrder(const Order& order);
        bool cancelOrder(std::uint64_t orderId);
        void matchOrder(Order& incomingOrder);
        std::size_t getTradeCount() const;

        void printTrades() const;
        void printBuyBook() const;
        void printSellBook() const;
        void printOrderBook() const;

};

#endif