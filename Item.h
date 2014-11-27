#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

void setItem();

void getItem(unsigned id);

string getItemName(unsigned id);

unsigned getMaxStack(unsigned id);
unsigned getItemSize();

#endif // ITEM_H
