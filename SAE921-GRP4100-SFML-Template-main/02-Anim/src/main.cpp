

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Game");
    
    std::vector<sf::Texture> textures;
    int idxTextures = 0;
    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    // Period = nb Miliseconds / Frame Rate
    constexpr float intPeriod = (1000.0f / 30.0f);

    // Animation
    // Load every textures --------------------------------------------------------------------------------------------------
    for (size_t i = 1; i <= 16; i++)
    {
        sf::Texture newTexture;
        std::stringstream path;
        path << "data/sprites/Run" << std::setw(2) << std::setfill('0') << i << ".png";
        std::cout << "Path=" << path.str() << std::endl;

        newTexture.loadFromFile(path.str());
        textures.push_back(newTexture);
             
    }

    // We need a sprite to display the texture
    sf::Sprite sprite;

    sprite.setTexture(textures[idxTextures]);
    sprite.setOrigin(textures[idxTextures].getSize().x / 2.0f, textures[idxTextures].getSize().y / 2.0f);
    sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    // Time management
    sf::Clock clock;
    sf::Time totalElapsed;

    while (window.isOpen())
    {
        
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;

        while (window.pollEvent(event))
        {

            switch (event.type)
            {

                // évènement "fermeture demandée" : on ferme la fenêtre
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }

        }

        // Graphical Region
        window.clear(sf::Color::Black);


        // Every 100ms, we load a new texture
        sf::Time elapsed = clock.restart();
        totalElapsed = totalElapsed + elapsed;
        std::cout << "Counting ..... " << totalElapsed.asSeconds() << std::endl;


        if (totalElapsed.asMilliseconds() >= intPeriod) {
            // Picking next texture
            idxTextures++;
            // Reset time
            totalElapsed = totalElapsed.Zero;
            // Switch to first frame
            if (idxTextures >= textures.size())
                idxTextures = 5;
            std::cout << "New texture index : " << idxTextures << std::endl;
        }

        // Load a texture
        sprite.setTexture(textures[idxTextures]);

        // Display the texture
        window.draw(sprite);

        // Window Display
        window.display();

    }

}
