#include <vector>

#include "globals.hpp"

class Board {
private: 
    std::vector<std::vector<bool>> board; 
public:
    Board();
    void updateBoard();
};