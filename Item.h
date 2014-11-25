#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{
    public:
        string name;
        unsigned id;
        unsigned value;

        Item(string name, unsigned id, unsigned value)
        {
            this->name = name;
            this->id = id;
            this->value = value;
        }
};

void setItem();

void getItem(unsigned id);

string getItemName(unsigned id);

#endif // ITEM_H
