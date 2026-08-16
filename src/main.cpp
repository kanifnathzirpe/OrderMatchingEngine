#include "Order.h"
#include "OrderBook.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include <iomanip>



struct BenchmarkResult {
    long long matchingTime;
    long long cancellationTime;

    double matchingThroughput;
    double cancellationThroughput;

    std::size_t tradesExecuted;
};

BenchmarkResult runBenchmark(int NUM_ORDERS) {
    OrderBook book;

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> priceDist(95.0,105.0);
    std::uniform_int_distribution<int> quantityDist(1,100);
    std::uniform_int_distribution<int> sideDist(0,1);
    std::uniform_int_distribution<int> typeDist(0,1);
    
    std::vector<std::uint64_t> orderIds;
    orderIds.reserve(NUM_ORDERS);
    //matching
    auto start = std::chrono::high_resolution_clock::now();
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
    auto matchingDuration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    
    //cancellation
    std::shuffle(orderIds.begin(), orderIds.end(), rng);
    const int NUM_CANCELS = NUM_ORDERS/2;

    auto cancelStart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<NUM_CANCELS; i++) {
        book.cancelOrder(orderIds[i]);
    }
    auto cancelEnd = std::chrono::high_resolution_clock::now();
    auto cancelDuration = std::chrono::duration_cast<std::chrono::microseconds>(cancelEnd-cancelStart);
    BenchmarkResult result;
    result.matchingTime = matchingDuration.count();
    result.cancellationTime = cancelDuration.count();
    result.matchingThroughput = NUM_ORDERS/(matchingDuration.count()/1'000'000.0);
    result.cancellationThroughput = NUM_CANCELS/(cancelDuration.count()/1'000'000.0);
    result.tradesExecuted = book.getTradeCount();

    return result;
}

int main() {
    constexpr int NUM_ORDERS = 1'000'000;
    constexpr int NUM_RUNS = 5;
    std::vector<BenchmarkResult> results;
    results.reserve(NUM_RUNS);
    for(int i=0;i<NUM_RUNS;i++) {
        std::cout<<"Running Benchmark " << i+1 << "/" << NUM_RUNS << "...\n";
        results.push_back(runBenchmark(NUM_ORDERS));
    }
    
    long long totalMatching = 0;
    long long totalCancellation = 0;

    double totalMatchingThroughput = 0;
    double totalCancellationThroughput = 0;

    long long minMatching = results.front().matchingTime;
    long long maxMatching = results.front().matchingTime;

    long long minCancellation = results.front().cancellationTime;
    long long maxCancellation = results.front().cancellationTime;

    for (const auto& r : results) {

        totalMatching += r.matchingTime;
        totalCancellation += r.cancellationTime;

        totalMatchingThroughput += r.matchingThroughput;
        totalCancellationThroughput += r.cancellationThroughput;

        minMatching = std::min(minMatching, r.matchingTime);
        maxMatching = std::max(maxMatching, r.matchingTime);

        minCancellation = std::min(minCancellation, r.cancellationTime);
        maxCancellation = std::max(maxCancellation, r.cancellationTime);
    }

    std::cout << "\n================ BENCHMARK REPORT ================\n";
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\nMatching\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Average Time        : "
              << totalMatching / NUM_RUNS
              << " us\n";

    std::cout << "Minimum Time        : "
              << minMatching
              << " us\n";

    std::cout << "Maximum Time        : "
              << maxMatching
              << " us\n";

    std::cout << "Average Throughput  : "
              << totalMatchingThroughput / NUM_RUNS
              << " orders/sec\n";

    std::cout << "Trades Executed     : "
              << results.front().tradesExecuted
              << "\n";

    std::cout << "\nCancellation\n";
    std::cout << "--------------------------------------\n";

    std::cout << "Average Time        : "
              << totalCancellation / NUM_RUNS
              << " us\n";

    std::cout << "Minimum Time        : "
              << minCancellation
              << " us\n";

    std::cout << "Maximum Time        : "
              << maxCancellation
              << " us\n";

    std::cout << "Average Throughput  : "
              << totalCancellationThroughput / NUM_RUNS
              << " cancels/sec\n";

    return 0;
}