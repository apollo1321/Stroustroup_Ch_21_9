#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>
#include <iostream>

struct Purchase
{
    std::string name;
    double unit_price;
    size_t count;
};

struct Order
{
    std::string cliName;
    std::string cliAddress;
    std::string cliBirthDate;
    std::vector<Purchase> purchases;
};

std::istream& operator>> (std::istream&, Purchase&);
std::ostream& operator<< (std::ostream&, const Purchase&);


std::istream& operator>> (std::istream&, Order&);
std::ostream& operator<< (std::ostream&, const Order&);


#endif // COMMON_H
