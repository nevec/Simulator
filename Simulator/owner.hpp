#ifndef OWNER_HPP
#define OWNER_HPP

#include <memory>
#include <string>
#include <utility>
#include <vector>
using std::string;
using std::vector;
using std::shared_ptr;

class RealEstate;

class Owner {
private:
    string first_name, last_name;
    int balance;
    int titushkas_amount;
    vector<shared_ptr<RealEstate>> estate;
    
public:
    Owner() : first_name("noname"), last_name("noname"), balance(0),
        titushkas_amount(0), estate() {}
    Owner(string fname, string lname, int bal) : first_name(std::move(fname)), last_name(std::move(lname)), balance(bal),
        titushkas_amount(0), estate() {}
    
    void buyEstate(shared_ptr<RealEstate> e);
    void sellEstate(shared_ptr<RealEstate> e);
    void buyTitushkas(int amount);
    void doRacket(Owner &o);
    void addEstateIncome();
    
    string getName() const { return first_name + " " + last_name; }
    vector<shared_ptr<RealEstate>> getEstate() const { return estate; }
    int getBalance() const { return balance; }
    int getTitushkas() const { return titushkas_amount; }
    ~Owner() {}
};

#endif // OWNER_HPP
