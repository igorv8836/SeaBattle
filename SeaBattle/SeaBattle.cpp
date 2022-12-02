
//int main() {
//	setlocale(LC_ALL, "ru");
//	srand(time(0));
//	SeaWar a = SeaWar();
//}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include "SeaWar.h"
#include "SeaBattle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture texture;
    if (!texture.loadFromFile("water.png"))
    {
        std::cout << "Error!";
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}