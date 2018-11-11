#ifndef ESTATE_HPP
#define ESTATE_HPP

#include "owner.hpp"
#include <memory>
#include <string>
#include <utility>
#include <iostream>


class RealEstate {
private:
    string name;
    int profit;
    int price;
    Owner *owner;
    
public:
    RealEstate() : name("noname"), profit(0), price(0), owner(nullptr) { }
    RealEstate(string name, int price, int profit) : name(std::move(name)), profit(profit), price(price), owner(nullptr) { }
    
    const string& getName() const { return name; }
    int getProfit() const { return profit; }
    void setProfit(int profit) { this->profit = profit; }
    int getPrice() const { return price; }
    void setPrice(int price) { this->price = price; }
    Owner* getOwner() const { return owner; }
    
    friend void Owner::buyEstate(shared_ptr<RealEstate> e);
    friend void Owner::sellEstate(shared_ptr<RealEstate> e);
    ~RealEstate() {}
};

#endif // ESTATE_HPP
