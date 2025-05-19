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

    // Random generator
    std::random_device seed; 
    std::mt19937 gen;
public: 
    // Sets the position of the bag and its bounding box
    void setPosition(sf::Vector2f position); 

    // Gets the position (top left) of the bag
    sf::Vector2f getPosition(); 

    // Inserts a tetromino into the bag, returns true if insertion was successful, false if it was not (bag is full)
    bool insertTetromino(Tetromino t); 

    // Checks if a given tetromino has a valid position within the board. 
    bool hasValidPos(Tetromino t, std::vector<std::vector<int>>& board);

    // Update function for the bag
    void update(sf::RenderWindow& r, std::vector<std::vector<int>>& board);

    // Draws the bag to the screen, including tetrominos
    void draw(sf::RenderWindow& w);

    // Draws the bag to a texture, including tetrominos
    void draw(sf::RenderTexture& w);

    // Refills the bag up to max capacity, generates random tetrominos with different rotations + color
    void refillBag();

    // Resets the bag, clears it and refills it
    void reset(); 

    Bag(int capacity);

    Bag(sf::Vector2f position, int capacity); 
};
