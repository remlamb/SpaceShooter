#include "Game.h"

Game::Game() : _gravity(0, 0), _world(_gravity), player(_world, this->_window), _contactListener(*this) {
    
    isMainMenuLaunch = false;
    onStart = true;
    timeStep = 1.0f / 60.0f;
    backgroundTexture.loadFromFile("data/Background.jpg");
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("data/Font/kenvector_future.ttf"))
    {
        std::cout << "Failed to load font";
    }

    if (!sfxAmbiantSound.loadFromFile("data/Sound/ambiantSound.ogg")) {
        std::cout << "SoundEffect failed to load" << std::endl;
    }
    if (!sfxEndSound.loadFromFile("data/Sound/endSound.ogg")) {
        std::cout << "SoundEffect failed to load" << std::endl;
    }

    score = 0;
    isPaused = false;
    isEndSoundSet = false;
}


void Game::Init() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4; //use for asteroide (enemy bullet) shape
    _window.create(sf::VideoMode(900, 720), "Space Shooter", 7U, settings);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);

    player.Init();
    InitScore();
    gl.SetUpBordure(_world, _window);   //bordure that destroy projectile 
    _world.SetContactListener(&_contactListener);
}

void Game::Update() {
    srand(time(NULL));  //random seed
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    sound.setBuffer(sfxAmbiantSound);   //set up main soundtrack / adujst sound
    sound.setVolume(20.f);


    while (_window.isOpen())
    {
        if (onStart) {  //launch main menu on start
            MainMenu();
        }
        
        GameUpdate();   //Update Everything in the window
        GamePaused();   //Paused Game 
        OnPlayerDeath();    //Pause and init death Ui
        EscapeScreen(); //if player out of bounds pause + show an alternative end message // Had to be called after PlayerDeath fonction, because it simulate death
        //create physical world with current time step
        _world.Step(timeStep, velocityIterations, positionIterations);
        //Input
        JoystickInput();
        EventAndKeyboardInput();
        //Graphic
        GameRender();
    }
}


void Game::InitScore() {
    scoreText.setFont(font);
    scoreText.setString("Score : ");
    scoreText.setCharacterSize(14);
    scoreText.setFillColor(sf::Color(255, 82, 69));
    scoreText.setPosition(28, 50);
}

void Game::UpdateScore() {
    std::string textScore;
    textScore = "Score : " + std::to_string(score);
    scoreText.setString(textScore);
}  

void Game::RenderScore() {
    _window.draw(scoreText);
}

void Game::InitDeathScreen() {
    deathText.setFont(font);
    deathText.setString("End with Score :  ");
    deathText.setCharacterSize(28);
    deathText.setFillColor(sf::Color(255, 217, 186));

    sf::FloatRect deathtextRect = deathText.getLocalBounds();
    deathText.setOrigin(deathtextRect.left + deathtextRect.width / 2.0f, deathtextRect.top + deathtextRect.height / 2.0f);
    deathText.setPosition(_window.getSize().x / 2, 150);

    std::string endScore;
    endScore = std::to_string(score);
    finalScore.setFont(font);
    finalScore.setString(endScore);
    finalScore.setCharacterSize(50);
    finalScore.setFillColor(sf::Color(255, 82, 69));
    finalScore.setOutlineColor(sf::Color(255, 217, 186));
    finalScore.setOutlineThickness(4);

    sf::FloatRect finalScoretextRect = finalScore.getLocalBounds();
    finalScore.setOrigin(finalScoretextRect.left + finalScoretextRect.width / 2.0f, finalScoretextRect.top + finalScoretextRect.height / 2.0f);
    finalScore.setPosition(_window.getSize().x / 2, 250);


    deathBackground.setSize(sf::Vector2f(800, 600));
    deathBackground.setOrigin(sf::Vector2f(deathBackground.getSize().x/2, deathBackground.getSize().y/2));
    deathBackground.setOutlineColor(sf::Color(255, 217, 186));
    deathBackground.setFillColor(sf::Color(90, 68, 153, 0));
    deathBackground.setOutlineThickness(6);
    deathBackground.setPosition(_window.getSize().x / 2, _window.getSize().y / 2);

    launchTextBtn.setString("Use escape or R2 to leave");
    launchTextBtn.setPosition(_window.getSize().x / 2, _window.getSize().y - 200);
}

void Game::RenderDeathScreen() {
    if (player.playerHealth <= 0) {
        _window.draw(backgroundSprite);
        _window.draw(deathBackground);
        _window.draw(deathText);
        _window.draw(finalScore);
        _window.draw(launchTextBtn);
    }
}

void Game::EscapeScreen() {
    if (player.IsOutOfBounds()) {
        isPaused = true;
        InitDeathScreen();
        player.playerHealth = -1;
        deathText.setString("Don't leave us :( ");
        finalScore.setString(" ");
    }
}

void Game::SetSpawnTimefaster() {
    if (timerBoost.GetMilliseconds() > timeBetweenBoost) {
        if (enemyManager.timeBetweenEnemy >= 1000) {
            enemyManager.timeBetweenEnemy -= 100;
        }
        timerBoost.Reset();
    }
}


