#ifndef INVENTORY_H
#define INVENTORY_H

void setInventory();

void clearInventory();
void printInventory();

void addItem(unsigned item, unsigned number);
void removeItem(unsigned item, unsigned number);

#endif // INVENTORY_H
