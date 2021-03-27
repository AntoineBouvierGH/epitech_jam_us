/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** main.cpp
*/

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

std::vector<sf::Sprite> putChoices(std::vector<std::string> playersDir)
{
    int i = 0;
    int size = playersDir.size();
    std::vector<sf::Sprite> spriteVect;
    sf::Vector2f vect(820.0, 840);

    while (i < size) {
        if (playersDir[i] == "UP") {
            sf::Sprite sprite;
            sprite.setRotation(270.f);
            sprite.setOrigin(40.f, 31.f);
            sprite.setPosition(vect);
            spriteVect.push_back(sprite);
        }
        if (playersDir[i] == "DOWN") {
            sf::Sprite sprite;
            sprite.setRotation(90.f);
            sprite.setOrigin(40.f, 31.f);
            sprite.setPosition(vect);
            spriteVect.push_back(sprite);
        }
        vect.x += 100;
        i++;
    }
    return (spriteVect);
}

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
    return (rez);
}

int gameLoop(sf::RenderWindow &window, int selectedLanguage, int playerNumber)
{
    sf::Texture texture;
    texture.loadFromFile("texture.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.setFramerateLimit(30);
    sf::Vector2f shipPos(0.0, 360.0);
    sprite.setPosition(shipPos);
    int x = 0;
    int y = 0;
    int p1p = 0;
    int p2p = 0;
    int p3p = 0;
    int p4p = 0;
    std::vector<std::string> playersDir;
    int currentPos = 2;
    std::string final = "################################################################################################";


    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Create a text
    sf::Text text("",font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    std::string loadingString = "";

    sf::Text voteText("",font);
    voteText.setCharacterSize(30);
    voteText.setStyle(sf::Text::Bold);
    sf::Vector2f votePos(840.0, 500.0);
    voteText.setPosition(votePos);
    const char *voteNowSTring[2] = { "vote now!", "votez maintenant"};
    int phase = 0;

    std::vector<sf::Sprite> spriteVect;
    sf::Texture textureArrow;
    textureArrow.loadFromFile("arrow.png");


    while (window.isOpen())
    {
        sf::Event event;
        spriteVect = putChoices(playersDir);
        if (phase == 0) {
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
                                p1p = 1;
                                playersDir.push_back("UP");
                            }
                            if (event.key.code == sf::Keyboard::Q)
                            {
                                p1p = 1;
                                playersDir.push_back("DOWN");
                            }
                        }
                        if (p2p == 0 && phase == 0) {
                            if (event.key.code == sf::Keyboard::P)
                            {
                                p2p = 1;
                                playersDir.push_back("UP");
                            }
                            if (event.key.code == sf::Keyboard::M)
                            {
                                p2p = 1;
                                playersDir.push_back("DOWN");
                            }
                        }
                        if (p3p == 0 && phase == 0) {
                            if (event.key.code == sf::Keyboard::D)
                            {
                                p3p = 1;
                                playersDir.push_back("UP");
                            }
                            if (event.key.code == sf::Keyboard::C)
                            {
                                p3p = 1;
                                playersDir.push_back("DOWN");
                            }
                        }
                        if (p4p == 0 && phase == 0) {
                            if (event.key.code == sf::Keyboard::J)
                            {
                                p4p = 1;
                                playersDir.push_back("UP");
                            }
                            if (event.key.code == sf::Keyboard::N)
                            {
                                p4p = 1;
                                playersDir.push_back("DOWN");
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (phase == 0) {
            voteText.setString(voteNowSTring[selectedLanguage]);
            if (final == loadingString) {
                loadingString = "";
                p2p = 0;
                p1p = 0;
                p3p = 0;
                p4p = 0;
                int nextMove = computeVotes(playersDir, currentPos);
                currentPos = nextMove;
                spriteVect.clear();
                playersDir.clear();
                phase = 1;
            }
            text.setString(loadingString);
            loadingString = loadingString + "#";
            window.clear();
            for (int i = 0; i < spriteVect.size(); i++) {
                spriteVect[i].setTexture(textureArrow);
                window.draw(spriteVect[i]);
            }
            window.draw(sprite);
            window.draw(text);
            window.draw(voteText);
            window.display();
        }
        else if (phase == 1) {
            for (int i = 0; i < playersDir.size(); i++) {
                    std::cout << playersDir[i] << std::endl;
                }
            float y = shipPos.y;
            float dest = currentPos * 180;
            if (dest > y) {
                while (y < dest) {
                    shipPos.y = y;
                    sprite.setPosition(shipPos);
                    window.clear();
                    window.draw(sprite);
                    window.display();
                    y += 10;
                }
            } else if (dest < y) {
                while (y > dest) {
                    shipPos.y = y;
                    sprite.setPosition(shipPos);
                    window.clear();
                    window.draw(sprite);
                    window.display();
                    y -= 10;
                }
            }
            for (int i = 0; i < playersDir.size(); i++) {
                playersDir[i] = "";
            }
            playersDir.clear();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
            }
            phase = 0;
        }
    }
    return 0;
}

int main(void)
{
    int selectedLanguage = 1;

    int playerNumber = 4;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Coop Entreprise");
    gameLoop(window, selectedLanguage, playerNumber);


}
