#include <iostream>
#include <string>

#include "Inventory.h"
#include "Item.h"

using namespace std;

unsigned inventory[16][2];

void setInventory()
{
    return;
}

void clearInventory()
{
    for (unsigned invSlot = 0; invSlot < 16; invSlot++)
    {
        inventory[invSlot][0] = 0;
        inventory[invSlot][1] = 0;
    }

    return;
}

void printInventory()
{
    cout << "Inventory:\n";
    for (unsigned invSlot = 0; invSlot < 16; invSlot++)
    {
        string name = getItemName(inventory[invSlot][0]);
        cout << "ID: " << inventory[invSlot][0] << " - " << name << " - Number: "<< inventory[invSlot][1] << endl;
    }

    return;
}

void addItem(unsigned item, unsigned number)
{
    return;
}

void removeItem(unsigned item, unsigned number)
{
    return;
}
