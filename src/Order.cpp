#include <iostream>
#include "Order.h"

 Order::Order(std::uint64_t orderId, OrderSide side, OrderType type, double price, std::uint32_t quantity, std:: uint64_t timestamp)
    : orderId(orderId), side(side), type(type), price(price), quantity(quantity), timestamp(timestamp) 
    {}

void Order::display() const {
    std::cout<<"Order ID: " << orderId
            <<" | Side: " << (side==OrderSide::Buy? "Buy":"Sell")
            <<" | Type: " << (type==OrderType::Limit? "Limit":"Market")
            <<" | Price: " << price
            <<" | Quantity: " << quantity
            <<" | Timestamp: " << timestamp
            << std::endl;
}

std::uint64_t Order::getOrderId() const {
    return orderId;
}

OrderSide Order::getSide() const {
    return side;
}

OrderType Order::getType() const {
    return type;
}

double Order::getPrice() const {
    return price;
}

std::uint32_t Order::getQuantity() const {
    return quantity;
}

std::uint64_t Order::getTimestamp() const {
    return timestamp;
}