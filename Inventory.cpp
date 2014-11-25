#include <iostream>
#include <string>

#include "Inventory.h"
#include "Item.h"

using namespace std;

unsigned inventory[16][2];
unsigned invSlots = 16;
unsigned maxStack = 16;

void setInventory()
{
    return;
}

void clearInventory()
{
    for (unsigned invSlot = 0; invSlot < invSlots; invSlot++)
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
    for (unsigned invSlot = 0; invSlot < invSlots; invSlot++)
    {
        if ((inventory[invSlot][0] == item or inventory[invSlot][0] == 0) and item > 0)
        {
            if (inventory[invSlot][1] < maxStack)
            {
                inventory[invSlot][0] = item;
                inventory[invSlot][1]++;
                break;
            }
        }
    }
    return;
}

void removeItem(unsigned item, unsigned number)
{
    return;
}
