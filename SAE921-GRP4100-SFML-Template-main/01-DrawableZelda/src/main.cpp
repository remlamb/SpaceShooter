

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"

#include "Link.h"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Window");

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    Link link;
    


    while (window.isOpen())
    {
        
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        sf::Vector2f position;
        //position = linkSprite.getPosition();
        

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
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    link.Moveup();

                
                    

                    break;

                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    link.Movedown();



                    break;

                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    link.MoveLeft();


                    break;

                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    link.MoveRight();
                    //link.Move(sf::Vector2f(1, 0));


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

        window.draw(link);

        // Window Display
        window.display();

    }



}
