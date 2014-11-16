#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Item.h"

#define tile 32

using namespace sf;

unsigned fps = 60;

std::string str = "";

std::stringstream strstream;

int main()
{
    setItem();
    Font font;
    if (!font.loadFromFile("SSDD.ttf"))
        return EXIT_FAILURE;

    Texture itemset;
    if (!itemset.loadFromFile("itemset.png"))
        return EXIT_FAILURE;

    Sprite item;
    item.setTexture(itemset);
    item.setTextureRect(IntRect(0, 0, tile, tile));

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
                else if (event.text.unicode < 128 and event.text.unicode != 13 and event.text.unicode != 27
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
                    Vector2u integer(0, 0);
                    strstream.clear();
                    strstream.str("");
                    strstream.str(str);
                    strstream >> integer.x;
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
            }
        }
        Vector2i mouse_position(Mouse::getPosition(window));
        item.setPosition(mouse_position.x-16, mouse_position.y-16);

        window.clear(Color(216, 248, 120, 0));

        window.draw(text);
        window.draw(item);

        window.display();
    }
    return EXIT_SUCCESS;
}
