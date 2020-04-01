#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <list>
#include "common.h"

using namespace std;

struct OrderSum
{
    double operator() (double a, const Order& b)
    {
        for (auto& purchase : b.purchases) a += purchase.unit_price * purchase.count;
        return a;
    }
};

int main()
{
    string in  = "in.txt";
    string out = "out.txt";
    string in2 = "in2.txt";

    ifstream ifs{ in };
    if (!ifs)
    {
        cerr << "Can' open file " + in <<  endl;
        return -1;
    }
    ifstream ifs1{ in2 };
    if (!ifs1)
    {
        cerr << "Can' open file " + in <<  endl;
        return -1;
    }

    ofstream ofs{ out };
    if (!ofs)
    {
        cerr << "Can't open file" + out << endl;
        return -1;
    }

    vector<Order> data { istream_iterator<Order>{ ifs }, istream_iterator<Order>{ } };
    list<Order> data_lst { istream_iterator<Order>{ ifs1 }, istream_iterator<Order>{ } };

    auto sort_by_addr = [] (const Order& a, const Order& b) { return a.cliAddress < b.cliAddress; };

    sort (data.begin(), data.end(), sort_by_addr);

    data_lst.sort (sort_by_addr);

    merge (data.begin(), data.end(), data_lst.begin(), data_lst.end(), ostream_iterator<Order> { ofs, "\n" },
           sort_by_addr);

    double sum = 0;
    sum = accumulate (data.begin(), data.end(), sum, OrderSum{ });
    sum = accumulate (data_lst.begin(), data_lst.end(), sum, OrderSum{ });
    cout << "Sum of all orders: " << sum << endl;

    return 0;
}
