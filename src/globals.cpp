#include "../include/globals.hpp"

bool mouseHeld = false; 

std::vector<std::vector<std::vector<bool>>> tetrominoes = 
{
    { // Line 2
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // Line 3
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // Line 4
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // Line 5
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // Square 2x2
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // Square 3x3
        {1, 1, 1, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }, 
    { // L 2x2
        {0, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }, 
    { // L 2x3
        {0, 0, 1, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // L 3x3
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }, 
    { // T 2x3
        {0, 1, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // T 3x3
        {1, 1, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // Rectangle 2x3
        {1, 1, 1, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    { // S 
        {0, 1, 1, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }
};

sf::Vector2i toGridCoords(sf::Vector2f globalCoords) {
    return {(globalCoords.x - X_OFFSET)/ (int) BLOCK_SIZE, (globalCoords.y - Y_OFFSET)/ (int) BLOCK_SIZE};
}

sf::Vector2f toGlobalCoords(sf::Vector2i gridCoords) {
    return {(float)gridCoords.x * BLOCK_SIZE + X_OFFSET, (float)gridCoords.y * BLOCK_SIZE + Y_OFFSET};
}

sf::Vector2f mouseToGlobalCoords(sf::RenderWindow& window, sf::Vector2i mouse) {
    return {
        sf::Mouse::getPosition().x - window.getPosition().x + MOUSE_X_OFFSET, 
        sf::Mouse::getPosition().y - window.getPosition().y + MOUSE_Y_OFFSET  
    };
}

bool withinBoard(sf::Vector2i gridCoords) {
    return gridCoords.x >= 0 && gridCoords.x <= BOARD_SIZE && gridCoords.y >= 0 && gridCoords.y <= BOARD_SIZE; 
}
