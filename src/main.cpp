#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/tetromino.hpp"
#include "include/board.hpp"
#include "include/globals.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Block Blast");
    window.setFramerateLimit(144);

    Board board;

    // Block b1(Color::TEAL, {0.f, 0.f});
    Block b2(Color::TEAL, {BLOCK_SIZE, 0.f});

    Tetromino line(TetrominoShape::Rectangle, Color::TEAL, {100.0f, 200.0f}); 

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(BACKGROUND_COLOR);
        window.draw(board.outline);

        line.draw(window);

        window.display();
    }
}
