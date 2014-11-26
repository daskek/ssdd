#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{
    public:
        string name;
        unsigned id;
        unsigned maxStack;
        unsigned value;

        Item(string name, unsigned id, unsigned maxStack, unsigned value)
        {
            this->name = name;
            this->id = id;
            this->maxStack = maxStack;
            this->value = value;
        }
};

void setItem();

void getItem(unsigned id);

string getItemName(unsigned id);

unsigned getMaxStack(unsigned id);

#endif // ITEM_H
