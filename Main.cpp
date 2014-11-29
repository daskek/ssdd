#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Config.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemList.h"
#include "Map.h"

using namespace sf;

Vector2u integer(0, 0);
Vector2u grid(0, 0);
Vector2i playerMove(0, 0);
Vector2i playerMoveNext(0, 0);

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

    Texture tileset;
    if (!tileset.loadFromFile("tileset.png"))
        return EXIT_FAILURE;

    Texture playerTexture;
    if (!playerTexture.loadFromFile("player.png"))
        return EXIT_FAILURE;

    Texture inv;
    if (!inv.loadFromFile("inventory.png"))
        return EXIT_FAILURE;

    Sprite item;
    item.setTexture(itemset);
    item.setTextureRect(IntRect(0, 0, tile, tile));

    Sprite mapTile[221];
    for (unsigned tiles = 0; tiles < 221; tiles++)
    {
        mapTile[tiles].setTexture(tileset);
        mapTile[tiles].setTextureRect(IntRect(getTile()*tile, 0, tile, tile));
        mapTile[tiles].setPosition(tile*(tiles-grid.x), tile*grid.y);

        if (tiles % 17 == 16)
        {
            grid.x += 17;
            grid.y++;
        }
    }
    grid.x = 0;
    grid.y = 0;

    Sprite player;
    player.setTexture(playerTexture);
    player.setTextureRect(IntRect(tile, 0, tile, tile));
    player.setPosition(tile*8, tile*6);

    Sprite spr_inv;
    spr_inv.setTexture(inv);
    spr_inv.setPosition(tile*11, tile*7);

    Text inv_number[16];
    for (unsigned items = 0; items < 16; items++)
    {
        inv_number[items].setFont(font);
        inv_number[items].setCharacterSize(16);
        inv_number[items].setColor(Color::Black);
    }

    Sprite inv_item[16];
    for (unsigned items = 0; items < 16; items++)
    {
        inv_item[items].setTexture(itemset);
        inv_item[items].setTextureRect(IntRect(0, 0, tile, tile));

        inv_item[items].setPosition(tile*(12+items-grid.x), tile*(8+grid.y));
        inv_number[items].setPosition(1+tile*(12+items-grid.x), -5+tile*(8+grid.y));

        if (items % 4 == 3)
        {
            grid.x += 4;
            grid.y++;
        }
    }
    grid.x = 0;
    grid.y = 0;

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

    View view(FloatRect(0, 0, tile*17, tile*13));
    view.setCenter(tile*8.5f, tile*6.5f);
    window.setView(view);

    while (window.isOpen())
    {
        Vector2i mouse_position(Mouse::getPosition(window));
        item.setPosition(mouse_position.x-16, mouse_position.y-16);

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

            else if (event.type == Event::KeyReleased)
            {
                if ((event.key.code == Keyboard::Up and playerMoveNext.y == -1) or (event.key.code == Keyboard::Down and playerMoveNext.y == 1) or
                    (event.key.code == Keyboard::Left and playerMoveNext.x == -1) or (event.key.code == Keyboard::Right and playerMoveNext.x == 1))
                {
                    if (tileMoved == 0)
                    {
                        playerMove.x = 0;
                        playerMove.y = 0;
                    }
                    playerMoveNext.x = 0;
                    playerMoveNext.y = 0;
                    std::cout << "Key released.\n";
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    player.setTextureRect(IntRect(tile, 3*tile, tile, tile));
                    if (tileMoved == 0)
                    {
                        playerMove.x = 0;
                        playerMove.y = -1;
                    }
                    playerMoveNext.x = 0;
                    playerMoveNext.y = -1;
                    std::cout << "Pressing key: Up\n";
                }
                if (event.key.code == Keyboard::Down)
                {
                    player.setTextureRect(IntRect(tile, 0, tile, tile));
                    if (tileMoved == 0)
                    {
                        playerMove.x = 0;
                        playerMove.y = 1;
                    }
                    playerMoveNext.x = 0;
                    playerMoveNext.y = 1;
                    std::cout << "Pressing key: Down\n";
                }
                if (event.key.code == Keyboard::Left)
                {
                    player.setTextureRect(IntRect(tile, tile, tile, tile));
                    if (tileMoved == 0)
                    {
                        playerMove.x = -1;
                        playerMove.y = 0;
                    }
                    playerMoveNext.x = -1;
                    playerMoveNext.y = 0;
                    std::cout << "Pressing key: Left\n";
                }
                if (event.key.code == Keyboard::Right)
                {
                    player.setTextureRect(IntRect(tile, 2*tile, tile, tile));
                    if (tileMoved == 0)
                    {
                        playerMove.x = 1;
                        playerMove.y = 0;
                    }
                    playerMoveNext.x = 1;
                    playerMoveNext.y = 0;
                    std::cout << "Pressing key: Right\n";
                }

                else if (event.key.code == Keyboard::Return)
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
                else if (event.key.code == Keyboard::Escape)
                    window.close();
                else if (event.key.code == Keyboard::I)
                {
                    if (showInventory == true)
                    {
                        printInventory();
                        showInventory = false;
                    }
                    else
                        showInventory = true;
                }

                else if (event.key.code == Keyboard::C)
                    clearInventory();
                else if (event.key.code == Keyboard::Q)
                    checkItem(prevInt);
            }

            else if (event.type == Event::MouseButtonPressed)
            {
                if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (mouse_position.x >= tile*11 and mouse_position.y >= tile*7)
                            addItem(prevInt, 1);
                        else
                            removeItem(prevInt, 1);
                    }
                if (Mouse::isButtonPressed(Mouse::Right))
                {
                    {
                        if (mouse_position.x >= tile*11 and mouse_position.y >= tile*7)
                            addItem(prevInt, 8);
                        else
                            removeItem(prevInt, 8);
                    }
                }
            }
        }

        if ((playerX + playerMove.x >= 0) and (playerX + playerMove.x <= 16) and (playerY + playerMove.y >= 0) and (playerY + playerMove.y <= 12))
        {
            player.move(playerMove.x*playerBaseSpeed, playerMove.y*playerBaseSpeed);
            tileMoved += playerBaseSpeed;

            if (moveAnimation == 0)
            {
                if (playerMove.y == -1)
                    player.setTextureRect(IntRect(0, 3*tile, tile, tile));
                else if (playerMove.y == 1)
                    player.setTextureRect(IntRect(0, 0, tile, tile));
                else if (playerMove.x == -1)
                    player.setTextureRect(IntRect(0, tile, tile, tile));
                else if (playerMove.x == 1)
                    player.setTextureRect(IntRect(0, 2*tile, tile, tile));
            }
            else if (moveAnimation == 1)
            {
                if (playerMove.y == -1)
                    player.setTextureRect(IntRect(2*tile, 3*tile, tile, tile));
                else if (playerMove.y == 1)
                    player.setTextureRect(IntRect(2*tile, 0, tile, tile));
                else if (playerMove.x == -1)
                    player.setTextureRect(IntRect(2*tile, tile, tile, tile));
                else if (playerMove.x == 1)
                    player.setTextureRect(IntRect(2*tile, 2*tile, tile, tile));
            }

            if (tileMoved == 32)
            {
                if (playerMove.y == -1)
                    player.setTextureRect(IntRect(tile, 3*tile, tile, tile));
                else if (playerMove.y == 1)
                    player.setTextureRect(IntRect(tile, 0, tile, tile));
                else if (playerMove.x == -1)
                    player.setTextureRect(IntRect(tile, tile, tile, tile));
                else if (playerMove.x == 1)
                    player.setTextureRect(IntRect(tile, 2*tile, tile, tile));

                tileMoved = 0;
                playerX += playerMove.x;
                playerY += playerMove.y;
                playerMove.x = playerMoveNext.x;
                playerMove.y = playerMoveNext.y;

                if (moveAnimation == 0)
                    moveAnimation = 1;
                else
                    moveAnimation = 0;
            }
        }

        window.clear();

        for (unsigned tiles = 0; tiles < 221; tiles++)
        {
            window.draw(mapTile[tiles]);
        }

        window.draw(player);

        if (showInventory == true)
        {
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
        }

        window.draw(text);
        window.draw(item);

        window.display();
    }
    return EXIT_SUCCESS;
}
