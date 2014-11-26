#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Config.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemList.h"

using namespace sf;

Vector2u integer(0, 0);

int main()
{
    setItem();
    setInventory();

    Font font;
    if (!font.loadFromFile("SSDD.ttf"))
        return EXIT_FAILURE;

    Texture itemset;
    if (!itemset.loadFromFile("itemset.png"))
        return EXIT_FAILURE;

    Texture inv;
    if (!inv.loadFromFile("inventory.png"))
        return EXIT_FAILURE;

    Sprite item;
    item.setTexture(itemset);
    item.setTextureRect(IntRect(0, 0, tile, tile));

    Sprite spr_inv;
    spr_inv.setTexture(inv);
    spr_inv.setPosition(tile*11, tile*7);

    Text inv_number[16];
    for (unsigned items = 0; items < 16; items++)
    {
        inv_number[items].setFont(font);
        inv_number[items].setCharacterSize(8);
        inv_number[items].setColor(Color::Black);
    }

    Sprite inv_item[16];
    for (unsigned items = 0; items < 16; items++)
    {
        inv_item[items].setTexture(itemset);
        inv_item[items].setTextureRect(IntRect(0, 0, tile, tile));
        if (items >= 12)
        {
            inv_item[items].setPosition(tile*(0+items), tile*(11));
            inv_number[items].setPosition(2+tile*(0+items), 2+tile*(11));
        }
        else if (items >= 8)
        {
            inv_item[items].setPosition(tile*(4+items), tile*(10));
            inv_number[items].setPosition(2+tile*(4+items), 2+tile*(10));
        }
        else if (items >= 4)
        {
            inv_item[items].setPosition(tile*(8+items), tile*(9));
            inv_number[items].setPosition(2+tile*(8+items), 2+tile*(9));
        }
        else
        {
            inv_item[items].setPosition(tile*(12+items), tile*(8));
            inv_number[items].setPosition(2+tile*(12+items), 2+tile*(8));
        }
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(8, 2);
    text.setColor(Color::Black);
    text.setString(str);

    Vector2u screen_dimensions(tile*17, tile*13);
    RenderWindow window(VideoMode(screen_dimensions.x, screen_dimensions.y), "SSDD", Style::Close);
    window.setFramerateLimit(fps);
    window.setMouseCursorVisible(true);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b' and text.getString() != "")
                {
                    str.erase(str.size() - 1, 1);
                    text.setString(str);
                }
                else if (event.text.unicode == '\b' and text.getString() == "")
                {
                    text.setString(str);
                }
                else if (event.text.unicode >= 48 and event.text.unicode <= 57 and event.text.unicode != 13 and event.text.unicode != 27
                         and (text.getLocalBounds().width + 18) < screen_dimensions.x)
                {
                    str += static_cast<char>(event.text.unicode);
                    text.setString(str);
                }
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Return)
                {
                    integer.x = 0;
                    integer.y = 0;
                    strstream.clear();
                    strstream.str("");
                    strstream.str(str);
                    strstream >> integer.x;
                    prevInt = integer.x;
                    if (integer.x < ((itemset.getSize().x/tile)*(itemset.getSize().y/tile)))
                    {
                        getItem(integer.x);
                        while (integer.x >= (itemset.getSize().x/tile))
                        {
                            integer.x -= (itemset.getSize().x/tile);
                            integer.y++;
                        }
                        item.setTextureRect(IntRect(integer.x*tile, integer.y*tile, tile, tile));
                    }
                    str = "";
                    text.setString(str);
                }
                else if (event.key.code == Keyboard::I)
                    printInventory();
                else if (event.key.code == Keyboard::C)
                    clearInventory();
                else if (event.key.code == Keyboard::Q)
                    checkItem(prevInt);
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                unsigned number = 1;
                if (event.key.code == Keyboard::LShift)
                    number = 9;
                if (Mouse::isButtonPressed(Mouse::Left))
                    addItem(prevInt, number);
                else if (Mouse::isButtonPressed(Mouse::Right))
                    removeItem(prevInt, number);
            }
        }
        Vector2i mouse_position(Mouse::getPosition(window));
        item.setPosition(mouse_position.x-16, mouse_position.y-16);

        window.clear(Color(216, 248, 120, 0));

        window.draw(spr_inv);
        for (unsigned invSlot = 0; invSlot < 16; invSlot++)
        {
            integer.x = getInvItem(invSlot);
            integer.y = 0;
            if (integer.x < ((itemset.getSize().x/tile)*(itemset.getSize().y/tile)))
            {
                while (integer.x >= (itemset.getSize().x/tile))
                {
                    integer.x -= (itemset.getSize().x/tile);
                    integer.y++;
                }
                inv_item[invSlot].setTextureRect(IntRect(integer.x*tile, integer.y*tile, tile, tile));
            }
            window.draw(inv_item[invSlot]);
            if (getInvMaxStack(invSlot) > 1)
            {
                unsigned number = getItemNumber(invSlot);
                strstream.clear();
                strstream.str("");
                strstream << number;
                inv_number[invSlot].setString(strstream.str());
                window.draw(inv_number[invSlot]);
            }
        }

        window.draw(text);
        window.draw(item);

        window.display();
    }
    return EXIT_SUCCESS;
}
