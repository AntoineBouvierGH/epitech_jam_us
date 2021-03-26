/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** main.cpp
*/

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

int computeVotes(std::vector<std::string> playersDir, int currentPos)
{
    int rez = 0;
    int count = 0;
    int i = 0;
    int s = playersDir.size();

    while (i < s) {
        if (playersDir[i] == "UP")
            count--;
        else if (playersDir[i] == "DOWN")
            count++;
        i++;
    }
    rez = currentPos + count;
    if (rez < 0)
        rez = 0;
    if (rez > 5)
        rez = 5;
    std::cout << count << currentPos << rez << std::endl;
    return (rez);
}

int main(void)
{
    sf::Texture texture;
    texture.loadFromFile("texture.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Coop Entreprise");
    window.setFramerateLimit(30);
    sf::Vector2f spriteVect(0.0, 360.0);
    sprite.setPosition(spriteVect);
    int x = 0;
    int y = 0;
    int playerNumber = 2;
    int p1p = 0;
    int p2p = 0;
    std::vector<std::string> playersDir;
    int currentPos = 2;
    std::string final = "##########################################################################################";


    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Create a text
    sf::Text text("",font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    std::string loadingString = "";
    int phase = 0;



    while (window.isOpen())
    {
        sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        if (p1p == 0 && phase == 0) {
                            if (event.key.code == sf::Keyboard::A)
                            {
                                printf("A\n");
                                p1p = 1;
                                playersDir.push_back("UP");
                            }
                            if (event.key.code == sf::Keyboard::Q)
                            {
                                printf("Q\n");
                                p1p = 1;
                                playersDir.push_back("DOWN");
                            }
                        }
                        if (p2p == 0 && phase == 0) {
                            if (event.key.code == sf::Keyboard::P)
                            {
                                printf("P\n");
                                p2p = 1;
                                playersDir.push_back("UP");
                            }
                            if (event.key.code == sf::Keyboard::M)
                            {
                                printf("M\n");
                                p2p = 1;
                                playersDir.push_back("DOWN");
                            }
                        }

                        break;
                    default:
                        break;
                }
            }
        if (phase == 0) {
            if (final == loadingString) {
                loadingString = "";
                p2p = 0;
                p1p = 0;
                int nextMove = computeVotes(playersDir, currentPos);
                currentPos = nextMove;
                playersDir.clear();
                phase = 1;
            }
            text.setString(loadingString);
            loadingString = loadingString + "#";
            window.clear();
            window.draw(sprite);
            window.draw(text);
            window.display();
        }
        if (phase == 1) {
            printf("hello");
            float y = spriteVect.y;
            float dest = currentPos * 180;
            if (dest > y) {
                while (y < dest) {
                    spriteVect.y = y;
                    sprite.setPosition(spriteVect);
                    window.clear();
                    window.draw(sprite);
                    window.display();
                    y += 10;
                }
            } else if (dest < y) {
                while (y > dest) {
                    spriteVect.y = y;
                    sprite.setPosition(spriteVect);
                    window.clear();
                    window.draw(sprite);
                    window.display();
                    y -= 10;
                }
            }
            phase = 0;
        }
    }
    return 0;
}
