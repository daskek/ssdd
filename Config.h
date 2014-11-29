#ifndef CONFIG_H
#define CONFIG_H

#define tile 32
#define fps 60

unsigned prevInt = 0;
unsigned tileMoved = 0;
unsigned moveAnimation = 0;

int playerBaseSpeed = 2;
int playerX = 8;
int playerY = 6;

std::string str = "";

std::stringstream strstream;

enum playerDirection { Up, Down, Left, Right };
playerDirection direction = Down;

bool showInventory = true;

void setConfig();

#endif // CONFIG_H
