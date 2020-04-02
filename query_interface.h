#ifndef QUERTY_INTERFACE_H
#define QUERTY_INTERFACE_H

#include "common.h"

using std::vector;
using std::string;

class Query
{
    vector<Order> orders;
public:
    Query () = default;
    Query (const string& filename);

    void readOrders (const string& filename);
    void writeOrders (const string& filename) const;

    void addOrder (const Order& order)
    {
        orders.push_back (order);
    }

    enum SortType
    {
        byCliName, byCliAddr, byCliBirth
    };

    void sortBy (SortType type = byCliName);

    void clearData ()
    {
        orders.clear();
    }

    vector<Order> findName     (const string& val);
    vector<Order> findAddr     (const string& val);
    vector<Order> findItemName (const string& val);

    const vector<Order>& getOrders () const
    {
        return orders;

    }
    vector<Order> getOrders ()
    {
        return orders;
    }
};

#endif // QUERTY_INTERFACE_H
