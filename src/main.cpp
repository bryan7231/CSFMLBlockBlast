#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/tetromino.hpp"
#include "include/board.hpp"
#include "include/globals.hpp"
#include "include/bag.hpp"
#include "include/scoreboard.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Block Blast");
    window.setFramerateLimit(144);
    sf::RenderTexture sceneTexture, blurTexture;
    if (!sceneTexture.resize({WINDOW_WIDTH, WINDOW_HEIGHT})) {
        std::cout << "Main scene could not be resized." << "\n";
    }
    if (!blurTexture.resize({WINDOW_WIDTH, WINDOW_HEIGHT})) {
        std::cout << "Blur texture could not be resized." << "\n"; 
    }

    sf::Shader blurShaderH, blurShaderV;
    if (!blurShaderH.loadFromFile("../shaders/blur_horizontal.frag", sf::Shader::Type::Fragment)) {
        std::cout << "Horizontal shader did not load." << "\n"; 
    }
    
    if (!blurShaderV.loadFromFile("../shaders/blur_vertical.frag", sf::Shader::Type::Fragment)) {
        std::cout << "Vertical shader did not laod." << "\n";
    }

    sf::Sprite sprite(sceneTexture.getTexture());

    Board board;

    Bag bag(3); 

    Scoreboard s("Nunito-SemiBold.ttf"); 

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            } 
            if (event->is<sf::Event::MouseButtonPressed>()) 
            {
                // std::cout << sf::Mouse::getPosition().x - window.getPosition().x << ", " << sf::Mouse::getPosition().y - window.getPosition().y << "\n";
                mouseHeld = true; 
            }
            if (event->is<sf::Event::MouseButtonReleased>()) 
            {
                mouseHeld = false; 
            }
            
            if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                board.clear(); 
                bag.reset(); 
                s.reset();

                gameOver = false;
                score = 0.0f; 
            }
        }

        if (gameOver) {
            blurShaderH.setUniform("texture", sceneTexture.getTexture());
            blurShaderH.setUniform("radius", 5.f);
            blurShaderH.setUniform("resolution", sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

            sprite.setTexture(sceneTexture.getTexture());
            blurTexture.clear(BACKGROUND_COLOR);
            blurTexture.draw(sprite, &blurShaderH); 
            blurTexture.display(); 

            blurShaderV.setUniform("texture", blurTexture.getTexture());
            blurShaderV.setUniform("radius", 5.f);
            blurShaderV.setUniform("resolution", sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

            sprite.setTexture(blurTexture.getTexture()); 

            window.clear(BACKGROUND_COLOR);
            window.draw(sprite, &blurShaderV);

            s.draw(window); 

            window.display(); 

            continue; 
        }

        board.updateBoard();

        bag.update(window, board.board); 

        s.update(); 

        sceneTexture.clear(BACKGROUND_COLOR);
        
        board.draw(sceneTexture);

        bag.draw(sceneTexture);

        s.draw(sceneTexture); 

        sceneTexture.display();
        
        sprite.setTexture(sceneTexture.getTexture()); 

        window.clear(BACKGROUND_COLOR);

        window.draw(sprite); 

        window.display();
    }
}
