#include <iostream>
#include <string>

#include "Inventory.h"
#include "Item.h"

using namespace std;

unsigned inventory[16][2];
unsigned invSlots = 16;

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
    cout << "Inventory cleared.\n";

    return;
}

void printInventory()
{
    cout << "Inventory:\n";
    for (unsigned invSlot = 0; invSlot < 16; invSlot++)
    {
        string name = getItemName(inventory[invSlot][0]);
        if (inventory[invSlot][0] != 0)
        {
            cout << name << " - Number: " << inventory[invSlot][1];
            cout << " - Max Stack: " << getMaxStack(inventory[invSlot][0]) << " - ID: " << inventory[invSlot][0] << endl;
        }
        else
            cout << "-\n";
    }

    return;
}

void addItem(unsigned item, unsigned number)
{
    unsigned itemsAdded = 0;
    for (unsigned invSlot = 0; invSlot < invSlots; invSlot++)
    {
        if ((inventory[invSlot][0] == item or inventory[invSlot][0] == 0) and item > 0)
        {
            while (inventory[invSlot][1] < getMaxStack(item) and number > 0)
            {
                inventory[invSlot][0] = item;
                inventory[invSlot][1]++;
                number--;
                itemsAdded++;
                break;
            }
        }
    }
    cout << "Added " << itemsAdded << " "<< getItemName(item) << " to inventory. - ID: " << item << " - Max Stack: " << getMaxStack(item) << endl;
    return;
}

void removeItem(unsigned item, unsigned number)
{
    unsigned itemsRemoved = 0;
    for (unsigned invSlot = 15; invSlot > 0; invSlot--)
    {
        if (inventory[invSlot][0] == item  and item > 0)
        {
            while (inventory[invSlot][1] > 0 and number > 0)
            {
                inventory[invSlot][1]--;
                if (inventory[invSlot][1] == 0)
                    inventory[invSlot][0] = 0;
                number--;
                itemsRemoved++;
                break;
            }
        }
    }
    cout << "Removed " << itemsRemoved << " " << getItemName(item) << " from inventory. - ID: " << item << " - Max Stack: " << getMaxStack(item) << endl;
    return;
}

unsigned checkItem(unsigned item)
{
    unsigned number = 0;
    for (unsigned invSlot = 0; invSlot < invSlots; invSlot++)
    {
        if (inventory[invSlot][0] == item and item > 0)
        {
            number += inventory[invSlot][1];
        }
    }
    cout << "There is " << number << " " << getItemName(item) << " in inventory. - ID: " << item << " - Max Stack: " << getMaxStack(item) << endl;
    return number;
}

unsigned getInvItem(unsigned invSlot)
{
    return inventory[invSlot][0];
}

unsigned getStackNumber(unsigned invSlot)
{
    return inventory[invSlot][1];
}

unsigned getInvMaxStack(unsigned invSlot)
{
    return getMaxStack(inventory[invSlot][0]);
}

unsigned getItemNumber(unsigned invSlot)
{
    return inventory[invSlot][1];
}
