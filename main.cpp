/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** main.cpp
*/

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

std::vector<sf::Sprite> getAsteroids(std::string line)
{
    float x = 1700;
    float y = 0;
    int i = 0;
    std::vector<sf::Sprite>  asteroids;

    while (i < 6) {
        if (line[i] == '#') {
            sf::Sprite sprite;
            sf::Vector2f vect;
            vect.x = x;
            vect.y = y;
            sprite.setPosition(vect);
            asteroids.push_back(sprite);
            std::cout << "#"<<std::endl;
        }
        y += 180;
        i++;
    }
    return (asteroids);
}

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
    texture.loadFromFile("Textures/ship.png");
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
    font.loadFromFile("Fonts/arial.ttf");
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

    const char *voteNowSTring[4] = { "vote now!", "votez maintenant!", "vota ahora!", "wähle nun!"};
    const char *scoreString[4] = {"Your score is: ", "votre score est: ", "Tu puntaje es: ", "dein Ergebnis ist: "};
    const char *nbPlayerString[4] = {"players number is: ", "le nombre de joueurs est: ", "el numero de jugador es: ", "spielernummer ist: "};
    int phase = 0;

    std::vector<sf::Sprite> spriteVect;
    sf::Texture textureArrow;
    textureArrow.loadFromFile("Textures/arrow.png");


    std::ifstream file;
    std::string line;
    file.open("map.txt");
    getline(file, line);
    if (line == "end")
        return (1);
    std::vector<sf::Sprite> asteroids = getAsteroids(line);

    sf::Text scoreText("", font);
    scoreText.setCharacterSize(30);
    scoreText.setStyle(sf::Text::Bold);
    votePos.y = 200;
    scoreText.setPosition(votePos);

    sf::Text nbPlayerText("", font);
    nbPlayerText.setCharacterSize(30);
    nbPlayerText.setStyle(sf::Text::Bold);
    votePos.y = 10;
    nbPlayerText.setPosition(votePos);
    std::string nbPlayerStr = nbPlayerString[selectedLanguage] + std::to_string(playerNumber);
    nbPlayerText.setString(nbPlayerStr);


    int score = 0;
    std::string strScoreText;


    while (window.isOpen())
    {
        sf::Event event;
        strScoreText = std::to_string(score);
        strScoreText = scoreString[selectedLanguage] + strScoreText;
        scoreText.setString(strScoreText);
        spriteVect = putChoices(playersDir);
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
                    if (p3p == 0 && phase == 0 && playerNumber >= 3) {
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
                    if (p4p == 0 && phase == 0 && playerNumber == 4) {
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
            for (int i = 0; i < asteroids.size(); i++) {
                asteroids[i].setTexture(texture);
                window.draw(asteroids[i]);
            }
            window.draw(sprite);
            window.draw(text);
            window.draw(voteText);
            window.draw(scoreText);
            window.draw(nbPlayerText);
            window.display();
        }
        else if (phase == 1) {
            float tmpX = asteroids[0].getPosition().x;
            float y = shipPos.y;
            float dest = currentPos * 180;
            if (dest > y) {
                while (y < dest) {
                    shipPos.y = y;
                    sprite.setPosition(shipPos);
                    window.clear();
                    tmpX -= 10;
                    for (int i = 0; i < asteroids.size(); i++) {
                        sf::Vector2f tmpPos = asteroids[i].getPosition();
                        tmpPos.x = tmpX;
                        asteroids[i].setPosition(tmpPos);
                        window.draw(asteroids[i]);
                    }
                    window.draw(sprite);
                    window.draw(scoreText);
                    window.draw(nbPlayerText);
                    window.display();
                    y += 10;
                }
            } else if (dest < y) {
                while (y > dest) {
                    shipPos.y = y;
                    sprite.setPosition(shipPos);
                    window.clear();
                    tmpX -= 10;
                    for (int i = 0; i < asteroids.size(); i++) {
                        sf::Vector2f tmpPos = asteroids[i].getPosition();
                        tmpPos.x = tmpX;
                        asteroids[i].setPosition(tmpPos);
                        window.draw(asteroids[i]);
                    }
                    window.draw(sprite);
                    window.draw(scoreText);
                    window.draw(nbPlayerText);
                    window.display();
                    y -= 10;
                }
            }
            while (tmpX > -550) {
                window.clear();
                for (int i = 0; i < asteroids.size(); i++) {
                    sf::Vector2f tmpPos = asteroids[i].getPosition();
                    tmpPos.x = tmpX;
                    asteroids[i].setPosition(tmpPos);
                    window.draw(asteroids[i]);
                }
                window.draw(sprite);
                window.draw(scoreText);
                window.draw(nbPlayerText);
                window.display();
                tmpX -= 10;
            }
            playersDir.clear();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return (0);
                }
            }
            if (line[currentPos] != ' ')
                return (0);
            getline(file, line);
            if (line == "end")
                return (1);
            asteroids.clear();
            asteroids = getAsteroids(line);
            phase = 0;
            score += 1;
        }
    }
    return 0;
}

int main(void)
{
    int selectedLanguage = 2;

    int playerNumber = 3;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Coop Entreprise");
    gameLoop(window, selectedLanguage, playerNumber);


}
