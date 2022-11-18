

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"


int main()
{
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Window");

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);


    // Define a Shape
    // https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Shape.php
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(150, 50, 250, 100));
    // define a position
    shape.setOrigin(shape.getRadius() / 2.0f, shape.getRadius() / 2.0f);
    //shape.setPosition(center.x / 2.0f, center.y / 2.0f);

    // Redefine Size
    shape.setRadius(40.0f);


    sf::Texture up;
    sf::Texture down;
    sf::Texture left;
    sf::Texture right;


    //down.loadFromFile("D:/VisualStudio/SAE921-GRP4100-SFML-Template-main/00-WhiteWindow/data/sprites/down.png");       recherche pas depuis le build donc mauvais 
    up.loadFromFile("data/sprites/up.png");
    down.loadFromFile("data/sprites/down.png");
    left.loadFromFile("data/sprites/left.png");
    right.loadFromFile("data/sprites/right.png");



    // Using a sprite
    // https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php
    sf::Sprite spriteLink;
    spriteLink.setTexture(down);
    spriteLink.setOrigin(up.getSize().x / 2.0f, up.getSize().y / 2.0f);
    const auto center = window.getSize();
    spriteLink.setPosition(center.x / 2.0f, center.y / 2.0f);


    while (window.isOpen())
    {
        
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        sf::Vector2f position;
        position = spriteLink.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { //pas un event pour eviter le stop en mouv puisque que event verification a chaque frame 
            std::cout << " up " << std::endl;
            spriteLink.setTexture(down);
            position.y -= 2;
            spriteLink.setPosition(position);
        }
        

        while (window.pollEvent(event))
        {


            switch (event.type)
            {

                // évènement "fermeture demandée" : on ferme la fenêtre
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                std::cout << "Key pressed " << event.key.code << std::endl;

                

                switch (event.key.code)
                {
                /* dans if maintenant pour monter la diff de reaction
                case sf::Keyboard::up:
                case sf::Keyboard::W:
                    std::cout << " up " << std::endl;
                    spriteLink.setTexture(down);                   
                    position.y -= 2;
                    spriteLink.setPosition(position);

                */
                    

                    break;

                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    std::cout << " down " << std::endl;
                    spriteLink.setTexture(up);
                    position.y += 2;
                    spriteLink.setPosition(position);



                    break;

                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    std::cout << " Left " << std::endl;
                    spriteLink.setTexture(left);
                    position.x -= 2;
                    spriteLink.setPosition(position);


                    break;

                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    std::cout << " Right " << std::endl;
                    spriteLink.setTexture(right);
                    position.x += 2;
                    spriteLink.setPosition(position);


                    break;



                default:
                    break;
                }
                break;

            default:
                break;
            }

        }
        
       

        // Graphical Region
        window.clear(sf::Color::Black);

        window.draw(spriteLink);


        /*
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        window.draw(shape);
        shape.setPosition(pos.x, pos.y);
        */


        //window.draw(something to draw);

        // Window Display
        window.display();

    }



}
