#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    public:

    std::string name;
    unsigned id;
    unsigned value;

    Item(std::string name, unsigned id, unsigned value)
    {
        this->name = name;
        this->id = id;
        this->value = value;
    }
};

void setItem();
void getItem(unsigned id);

#endif
