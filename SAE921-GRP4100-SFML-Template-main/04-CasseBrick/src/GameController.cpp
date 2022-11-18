#include "GameController.h"

void GameController::SetupBricks() {
    int posx = 50;
    int posy = 100;

    while (posx < 500) {
        bricks.emplace_back(posx, posy);
        posx += 100;
    }

    posx = 150;
    posy = 150;
    while (posx < 500) {
        bricks.emplace_back(posx, posy);
        posx += 200;
    }

    bricks.emplace_back(250, 200);


}

void GameController::Init() {

    sf::RenderWindow window(sf::VideoMode(600, 600), "Casse-briques");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::Music music;
    if (!music.openFromFile("data/CasseBrick.ogg")) {
        std::cout << "SoundEffect failed to load" << std::endl;
    }
    music.setLoop(true);

    SetupBricks();
    music.play();


    Update(window);
}

void GameController::Update(sf::RenderWindow& window) {
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            switch (event.type)
            {

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Space:
                    ball.Launch();
                    break;

                case sf::Keyboard::Left:
                    bar.MoveLeft();
                    break;

                case sf::Keyboard::Right:
                    bar.MoveRight();
                    break;
                }
                break;


            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }

        }

        ball.Move();
        ball.BallOutofRange();
        ball.IsCollidingBar(bar);

        // Graphical Region
        window.clear(sf::Color(17, 25, 41));
        window.draw(bar);
        window.draw(ball);

        int brickVectorPointeur = 0;
        for (auto& brick : bricks) {
            if (ball.IsCollidingBrick(brick)) {
                brick.brickShape.setSize(sf::Vector2f(0, 0));
            }
            brickVectorPointeur++;
            window.draw(brick);
        }


        // Window Display
        window.display();

    }
}

GameController::GameController() {

}



