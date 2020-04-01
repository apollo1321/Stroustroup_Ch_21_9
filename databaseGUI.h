#ifndef DATABASEGUI_H
#define DATABASEGUI_H
#include "../Graph_lib/GUI.h"
#include "common.h"
#include <sstream>
#include <fstream>

using Graph_lib::Point;
using std::string;
using std::stringstream;

class DataBaseWindow : Graph_lib::Window
{
    Graph_lib::In_box cliName;
    Graph_lib::In_box cliAddress;
    Graph_lib::In_box cliBirthDate;
    Graph_lib::Button nextOrder;


    Graph_lib::In_box purchaseName;
    Graph_lib::In_box purchasePrice;
    Graph_lib::In_box purchaseCount;
    Graph_lib::Button addPurchase;

    Graph_lib::In_box fileName;
    Graph_lib::Button saveButton;

    static constexpr int marginY      = 30;
    static constexpr int marginX      = 130;
    static constexpr int itemWidth    = 200;
    static constexpr int itemHeight   = 30;
    static constexpr int windowWidth  = 3*marginX + 4*itemWidth + marginX/2 + marginX/2;
    static constexpr int windowHeight = 4*marginY + 3*itemHeight;

public:
    DataBaseWindow (Point xy)
        : Graph_lib::Window{ xy, windowWidth, windowHeight, "Orders database modifier"},
          cliName      { Point{   marginX              , marginY }, itemWidth, itemHeight, "Client Name:"       },
          cliAddress   { Point{ 2*marginX +   itemWidth, marginY }, itemWidth, itemHeight, "Client Address:"    },
          cliBirthDate { Point{ 3*marginX + 2*itemWidth, marginY }, itemWidth, itemHeight, "Client Birth Date:" },
          nextOrder    { Point{ 3*marginX + 3*itemWidth + marginX/2, marginY }, itemWidth, itemHeight, "Set", cb_nextOrder},

          purchaseName { Point{   marginX              , 2*marginY + itemHeight }, itemWidth, itemHeight, "Purchase Name:" },
          purchasePrice{ Point{ 2*marginX +   itemWidth, 2*marginY + itemHeight }, itemWidth, itemHeight, "Purchase Price:"},
          purchaseCount{ Point{ 3*marginX + 2*itemWidth, 2*marginY + itemHeight }, itemWidth, itemHeight, "Purchase Count:"},
          addPurchase  { Point{ 3*marginX + 3*itemWidth + marginX/2, 2*marginY + itemHeight }, itemWidth, itemHeight, "Add", cb_addPurchase},

          fileName     { Point{   marginX              , 3*marginY + 2*itemHeight }, 3*itemWidth + 2*marginX, itemHeight, "Filename:"},
          saveButton   { Point{ 3*marginX + 3*itemWidth + marginX/2, 3*marginY + 2*itemHeight }, itemWidth  , itemHeight, "Save" ,
                         cb_save}
    {
        attach (cliName);
        attach (cliAddress);
        attach (cliBirthDate);
        attach (nextOrder);
        attach (purchaseName);
        attach (purchasePrice);
        attach (purchaseCount);
        attach (addPurchase);
        attach (fileName);
        attach (saveButton);
    }

private:
    std::vector<Order> orders;

    static void cb_nextOrder (Graph_lib::Address, Graph_lib::Address addr)
    {
        static_cast<DataBaseWindow*>(addr)->next();
    }

    static void cb_addPurchase (Graph_lib::Address, Graph_lib::Address addr)
    {
        static_cast<DataBaseWindow*>(addr)->add();
    }

    static void cb_save (Graph_lib::Address, Graph_lib::Address addr)
    {
        static_cast<DataBaseWindow*>(addr)->save();
    }


    void next ()
    {
        string name = cliName.get_string();
        string address = cliAddress.get_string();
        string birthDate = cliBirthDate.get_string();
        if (!name.empty())
            orders.push_back(Order{ name, address, birthDate, {} });
    }

    void add ()
    {
        string name = purchaseName.get_string();

        stringstream priceStream{ purchasePrice.get_string() };
        double priceVal = 0.0;
        if (!(priceStream >> priceVal)) return;

        stringstream countStream{ purchaseCount.get_string() };
        size_t countVal = 0;
        if (!(countStream >> countVal)) return;

        if (!orders.empty())
            orders.back().purchases.push_back(Purchase{name, priceVal, countVal});
    }

    void save ()
    {
        string file = fileName.get_string();
        std::ofstream ofs{ file };
        if (!ofs) return;
        for (const auto& order : orders) ofs << order << '\n';
        return;
    }
};


#endif // DATABASEGUI_H
