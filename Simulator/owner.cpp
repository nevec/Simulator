#include "owner.hpp"
#include "estate.hpp"
#include "config.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
using namespace std;

void Owner::buyEstate(shared_ptr<RealEstate> e) {
    if (e->getPrice() > balance)
        throw invalid_argument("Not enough money");
    
    balance -= e->getPrice();
    if (e->owner != nullptr)
        e->owner->sellEstate(e);
    e->owner = this;
    estate.push_back(move(e));
}

void Owner::sellEstate(shared_ptr<RealEstate> e) {
    if (e->owner == this) {
        auto it = find(estate.begin(), estate.end(), e);
        if (it == estate.end())
            throw invalid_argument("Error");
        this->estate.erase(it);
        e->owner = nullptr;
        balance += e->getPrice();
    } else {
        throw invalid_argument("User doesn't own the estate");
    }
}

void Owner::buyTitushkas(int amount) {
    if (balance >= amount*TitushkaPrice) {
        balance -= amount*TitushkaPrice;
        titushkas_amount += amount;
    } else {
        throw invalid_argument("Not enough money");
    }
}

void Owner::doRacket(Owner& o) {
    double percents = exp(-0.1*titushkas_amount);
    for (auto& e : o.estate) {
        int price = e->getPrice();
        e->setPrice(max<int>(1, price*(percents)));
    }
    titushkas_amount = 0;
}

void Owner::addEstateIncome() {
    for (auto& e : estate) {
        balance += e->getProfit();
    }
}

Owner::~Owner() {
  
}
