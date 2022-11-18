#include "Enemy.h"
#include "Game.h"
#include "SFMLToBox2D.h"

Enemy::Enemy(b2World& world, float posX, float posY, float direction) : _world(world) {
    enemyHealth = 3;
    movementDirection = direction;
    velocityAsteroideX = 0;

    enemyTexture.loadFromFile("data/Enemy.png");
    enemySprite.setTexture(enemyTexture);
    enemySprite.setOrigin(enemyTexture.getSize().x / 2.0f, enemyTexture.getSize().y / 2.0f);



    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(PixelsToMeters(posX), PixelsToMeters(posY)); //0, -200
    body = _world.CreateBody(&bodyDef);

    // Shape of the physical
    b2PolygonShape enemyBox;
    enemyBox.SetAsBox(PixelsToMeters(enemyTexture.getSize().x *0.5), PixelsToMeters(enemyTexture.getSize().y *0.5));

    // The fixture is what it defines the physic react
    b2FixtureDef enemyFixtureDef;
    enemyFixtureDef.shape = &enemyBox;
    enemyFixtureDef.density = 0.0f;
    enemyFixtureDef.friction = 0.0f;


    ContactEvent* m_userData = new ContactEvent(*this);
    enemyFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    currentHealthBarSize = sf::Vector2f(80, 10);
    enemyHealthBar.setSize(currentHealthBarSize);
    enemyHealthBar.setFillColor(sf::Color(130, 130, 130, 0));
    enemyHealthBar.setOrigin(enemyTexture.getSize().x / 2, enemyTexture.getSize().y / 2);

    body->CreateFixture(&enemyFixtureDef);


}

void Enemy::Move() {
    b2Vec2 position = body->GetPosition();
    body->SetLinearVelocity(b2Vec2(movementDirection * speed,  0));
    position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position); // sf::Vector2f(position.x, -1 * position.y);       // Translate meters to pixels
    enemySprite.setPosition(graphicPosition);        // Set the position of the Graphic object
}

void Enemy::ShootAsteroide(b2World& world) {
    RandomSpawn();
    if (timerBetweenAsteroide.GetMilliseconds() > timeBetweenAsteroide) {        
        if (timerIndestructibleShoot.GetMilliseconds() > timeBetweenIndestuctibleShoot) {
            currentAsteroide.emplace_back(world, randomAsteroideSpawningPos.x, randomAsteroideSpawningPos.y, false, velocityAsteroideX);
            timerIndestructibleShoot.Reset();
        }
        else {
            currentAsteroide.emplace_back(world, randomAsteroideSpawningPos.x, randomAsteroideSpawningPos.y, true, velocityAsteroideX);
        }
        timerBetweenAsteroide.Reset();
    }
}

void Enemy::FindAsteroidetoDestroy() {
    std::erase_if(currentAsteroide, [](Asteroide& a) {return a.isTouched; });
}

void Enemy::Update() {
    Move();
    if (canShoot) {
        ShootAsteroide(_world);
    }
    enemyHealthBar.setPosition(enemySprite.getPosition().x - 20, enemySprite.getPosition().y - 20);
    HideHealthBar();

    DestroyIfOutOfBounds();
}


Enemy::~Enemy() {
    _world.DestroyBody(body);
}

Enemy& Enemy::operator=(const Enemy& other) {
    Enemy enemy(other);
    return enemy;
}

void Enemy::OnHit() {
    enemyHealth -= 1;
    enemyHealthBar.setFillColor(sf::Color(130, 130, 130));
    timerHealthBarShown.Reset();
    currentHealthBarSize -= sf::Vector2f(27, 0);
    if (currentHealthBarSize.x <= 0) {
        currentHealthBarSize.x = 0;
    }
    enemyHealthBar.setSize(currentHealthBarSize);
    if (enemyHealth <= 0) {
        isTouched = true;
    }
}

void Enemy::HideHealthBar() {
    if (timerHealthBarShown.GetMilliseconds() > timeHealthBarShown) {
        enemyHealthBar.setFillColor(sf::Color(130, 130, 130, 0));  
    }
}

void Enemy::SetupUpAndReadSFX(sf::SoundBuffer& neededBuffer) {

}

void Enemy::RandomSpawn() {
    int randomNumber = rand() % 3;
    if (randomNumber == 0) {
        randomAsteroideSpawningPos = b2Vec2(body->GetPosition().x * 100, body->GetPosition().y * 100 - 60);
        velocityAsteroideX = 0;
    }
    else if (randomNumber == 1) {
        randomAsteroideSpawningPos = b2Vec2(body->GetPosition().x * 100 + 60, body->GetPosition().y * 100 - 60);
        velocityAsteroideX = 2;
    }
    else{
        randomAsteroideSpawningPos = b2Vec2(body->GetPosition().x * 100 - 60, body->GetPosition().y * 100 - 60);
        velocityAsteroideX = -2;
    }
}

void Enemy::DestroyIfOutOfBounds() {
    b2Vec2 position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position);

    if (graphicPosition.x < -100 || graphicPosition.x > 1380 ) {
        isTouched = true;
    }

}