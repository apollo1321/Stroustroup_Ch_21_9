#include "common.h"
#include <sstream>
#include <exception>
#include <algorithm>


using std::istream;
using std::ostream;
using std::string;
using std::runtime_error;
using std::copy;


void end_of_loop (istream& ist , char term, const string& message)
{
    if (ist.fail())
    {
        ist.clear();
        char ch;
        if (ist >> ch && ch == term) return;
        throw runtime_error (message);
    }
}


void readString (istream& is, string& str)
{
    if (!is) return;
    char ch;
    if (is >> ch && ch != '"')
    {
        is.unget();
        is.clear (std::ios_base::failbit);
        return;
    }

    string val;
    while (is.get(ch) && ch != '"')
        val += ch;

    if (!is)
        throw runtime_error ("Bad string record");

    str = val;
}


istream& operator>> (istream& is, Purchase& purchase)
{
    if (!is) return is;
    char ch = 0;
    if (is >> ch && ch != '{')
    {
        is.unget();
        is.clear (std::ios_base::failbit);
        return is;
    }

    string name;
    double price;
    size_t count;

    readString (is, name);
    is >> price >> count >> ch;

    if (!is || ch != '}')
        throw runtime_error ("Bad purchase record");

    purchase.name = name;
    purchase.unit_price = price;
    purchase.count = count;

    return is;
}


istream& operator>> (istream& is, Order& order)
{
    if (!is) return is;
    char ch = 0;
    is >> ch;
    if (is.eof()) return is;
    if (ch != '{')
    {
        is.unget();
        is.clear (std::ios_base::failbit);
        return is;
    }

    string cliName;
    string cliAddress;
    string cliBirthDate;

    readString (is, cliName);
    readString (is, cliAddress);
    readString (is, cliBirthDate);
    is >> ch;
    if (!is || ch != '[')
        throw runtime_error ("Bad order record");

    order.cliName = cliName;
    order.cliAddress = cliAddress;
    order.cliBirthDate = cliBirthDate;
    order.purchases.clear();

    for (Purchase purchase; is >> purchase;)
        order.purchases.push_back (purchase);

    end_of_loop (is, ']', "Bad end of purchase records");
    is >> ch;
    if (!is || ch != '}')
        throw runtime_error ("Bad end of order");

    return is;
}


std::ostream& operator<< (std::ostream& os, const Purchase& purchase)
{
    return os << "{ \"" << purchase.name << "\" "
              << purchase.unit_price << " " << purchase.count << " }";
}


std::ostream& operator<< (std::ostream& os, const Order& order)
{
    os << "{ \""  << order.cliName      << "\" \"" << order.cliAddress
       << "\" \"" << order.cliBirthDate << "\" [";
    for (const Purchase& purchace : order.purchases) os << purchace;
    os << "] }";
    return os;
}
