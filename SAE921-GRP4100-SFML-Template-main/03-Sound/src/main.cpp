

#include <iostream>

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Game");

    // Musique
    bool playPauseMusic = false;
    float volume = 50;

    sf::Music music;
    if (!music.openFromFile("data/sounds/music.wav"))
        return -1;
    music.setLoop(true);


    // Sound FX
    sf::SoundBuffer soundFx1;
    sf::SoundBuffer soundFx2;
    sf::Sound sound;

    if (!soundFx1.loadFromFile("data/sounds/soundFx_Laser.wav"))
        return -1;
    if (!soundFx2.loadFromFile("data/sounds/soundFx_Ring.wav"))
        return -1;

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    while (window.isOpen())
    {

        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;

        while (window.pollEvent(event))
        {

            volume = music.getVolume();

            switch (event.type)
            {

                // évènement "fermeture demandée" : on ferme la fenêtre
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:

                // Test de la valeur de la touche
                std::cout << "Key pressed : " << event.key.code << std::endl;
                switch (event.key.code)
                {
                case sf::Keyboard::Up:

                    volume += 10;
                    if (volume >= 100)
                        volume = 100;

                    std::cout << "Volume up ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ " << volume << std::endl;
                    break;

                case sf::Keyboard::Down:

                    volume -= 10;
                    if (volume <= 0)
                        volume = 0;
                    music.setVolume(volume);

                    std::cout << "Volume down vvvvvvvvvvvvvvvvvvvvvvvvvvv " << volume << std::endl;
                    break;

                case sf::Keyboard::Space:
                    std::cout << "PLAY / PAUSE !!!!!!!!!!!!!!!!!!!" << std::endl;
                    if (music.getStatus() != sf::Music::Status::Playing) {
                        music.play();
                    }
                    else {
                        music.pause();
                    }
                    std::cout << "Is playing ??? " << music.getStatus();
                    break;

                case sf::Keyboard::X:
                    if (event.key.shift) {
                        std::cout << "Tiouuuuu ***************************" << std::endl;
                        sound.setBuffer(soundFx1);
                        sound.play();
                    }
                    else {
                        std::cout << "Driiing ***************************" << std::endl;
                        sound.setBuffer(soundFx2);
                    }

                    sound.play();
                    break;

                default:
                    break;

                }

            default:
                break;
            }

        }

        // Graphical Region
        window.clear(sf::Color::Black);

        music.setVolume(volume);
        sound.setVolume(volume);

        // Window Display
        window.display();

    }

}
