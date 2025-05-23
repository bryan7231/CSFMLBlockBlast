#include "include/board.hpp"
#include <iostream>
#include <math.h>

Board::Board() {
    board.assign(BOARD_SIZE, std::vector<int>(BOARD_SIZE, -1));
    grid.assign(BOARD_SIZE, std::vector<sf::RectangleShape>(BOARD_SIZE));
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            grid[i][j].setSize({BLOCK_SIZE, BLOCK_SIZE});

            grid[i][j].setFillColor(BACKGROUND_COLOR);
    
            grid[i][j].setOutlineThickness(-OUTLINE_WIDTH);
            grid[i][j].setOutlineColor(GRID_COLOR);

            grid[i][j].setPosition({X_OFFSET + BLOCK_SIZE*j, Y_OFFSET + BLOCK_SIZE*i});
        }
    }

    outline.setSize({BOARD_SIZE*BLOCK_SIZE, BOARD_SIZE*BLOCK_SIZE});
    outline.setFillColor(BACKGROUND_COLOR);
    outline.setOutlineColor(sf::Color(255, 255, 255));
    outline.setOutlineThickness(OUTLINE_WIDTH*2);

    outline.setPosition({X_OFFSET, Y_OFFSET});
}

// Updates the board based on the board vector, clears completed rows and updates score
void Board::updateBoard() {

    std::vector<int> completedRows, completedCols; 
    // Check for rows 
    for (int r = 0; r < board.size(); r++) {
        bool complete = true;
        for (int c = 0; c < board.size(); c++) {
            if (board[r][c] < 0) complete = false; 
        } 
        if (complete) completedRows.push_back(r); 
    }
    // Check for columns
    for (int c = 0; c < board.size(); c++) {
        bool complete = true; 
        for (int r = 0; r < board.size(); r++) {
            if (board[r][c] < 0) complete = false;
        }
        if (complete) completedCols.push_back(c); 
    }
    
    const float baseScore = 10; 

    // 1. Base score * the number of rows and columns removed
    // 2. Exponential growth based on number of rows
    // 3. Multiplier for getting both rows and columns 
    if (completedRows.size() || completedCols.size()) {
        int totalClears = completedRows.size() + completedCols.size(); 
        float addedScore = baseScore * totalClears * powf(1.5f, totalClears); 
        addedScore += addedScore * completedRows.size() * completedCols.size(); 
        score += addedScore; 
        // std::cout << "Score: " << score << "\n"; 
    }

    // Remove completed rows and columns
    for (int r : completedRows) {
        for (int c = 0; c < board.size(); c++) {
            board[r][c] = -1; 
        }
    }

    for (int c : completedCols) {
        for (int r = 0; r < board.size(); r++) {
            board[r][c] = -1;
        }
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == -1) { // Empty cell
                grid[i][j].setFillColor(BACKGROUND_COLOR);
                grid[i][j].setOutlineColor(BACKGROUND_COLOR);
            } else if (board[i][j] == -2) { // Highlighted cell
                grid[i][j].setFillColor(HIGHLIGHT_COLOR);
                grid[i][j].setOutlineColor(BACKGROUND_COLOR);
            } else {
                grid[i][j].setFillColor(Colors[board[i][j]]);
                grid[i][j].setOutlineColor(BACKGROUND_COLOR);
            }
            // std::cout << board[i][j] << " ";
        }
        // std::cout << "\n";
    }
    // std::cout << "---------------------------------------------\n";
}

// Draws the board to a window
void Board::draw(sf::RenderWindow& window) {
    window.draw(outline);

    for (auto& rects : grid) {
        for (auto& rect : rects) {
            window.draw(rect);
        }
    }
}

// Draws the board to a texture
void Board::draw(sf::RenderTexture& window) {
    window.draw(outline);

    for (auto& rects : grid) {
        for (auto& rect : rects) {
            window.draw(rect);
        }
    }
}

// Clears the board, setting all tiles to empty
void Board::clear() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j] = -1; 
        }
    }
}
