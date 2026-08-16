#include "Order.h"
#include "OrderBook.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>


int main() {
    OrderBook book;
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> priceDist(95.0,105.0);
    std::uniform_int_distribution<int> quantityDist(1,100);
    std::uniform_int_distribution<int> sideDist(0,1);
    std::uniform_int_distribution<int> typeDist(0,1);
    
    const int NUM_ORDERS = 1000000;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::uint64_t> orderIds;
    orderIds.reserve(NUM_ORDERS);
    for(int i=1;i<=NUM_ORDERS;i++) {
        OrderSide side = (sideDist(rng)==0)? OrderSide::Buy : OrderSide::Sell;
        OrderType type = (typeDist(rng)==0)? OrderType::Limit : OrderType::Market;
        
        double price = priceDist(rng);
        int quantity = quantityDist(rng);
        
        Order order(i, side, type, price, quantity,i);
        book.addOrder(order);
        orderIds.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    double executionTimeSeconds = duration.count() / 1'000'000.0;
    double ordersPerSecond = NUM_ORDERS / executionTimeSeconds;
    
    std::cout << "\n========== PERFORMANCE ==========\n";
    std::cout << "Orders Processed : " << NUM_ORDERS << '\n';
    std::cout << "Trades Executed  : " << book.getTradeCount() << '\n';
    std::cout << "Execution Time   : " << duration.count() << " microseconds\n";
    std::cout << "Throughput       : " << ordersPerSecond << " orders/sec\n";
    
    std::shuffle(orderIds.begin(), orderIds.end(), rng);
    const int NUM_CANCELS = NUM_ORDERS/2;

    auto cancelStart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<NUM_CANCELS; i++) {
        book.cancelOrder(orderIds[i]);
    }
    auto cancelEnd = std::chrono::high_resolution_clock::now();

    auto cancelDuration = std::chrono::duration_cast<std::chrono::microseconds>(cancelEnd-cancelStart);
    double cancelSeconds = cancelDuration.count()/1000000.0;
    double cancelsPerSecond = NUM_CANCELS/cancelSeconds;

    std::cout << "\n========== CANCELLATION ==========\n";
    std::cout << "Orders Cancelled : " << NUM_CANCELS << '\n';
    std::cout << "Cancellation Time: " << cancelDuration.count() << " microseconds\n";
    std::cout << "Cancellation Throughput: " << cancelsPerSecond << " cancels/sec\n";
        
    

    return 0;
}