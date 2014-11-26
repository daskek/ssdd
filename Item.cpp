#include <iostream>
#include <string>
#include <vector>

#include "Item.h"

using namespace std;

vector< string > items;
vector< unsigned > items_maxStack;
vector< unsigned > items_value;

unsigned defaultStack = 8;

void setItem()
{
    items.push_back("Null");
    items_maxStack.push_back(0);
    items_value.push_back(0);

    items.push_back("Fish");
    items_maxStack.push_back(defaultStack);
    items_value.push_back(2);

    items.push_back("Wood");
    items_maxStack.push_back(defaultStack);
    items_value.push_back(2);

    return;
}

void getItem(unsigned id)
{
    if (id < items.size() and id >= 0)
    {
        cout << "ID: " << id << " - " << items[id] << " - Max Stack: " << items_maxStack[id] << " - Value: " << items_value[id] << endl;
    }
    else if (id > 0)
    {
        cout << "ID: " << id << endl;
    }

    return;
}

string getItemName(unsigned id)
{
    if (id >= 0 and id <= items.size())
        return items[id];
    else
        return "Unknown";
}

unsigned getMaxStack(unsigned id)
{
    return items_maxStack[id];
}
