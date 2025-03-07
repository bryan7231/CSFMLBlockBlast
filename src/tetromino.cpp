#include "tetromino.hpp"
#include <iostream>

// Create a tetromino with a shape defined by enum TetrominoShape a Color c, and a position vector. 
Tetromino::Tetromino(TetrominoShape s, Color c, sf::Vector2f position): Tetromino(tetrominoes[s], c, position) {}


// Create a tetromino with a shape defined by 5x5 vector layout, a Color c, and a position vector. 
Tetromino::Tetromino(std::vector<std::vector<bool>> layout, Color c, sf::Vector2f position): layout(layout), color(c), position(position), clicked(false), initialOffset({0, 0}) {
    this->visible = true; 
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

bool Tetromino::checkCollisions(sf::Vector2f pos) {
    return pos.x >= position.x && pos.x <= hitbox.x && pos.y >= position.y && pos.y <= hitbox.y; 
}   

void Tetromino::update(sf::RenderWindow& window, std::vector<std::vector<int>> board) {
    if (visible) {
        float y_off = 0.0; 
        float x_off = 0.0; 
        sf::Vector2f mousePos = mouseToGlobalCoords(window, sf::Mouse::getPosition()); 

        if (!mouseHeld) {
            this->clicked = false; 
        }

        if (mouseHeld && (checkCollisions(mousePos) || this->clicked)) {
            y_off = -15.0f;

            if (!clicked) initialOffset = mousePos - position; 
            this->position = mousePos - initialOffset;
            clicked = true; 
        }

        hitbox = {0.f, 0.f};
        for (Block& b : this->blocks) {
            // Erase old highlighted blocks. 
            sf::Vector2i oldGridCoords = toGridCoords(b.getPosition()); 

            if (withinBoard(oldGridCoords)) {
                board[oldGridCoords.x][oldGridCoords.y] = -1; 
            }

            b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*b.getTetroPos().x + x_off, BLOCK_SIZE*b.getTetroPos().y + y_off});

            sf::Vector2i newGridCoords = toGridCoords(b.getPosition());
            if (withinBoard(newGridCoords)) board[oldGridCoords.x][oldGridCoords.y] = -2; 
            hitbox = {std::max(hitbox.x, b.getPosition().x + BLOCK_SIZE), std::max(hitbox.y, b.getPosition().y + BLOCK_SIZE)};
        }
    }
}

void Tetromino::rotate(int deg) {
    blocks.clear(); 

    if (deg == 90) {
        // Transpose 
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = i+1; j < this->layout[i].size(); j++) {
                std::swap(this->layout[i][j], this->layout[j][i]);
            }
        }

        // Reverse rows
        for (int i = 0; i < this->layout.size(); i++) std::reverse(this->layout[i].begin(), this->layout[i].end()); 
    } else if (deg == 180) {
        std::vector<std::vector<bool>> newLayout(this->layout.size(), std::vector<bool>(this->layout[0].size(), false));
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = 0; j < this->layout[i].size(); j++) {
                newLayout[this->layout.size()-i-1][this->layout[0].size()-j-1] = this->layout[i][j]; 
            }
        }
        this->layout = newLayout; 
    } else {
        // Reverse rows
        for (int i = 0; i < this->layout.size(); i++) std::reverse(this->layout[i].begin(), this->layout[i].end());
        
        // Transpose 
        for (int i = 0; i < this->layout.size(); i++) {
            for (int j = i+1; j < this->layout[i].size(); j++) {
                std::swap(this->layout[i][j], this->layout[j][i]);
            }
        }
    }

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

// Flips the layout of a tetromino horizontally 
void Tetromino::hFlip() {
    blocks.clear(); 
    for (int i = 0; i < this->layout.size(); i++) std::reverse(this->layout[i].begin(), this->layout[i].end()); 

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

// Flips the layout of a tetromino vertically. 
void Tetromino::vFlip() {
    blocks.clear(); 
    for (int j = 0; j < this->layout[0].size(); j++) {
        for (int i = 0; i < this->layout.size() / 2; i++) {
            swap(this->layout[i][j], this->layout[this->layout.size()-i-1][this->layout[i].size()-j-1]);
        }
    }

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

void Tetromino::draw(sf::RenderWindow& w) {
    if (this->visible) {
        for (Block b : this->blocks) {
            w.draw(b.shape()); 
        }
    }
}

void Tetromino::toggleVisibility() {
    this->visible = !this->visible; 
}