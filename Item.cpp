#include <iostream>
#include <vector>

#include "Item.h"

std::vector< std::string > items;
std::vector< unsigned > items_value;

void setItem()
{
    items.push_back("");
    items_value.push_back(0);

    items.push_back("Fish");
    items_value.push_back(2);

    items.push_back("Wood");
    items_value.push_back(2);

    return;
}

void getItem(unsigned id)
{
    if (id < items.size() and id > 0)
    {
        std::cout << "ID: " << id << " - "<< items[id] << " - Value: " << items_value[id] << std::endl;
    }
    else if (id > 0)
    {
        std::cout << "ID: " << id << std::endl;
    }

    return;
}
