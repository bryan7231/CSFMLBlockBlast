#include "tetromino.hpp"
#include <iostream>

// Create a tetromino with a shape defined by enum TetrominoShape a Color c, and a position vector. 
Tetromino::Tetromino(TetrominoShape s, Color c, sf::Vector2f position): Tetromino(tetrominoes[s], c, position) {}

// Create a tetromino with a shape defined by 5x5 vector layout, a Color c, and a position vector. 
Tetromino::Tetromino(std::vector<std::vector<bool>> layout, Color c, sf::Vector2f position): layout(layout), color(c), position(position), clicked(false), initialPos(position), initialOffset({0, 0}), validPos(false), id(currId) {
    currId++; 
    this->visible = true; 

    // Add blocks with correct position
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};

                this->blocks.push_back(b); 
            }
        }
    }
}

// Sets the position of the tetromino, updating position of all blocks, as well as hitbox
void Tetromino::setPosition(sf::Vector2f pos) {
    this->position = pos; 
    initialPos = pos; 

    // Add blocks with correct position
    blocks.clear(); 
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};

                this->blocks.push_back(b); 
            }
        }
    }
}

// Gets the layout of the tetromino, in terms of a 5x5 matrix, where true is a location of a block
std::vector<std::vector<bool>>& Tetromino::getLayout() {
    return this->layout; 
}

bool Tetromino::checkCollisions(sf::Vector2f pos) {
    return pos.x >= position.x && pos.x <= hitbox.x && pos.y >= position.y && pos.y <= hitbox.y; 
}   

// Returns the size of the tetromino, in global coordinates; the smallest size that can fit all blocks in the tetromino
sf::Vector2f Tetromino::getSize() {
    return (hitbox - position)/BLOCK_SIZE; 
}

 // Shifts the layout of the tetromino, moving it to the top left corner of the matrix. Ensures that position of each tetromino is correct. 
void Tetromino::shiftLayout() {
    sf::Vector2i tL = {50, 50}; 

    // Fetch minimum r and c of the layout
    for (int r = 0; r < layout.size(); r++) {
        for (int c = 0; c < layout[r].size(); c++) {
            if (layout[r][c]) {
                tL = {std::min(tL.x, r), std::min(tL.y, c)}; 
            }
        }
    }

    if (tL == sf::Vector2i(50, 50)) return; 

    // Make a new layout where everything is shifted by that amount. 
    std::vector<std::vector<bool>> newLayout(layout.size(), std::vector<bool>(layout[0].size()));
    for (int r = 0; r < layout.size(); r++) {
        for (int c = 0; c < layout[r].size(); c++) {
            if (layout[r][c]) {
                if (r < tL.x || c < tL.y) {
                    std::cout << "Layout shifting failed, wrong mins. " << "\n";
                    return; 
                }
                newLayout[r-tL.x][c-tL.y] = true; 
            }
        }
    }
    
    layout = newLayout; 
}

// Updates and checks for collisions of tetromino, returns true if tetromino was placed during this frame
bool Tetromino::update(sf::RenderWindow& window, std::vector<std::vector<int>>& board) {
    bool ret = false; 
    // Only update tetromino if it is visible
    if (visible) {
        float y_off = 0.0; 
        float x_off = 0.0; 
        // Fetch mouse position to check if tetromino is being clicked on 
        sf::Vector2f mousePos = mouseToGlobalCoords(window, sf::Mouse::getPosition()); 

        // If block is being dragged and no other blocks are being dragged 
        if (mouseHeld && (checkCollisions(mousePos) || this->clicked) && (dragged == -1 || dragged == id)) {
            y_off = -15.0f;

            if (!clicked) initialOffset = mousePos - position; 
            this->position = mousePos - initialOffset;
            clicked = true; 
            dragged = id; 
        }

        // If mouse is let go during this frame
        if (!mouseHeld) {
            if (validPos && clicked) { // If valid position and mouse was held last frame, then drop the block there 
                validPos = false;
                // std::cout << "Valid Position to Place!\n"; 
                ret = true; 
                visible = false; 
                y_off = -15.0f; 
            } else if (!validPos && clicked) { // Otherwise, reset it back to original spot, so that block cannot be placed
                this->position = initialPos; 
            } 
            this->clicked = false;  
            dragged = -1; 
        }

        hitbox = {0.f, 0.f};
        // If the block is being dragged around, check if its a valid position where it currently is. 
        if (clicked) validPos = true; 
        for (Block& b : this->blocks) { 
            sf::Vector2i oldGridCoords = toGridCoords(b.getPosition()); 

            // Remove old highlight blocks 
            if (withinBoard(oldGridCoords) && board[oldGridCoords.y][oldGridCoords.x] == -2) {
                board[oldGridCoords.y][oldGridCoords.x] = -1; 
            }

            // Make block transparent when dragged around. 
            if (clicked) {
                sf::Color c = b.shape().getFillColor();
                c.a = 128; 
                sf::Color o = b.shape().getOutlineColor();
                o.a = 128; 
                b.shape().setFillColor(c); 
                b.shape().setOutlineColor(o); 
            } else {
                sf::Color c = b.shape().getFillColor();
                c.a = 255; 
                sf::Color o = b.shape().getOutlineColor();
                o.a = 255; 
                b.shape().setFillColor(c); 
                b.shape().setOutlineColor(o); 
            }

            // New position is position + blockSize * block position + offset
            b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*b.getTetroPos().x + x_off, BLOCK_SIZE*b.getTetroPos().y + y_off});

            sf::Vector2i newGridCoords = toGridCoords(b.getPosition());
            // std::cout << b.getPosition().x << ", " << b.getPosition().y << "\n";
            // std::cout << newGridCoords.x << ", " << newGridCoords.y << "\n";
            // std::cout << "---------------------------------------------------\n"; 

            // Only if the position is not already taken by another block and within the board, draw highlight squares there
            if (withinBoard(newGridCoords) && board[newGridCoords.y][newGridCoords.x] == -1) board[newGridCoords.y][newGridCoords.x] = -2; 
            else validPos = false; // Not valid because a block could not fit on the board

            // If the block is placed during this frame, then set the position, and change the board to adjust to that.
            if (!visible) {
                b.setPosition(toGlobalCoords(newGridCoords));
                board[newGridCoords.y][newGridCoords.x] = this->color; 
            }
            // Hitbox is the max x and y at this position 
            hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};
        }
    }
    return ret; 
}

