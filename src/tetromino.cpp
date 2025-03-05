#include "tetromino.hpp"

// Create a tetromino with a shape defined by enum TetrominoShape a Color c, and a position vector. 
Tetromino::Tetromino(TetrominoShape s, Color c, sf::Vector2f position): Tetromino(tetrominoes[s], c, position) {}


// Create a tetromino with a shape defined by 5x5 vector layout, a Color c, and a position vector. 
Tetromino::Tetromino(std::vector<std::vector<bool>> layout, Color c, sf::Vector2f position): layout(layout), color(c), position(position){
    this->visible = true; 
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                this->blocks.push_back(b); 
            }
        }
    }
}

void Tetromino::update() {
    for (Block& b : this->blocks) {
        b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*b.getTetroPos().x, BLOCK_SIZE*b.getTetroPos().y});
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

    // Re-add the blocks
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

                this->blocks.push_back(b); 
            }
        }
    }
}

// Flips the layout of a tetromino horizontally 
void Tetromino::hFlip() {
    blocks.clear(); 
    for (int i = 0; i < this->layout.size(); i++) std::reverse(this->layout[i].begin(), this->layout[i].end()); 

    // Re-add the blocks
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

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

    // Re-add the blocks
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {
            if (layout[i][j]) {
                Block b(this->color); 

                b.setTetroPos({j, i});
                b.setPosition(this->position + sf::Vector2f{BLOCK_SIZE*j, BLOCK_SIZE*i});

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