void Game::MainMenu() {

    isMainMenuLaunch = true;
    isPaused = true;
    launchText.setFont(font);
    launchText.setString("Space Shooter");
    launchText.setCharacterSize(40);
    launchText.setFillColor(sf::Color(90, 68, 153));
    launchText.setOutlineColor(sf::Color(255, 217, 186));
    launchText.setOutlineThickness(4);

    sf::FloatRect mainTextRect = launchText.getLocalBounds();
    launchText.setOrigin(mainTextRect.left + mainTextRect.width / 2.0f, mainTextRect.top + mainTextRect.height / 2.0f);
    launchText.setPosition(_window.getSize().x / 2, 150);


    launchTextBtn.setFont(font);
    launchTextBtn.setString("'Use Escape or R1 to Lauch'");
    launchTextBtn.setCharacterSize(28);
    launchTextBtn.setFillColor(sf::Color(255, 217, 186));

    sf::FloatRect mainTextBtnRect = launchTextBtn.getLocalBounds();
    launchTextBtn.setOrigin(mainTextBtnRect.left + mainTextBtnRect.width / 2.0f, mainTextBtnRect.top + mainTextBtnRect.height / 2.0f);
    launchTextBtn.setPosition(_window.getSize().x / 2, 450);

    infoText.setFont(font);
    infoText.setString("Use controller or keyboard arrow to move, R1 or espace to shoot \n                  Only playable with controller if one is connected");
    infoText.setCharacterSize(16);
    infoText.setFillColor(sf::Color(255, 217, 186));

    sf::FloatRect infoTextBtnRect = infoText.getLocalBounds();
    infoText.setOrigin(infoTextBtnRect.left + infoTextBtnRect.width / 2.0f, infoTextBtnRect.top + infoTextBtnRect.height / 2.0f);
    infoText.setPosition(_window.getSize().x / 2, _window.getSize().y -100);

    launchMenuBackground.setSize(sf::Vector2f(_window.getSize().x - 50, _window.getSize().y - 50));
    launchMenuBackground.setOrigin(sf::Vector2f(launchMenuBackground.getSize().x / 2, launchMenuBackground.getSize().y / 2));
    launchMenuBackground.setOutlineColor(sf::Color(255, 217, 186));
    launchMenuBackground.setFillColor(sf::Color(158, 154, 144, 0));
    launchMenuBackground.setOutlineThickness(-6);
    launchMenuBackground.setPosition(_window.getSize().x / 2, _window.getSize().y / 2);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Joystick::isButtonPressed(0, 5)) {
        isMainMenuLaunch = false;
        isPaused = false;
        onStart = false;
        sound.play();   //play main sound when game start
    }


}

void Game::RenderMainMenu() {
    if (isMainMenuLaunch) {
        _window.draw(launchMenuBackground);
        _window.draw(launchText);
        _window.draw(launchTextBtn);
        _window.draw(infoText);
    }
}

void Game::GameUpdate() {
    if (!isPaused) {
        timeStep = 1.0f / 60.0f;
        SetSpawnTimefaster();
        player.canShoot = true;
        player.Update();
        UpdateScore();
        enemyManager.AddEnemy(_world);
    }
}

void Game::GamePaused() {
    if (isPaused) {
        //stop player - enemy shooting 
        timeStep = 0.0f;
        for (auto& enemy : enemyManager.currentEnemy) {
            enemy.canShoot = false;
        }
        player.canShoot = false;
    }
}

void Game::OnPlayerDeath() {
    //Pause if player us dead then set up Ui and play death soundtrack
    if (player.playerHealth <= 0) {
        isPaused = true;
        InitDeathScreen();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Joystick::isButtonPressed(0, 7)) { //26
            _window.close();
        }

        if (!isEndSoundSet) {
            sound.setBuffer(sfxEndSound);
            sound.play();
            isEndSoundSet = true;
        }
    }
}

void Game::JoystickInput() {
    if (sf::Joystick::isConnected(0))
    {
        //Button R1
        if (sf::Joystick::isButtonPressed(0, 5)) {
            player.Shooting(_world);
        }

        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

        if (x > 30) {
            player.Move(1, 0);
        }
        else if (x < -30) {
            player.Move(-1, 0);
        }
        else if (y > 30) {
            player.Move(0, 1);
        }
        else if (y < -30) {
            player.Move(0, -1);
        }
        else {
            player.Move(0, 0);
        }
    }
}

void Game::EventAndKeyboardInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        player.Shooting(_world);
    }

    if (!sf::Joystick::isConnected(0)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) { //26
            player.Move(0, 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.Move(0, -1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.Move(1, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.Move(-1, 0);
        }
        else {
            player.Move(0, 0);
        }
    }

    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {

            // évènement "fermeture demandée" : on ferme la fenêtre
        case sf::Event::Closed:
            _window.close();
            break;

        default:
            break;
        }
    }
}

void Game::GameRender() {
    // Graphical Region //This Order is Important Especially for end screen
    _window.clear(sf::Color::Black);
    _window.draw(backgroundSprite);

    if (!isMainMenuLaunch) {
        player.Render();
        RenderScore();
        enemyManager.Render(_window);
    }

    RenderMainMenu();
    RenderDeathScreen();


    // Window Display
    _window.display();
}