#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include "SeaWar.h"
#include "SeaBattle.h"
using namespace sf;

int init() {
    bool flag = true; //проверка на окончание игры
    int x, y;
    sf::Vector2i localPosition; //координаты мыши
    sf::RenderWindow window(sf::VideoMode(1480, 520), "Sea Battle");
    window.setVerticalSyncEnabled(true);

    RectangleShape rect(Vector2f(40.f, 40.f));
    rect.setOutlineThickness(2.f);

    //текст, оповещающий о состоянии игры
    Text text;
    sf::Font font;
    font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
    text.setFont(font);
    text.setString("The game has started");
    text.setCharacterSize(26);
    text.setPosition(540, 0);
    text.setFillColor(sf::Color::White);

    ///////////////////////////////
    //отображение координатных осей
    Texture texture_x;
    Texture texture_y;
    texture_x.loadFromFile("image/x.png");
    texture_y.loadFromFile("image/y.png");

    Sprite sprite_x;
    Sprite sprite_y;
    Sprite sprite_x_2;
    Sprite sprite_y_2;
    Sprite sprite_x_3;
    Sprite sprite_y_3;

    sprite_x.setTexture(texture_x);
    sprite_x.setPosition(40, 40);

    sprite_y.setTexture(texture_y);
    sprite_y.setPosition(0, 80);
    
    sprite_x_2.setTexture(texture_x);
    sprite_x_2.setPosition(540, 40);

    sprite_y_2.setTexture(texture_y);
    sprite_y_2.setPosition(500, 80);

    sprite_x_3.setTexture(texture_x);
    sprite_x_3.setPosition(1040, 40);

    sprite_y_3.setTexture(texture_y);
    sprite_y_3.setPosition(1000, 80);

    ////////////////////////////////////////
    SeaWar f = SeaWar();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //следующий ход, если игра не закончена
        if (flag)
            f.next_move();

        //обработка нажатий, для управления стрельбой
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            localPosition = sf::Mouse::getPosition(window);
            x = localPosition.x;
            y = localPosition.y;
            if (x > 540 && x < 940 && y > 80 && y < 480) {
                f.coord_player_1[0] = (localPosition.x - 540) / 40;
                f.coord_player_1[1] = (localPosition.y - 80) / 40;
            }
        }

        //рисование
        window.clear();
        window.draw(text);
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                //рисование первого поля
                if (f.player1_ship[y][x] > 100)
                    rect.setFillColor(sf::Color::Red);
                else
                    rect.setFillColor(sf::Color::Blue);
                rect.setPosition(40 + x * 40, 80 + y * 40);
                window.draw(rect);

                //рисование второго поля
                if (f.player1_attack[y][x] == 2)
                    rect.setFillColor(sf::Color::Red);
                else if (f.player1_attack[y][x] == 1)
                    rect.setFillColor(sf::Color::Green);
                else
                    rect.setFillColor(sf::Color::Blue);
                rect.setPosition(540 + x * 40, 80 + y * 40);
                window.draw(rect);

                //рисование третьего поля
                if (f.player2_attack[y][x] == 2)
                    rect.setFillColor(sf::Color::Red);
                else if (f.player2_attack[y][x] == 1)
                    rect.setFillColor(sf::Color::Green);
                else
                    rect.setFillColor(sf::Color::Blue);
                rect.setPosition(1040 + x * 40, 80 + y * 40);
                window.draw(rect);

                //изменение статуса текста
                if (f.zero_ship(true) || f.zero_ship(false)) {
                    flag = false;
                    text.setFillColor(sf::Color::Blue);
                    if (f.zero_ship(true))
                        text.setString("First player won!!!");
                    else
                        text.setString("Second player won!!!");
                }
                else if (f.player_1_move)
                    text.setString("First player walks");
                else
                    text.setString("Second player walks");
                window.draw(text);

            }
        }
        window.draw(sprite_x);
        window.draw(sprite_y);
        window.draw(sprite_x_2);
        window.draw(sprite_y_2);
        window.draw(sprite_x_3);
        window.draw(sprite_y_3);
        window.display();
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    init();

}