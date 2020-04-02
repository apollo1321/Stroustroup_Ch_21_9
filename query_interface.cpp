#include "query_interface.h"
#include <fstream>
#include <exception>
#include <algorithm>
using std::runtime_error;

Query::Query (const string& filename)
{
    readOrders (filename);
}

void Query::readOrders (const string &filename)
{
    std::ifstream ifs{ filename };
    if (!ifs)
        throw runtime_error ("Can't open file " + filename + " for reading");

    for (Order order; ifs >> order;) orders.push_back (order);
}

void Query::writeOrders (const string &filename) const
{
    std::ofstream ofs { filename };
    if (!ofs)
        throw runtime_error ("Can't open file " + filename + " for writting");

    for (const Order& order : orders) ofs << order;
}

void Query::sortBy (SortType type)
{

    switch (type)
    {
    case byCliName:
        std::sort (orders.begin(), orders.end(), [] (const Order& a, const Order& b) { return a.cliName < b.cliName; });
        break;
    case byCliAddr:
        std::sort (orders.begin(), orders.end(), [] (const Order& a, const Order& b) { return a.cliAddress < b.cliAddress; });
        break;
    case byCliBirth:
        std::sort (orders.begin(), orders.end(), [] (const Order& a, const Order& b) { return a.cliBirthDate < b.cliBirthDate; });
        break;
    }
}

template<typename T, typename In, typename Pred>
// Requires Input_iterator<In>()
// Predicate<Pred, Value_type<In>>()
vector<T> findAllValues (In first, In last, Pred pred)
{
    vector<T> res;
    while (true)
    {
        first = std::find_if (first, last, pred);
        if (first != last)
            res.push_back (*first);
        ++first;
    }
    return res;
}

vector<Order> Query::findAddr (const string &val)
{
    return findAllValues<Order> (orders.begin(), orders.end(), [val] (const Order& a) { return a.cliAddress == val; });
}

vector<Order> Query::findName (const string &val)
{
    return findAllValues<Order> (orders.begin(), orders.end(), [val] (const Order& a) { return a.cliName == val; });
}

struct FindByItemName
{
    string val;
    bool operator() (const Order& order)
    {
        for (auto purchase : order.purchases)
            if (purchase.name == val)
                return true;
        return false;
    }
};

vector<Order> Query::findItemName (const string &val)
{
    return findAllValues<Order> (orders.begin(), orders.end(), FindByItemName{ val });
}








