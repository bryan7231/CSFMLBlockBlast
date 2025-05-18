#include "include/bag.hpp"
#include <iostream> 

void Bag::setPosition(sf::Vector2f position) {
    this->position = position; 
    boundingBox.setPosition(position); 
}

sf::Vector2f Bag::getPosition() {
    return this->position; 
} 

bool Bag::insertTetromino(Tetromino t) {
    if (tetros.size() == capacity) return false; 
    tetros.push_back(t);
    return true; 
} 

void Bag::refillBag() {
    typedef std::uniform_int_distribution<> randInt; 

    int totalBlockHeight = 0; 

    for (int i = 0; i < capacity; i++) {
        // Determine shape and color
        TetrominoShape t = (TetrominoShape)randInt(0, 12)(gen);
        Color c = (Color)randInt(0, 6)(gen);

        Tetromino newT(t, c, {position.x, position.y });

        // // Horizontal and vertical flip 
        int p = randInt(0, 1)(gen); 
        if (p == 1) newT.hFlip();

        p = randInt(0, 1)(gen); 
        if (p == 1) newT.vFlip();

        // Rotation
        p = randInt(0, 3)(gen);
        switch (p) {
            case 1: 
                newT.rotate(90);
                break;
            case 2:
                newT.rotate(180);
                break;
            case 3: 
                newT.rotate(270);
                break;
            default:
                break; 
        }
        
        totalBlockHeight += newT.getSize().y; 

        // std::cout << "Size of #" << i << ": (" << newT.getSize().x << ", " << newT.getSize().y << ")" << "\n"; 

        tetros.push_back(newT);
    }

    float spacing = (boundingBox.getSize().y - totalBlockHeight*BLOCK_SIZE) / capacity;  
    float startY = position.y + spacing/2.f; 
    for (int i = 0; i < capacity; i++) {
        tetros[i].setPosition({
            position.x + boundingBox.getSize().x / 2.f - tetros[i].getSize().x * BLOCK_SIZE / 2.f,
            startY
        });
        startY += tetros[i].getSize().y * BLOCK_SIZE + spacing; 
    }
}

void Bag::reset() {
    tetros.clear();

    refillBag(); 
}

bool Bag::hasValidPos(Tetromino t, std::vector<std::vector<int>>& board) {
    sf::Vector2i size = {(int)t.getSize().x, (int)t.getSize().y}; 

    for (int i = 0; i < board.size() - size.y + 1; i++) {
        for (int j = 0; j < board[i].size() - size.x + 1; j++) {
            bool isValid = true; 
            for (int r = 0; r < size.y; r++) {
                for (int c = 0; c < size.x; c++) {
                    if (t.getLayout()[r][c] && board[i+r][j+c] >= 0)  {
                        isValid = false; 
                        break; 
                    }
                }
                if (!isValid) break; 
            }
            if (isValid) return true; 
        }
    }
    return false; 
}

void Bag::update(sf::RenderWindow& r, std::vector<std::vector<int>>& board) {
    if (tetros.empty()) {
        refillBag(); 
        return; 
    }

    bool placedBlock = false; 
    // Erase invisible blocks and update blocks
    for (int i = tetros.size()-1; i >= 0; i--) {
        if (!tetros[i].isVisible()) {
            tetros.erase(tetros.begin()+i);
        } else {
            placedBlock |= tetros[i].update(r, board); 
        }
    }   

    // Check for game over
    if (!tetros.empty() && !placedBlock) {
        bool validPos = false; 
        for (int i = 0; i < tetros.size(); i++) {
            if (hasValidPos(tetros[i], board)) {
                validPos = true; break;
            }
        }
        gameOver = !validPos; 
    }
}

void Bag::draw(sf::RenderWindow& r) {
    r.draw(boundingBox); 
    for (Tetromino& t : tetros) {
        t.draw(r);
    }
}


void Bag::draw(sf::RenderTexture& r) {
    r.draw(boundingBox); 
    for (Tetromino& t : tetros) {
        t.draw(r);
    }
}

Bag::Bag(int capacity): Bag({(X_OFFSET)/2.f - (BLOCK_SIZE*3), BLOCK_SIZE/2.f}, capacity) {}

Bag::Bag(sf::Vector2f position, int capacity): position(position), capacity(capacity) {
    gen.seed(seed());

    boundingBox.setPosition(position); 
    boundingBox.setFillColor(BACKGROUND_COLOR); 
    boundingBox.setOutlineColor(BAG_COLOR); 
    boundingBox.setOutlineThickness(OUTLINE_WIDTH*3);

    boundingBox.setSize({BLOCK_SIZE*6, WINDOW_HEIGHT-BLOCK_SIZE}); 

}