#pragma once

#include <random> 
#include <SFML/Graphics.hpp>

#include "globals.hpp"
#include "tetromino.hpp"

class Bag {
private:
    sf::RectangleShape boundingBox; 
    std::vector<Tetromino> tetros; 
    int capacity;
    sf::Vector2f position; 

    std::random_device seed; 
    std::mt19937 gen;
public: 
    void setPosition(sf::Vector2f position); 
    sf::Vector2f getPosition(); 

    bool insertTetromino(Tetromino t); 
    bool hasValidPos(Tetromino t, std::vector<std::vector<int>>& board);

    void update(sf::RenderWindow& r, std::vector<std::vector<int>>& board);
    void draw(sf::RenderWindow& w);
    void draw(sf::RenderTexture& w);

    void refillBag();
    void reset(); 

    Bag(int capacity);

    Bag(sf::Vector2f position, int capacity); 
};
