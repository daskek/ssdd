#include <iostream>
#include <string>
#include <vector>

#include "Item.h"

using namespace std;

vector< std::string > items;
vector< unsigned > items_value;

void setItem()
{
    items.push_back("Null");
    items_value.push_back(0);

    items.push_back("Fish");
    items_value.push_back(2);

    items.push_back("Wood");
    items_value.push_back(2);

    return;
}

void getItem(unsigned id)
{
    if (id < items.size() and id >= 0)
    {
        cout << "ID: " << id << " - " << items[id] << " - Value: " << items_value[id] << endl;
    }
    else if (id > 0)
    {
        cout << "ID: " << id << endl;
    }

    return;
}

string getItemName(unsigned id)
{
    return items[id];
}