// Rotates the tetromino by a multiple of 90 degrees, only valid ones are, (90, 180, 270), shifting layout after
void Tetromino::rotate(int deg) {
    blocks.clear(); 

    if (deg == 90) { // Transpose then reverse rows
        // Transpose 
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = i+1; j < this->layout[i].size(); j++) {
                std::swap(this->layout[i][j], this->layout[j][i]);
            }
        }

        // Reverse rows
        for (int i = 0; i < this->layout.size(); i++) std::reverse(this->layout[i].begin(), this->layout[i].end()); 
    } else if (deg == 180) { // Just reflect over y = x
        // Swapping last indices with first to reflect
        std::vector<std::vector<bool>> newLayout(this->layout.size(), std::vector<bool>(this->layout[0].size(), false));
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = 0; j < this->layout[i].size(); j++) {
                newLayout[this->layout.size()-i-1][this->layout[0].size()-j-1] = this->layout[i][j]; 
            }
        }
        this->layout = newLayout; 
    } else if (deg == 270) { // Transpose then reverse columns
        // Transpose 
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = i+1; j < this->layout[i].size(); j++) {
                std::swap(this->layout[i][j], this->layout[j][i]);
            }
        }
        
        // Reverse columns
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = 0, k = this->layout.size()-1; j < k; j++, k--) {
                std::swap(this->layout[j][i], this->layout[k][i]); 
            }
        }
    }

    shiftLayout(); 

    hitbox = {0.f, 0.f};
    // Re-add the blocks, updating hitbox and location
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};

                this->blocks.push_back(b); 
            }
        }
    }
}

// Flips the layout of a tetromino horizontally, and shifts layout. 
void Tetromino::hFlip() {
    blocks.clear(); 
    // Reverse columns to flip horizontally
    for (int i = 0; i < this->layout.size(); i++) std::reverse(this->layout[i].begin(), this->layout[i].end()); 

    shiftLayout(); 

    hitbox = {0.f, 0.f};
    // Re-add the blocks
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};

                this->blocks.push_back(b); 
            }
        }
    }
}

// Flips the layout of a tetromino vertically, and shifts layout. 
void Tetromino::vFlip() {
    // Reverse rows to flip vertically
    blocks.clear(); 
    for (int j = 0; j < this->layout[0].size(); j++) {
        for (int i = 0; i < this->layout.size() / 2; i++) {
            swap(this->layout[i][j], this->layout[this->layout.size()-i-1][j]);
        }
    }

    shiftLayout(); 

    hitbox = {0.f, 0.f};
    // Re-add the blocks
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};

                this->blocks.push_back(b); 
            }
        }
    }
}

// Draws the tetromino to a window
void Tetromino::draw(sf::RenderWindow& w) {
    // Only draw if its visible
    if (this->visible) {
        for (Block b : this->blocks) {
            w.draw(b.shape()); 
        }
    }
}

// Draws the tetromino to a texture
void Tetromino::draw(sf::RenderTexture& w) {
    // Only draw if its visible 
    if (this->visible) {
        for (Block b : this->blocks) {
            w.draw(b.shape()); 
        }
    }
}

// Toggles the visibility of the tetromino
void Tetromino::toggleVisibility() {
    this->visible = !this->visible; 
}

// Returns true if the tetromino is visible, false otherwise 
bool Tetromino::isVisible() {
    return this->visible; 
}