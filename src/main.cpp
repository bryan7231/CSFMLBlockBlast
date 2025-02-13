#include <SFML/Graphics.hpp>

#include "include/block.hpp"
#include "include/globals.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Block Blast");
    window.setFramerateLimit(144);

    Block b1(Color::TEAL, {0.f, 0.f});
    Block b2(Color::TEAL, {45.f, 0.f});

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
        window.draw(b1.shape());
        window.draw(b2.shape());
        window.display();
    }
}
