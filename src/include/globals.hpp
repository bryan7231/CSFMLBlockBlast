#pragma once

#include <SFML/Graphics.hpp>

extern bool mouseHeld; 

#define WINDOW_WIDTH 1920u
#define WINDOW_HEIGHT 1080u

#define BACKGROUND_COLOR sf::Color(43, 43, 43)
#define GRID_COLOR sf::Color(60, 60, 60)

#define BLOCK_SIZE 75.f
#define OUTLINE_WIDTH 2.5f

#define BOARD_SIZE 8

#define MOUSE_X_OFFSET -8.f
#define MOUSE_Y_OFFSET -32.f

#define X_OFFSET (float)WINDOW_WIDTH / 2.f - ((BLOCK_SIZE*BOARD_SIZE)/2.f)
#define Y_OFFSET 150.f

enum Color {RED, ORANGE, YELLOW, GREEN, TEAL, BLUE, PURPLE};

enum TetrominoShape {Line2, Line3, Line4, Line5, Square2, Square3, L2, L2x3, L3, T2, T3, Rectangle, S};

extern std::vector<std::vector<std::vector<bool>>> tetrominoes; 

sf::Vector2i toGridCoords(sf::Vector2f globalCoords); 

sf::Vector2f toGlobalCoords(sf::Vector2i gridCoords); 

sf::Vector2f mouseToGlobalCoords (sf::RenderWindow &window, sf::Vector2i mouse); 

bool withinBoard(sf::Vector2i gridCoords); 