#include "Bullet.h"
#include "SFMLToBox2D.h"

Bullet::Bullet(float posX, float posY, b2World& world) : _world(world){
    
    laserTexture.loadFromFile("data/LaserBlue.png");
    laserSprite.setTexture(laserTexture);
    laserSprite.setOrigin(laserTexture.getSize().x / 2.0f, laserTexture.getSize().y / 2.0f);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;// b2_kinematicBody;
    bodyDef.position.Set(PixelsToMeters(posX), PixelsToMeters(posY));
    body = world.CreateBody(&bodyDef);

    // Shape of the physical
    b2PolygonShape bulletBox;
    bulletBox.SetAsBox(PixelsToMeters(laserTexture.getSize().x *0.5), PixelsToMeters(laserTexture.getSize().y *0.5 ));

    // The fixture is what it defines the physic react
    b2FixtureDef bulletFixtureDef;
    bulletFixtureDef.shape = &bulletBox;
    bulletFixtureDef.density = 0.0f;
    bulletFixtureDef.friction = 0.0f;

    ContactEvent* m_userData = new ContactEvent(*this);
    bulletFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);


    body->CreateFixture(&bulletFixtureDef);

    Update();
}

void Bullet::Update() {
    body->SetLinearVelocity(b2Vec2(0, 20));
    b2Vec2 position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position) ;
    laserSprite.setPosition(graphicPosition);
}

Bullet::~Bullet() {
    _world.DestroyBody(body);
}

Bullet& Bullet::operator=(const Bullet& other) {
    Bullet bullet(other);
    return bullet;
}
