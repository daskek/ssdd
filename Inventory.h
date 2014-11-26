#ifndef INVENTORY_H
#define INVENTORY_H

void setInventory();

void clearInventory();
void printInventory();

void addItem(unsigned item, unsigned number);
void removeItem(unsigned item, unsigned number);

unsigned checkItem(unsigned item);

unsigned getInvItem(unsigned slot);
unsigned getStackNumber(unsigned invSlot);
unsigned getInvMaxStack(unsigned invSlot);
unsigned getItemNumber(unsigned invSlot);

#endif // INVENTORY_H
