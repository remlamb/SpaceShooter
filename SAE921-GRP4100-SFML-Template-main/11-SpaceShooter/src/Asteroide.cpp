#include "Asteroide.h"
#include "SFMLToBox2D.h"

Asteroide::Asteroide(b2World& world, float posX, float posY, bool destructible, float velocityDirection) : _world(world) {

    isDestructible = destructible;
    velocityAsteroideX = velocityDirection;

    asteroideShape.setRadius(20);
    asteroideShape.setFillColor(sf::Color(192, 109, 122));
    asteroideShape.setOrigin(asteroideShape.getRadius(), asteroideShape.getRadius());
    asteroideShape.setOutlineThickness(-3);
    asteroideShape.setOutlineColor(sf::Color(220, 186, 198));

    if (!isDestructible) {
        asteroideShape.setFillColor(sf::Color(135, 71, 104));
        asteroideShape.setOutlineColor(sf::Color(125, 27, 78));
    }

    float pixelsMetersRatio = 100.0f;
    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;   //b2_dynamicBody
    bodyDef.position.Set(PixelsToMeters(posX), PixelsToMeters(posY));
    body = world.CreateBody(&bodyDef);

    // Shape of the physical
    b2CircleShape asteroideBox;
    asteroideBox.m_radius =  PixelsToMeters(asteroideShape.getRadius() * 0.5f);

    // The fixture is what it defines the physic react
    b2FixtureDef asteroideFixtureDef;
    asteroideFixtureDef.shape = &asteroideBox;
    asteroideFixtureDef.density = 0.0f;
    asteroideFixtureDef.friction = 0.0f;

    ContactEvent* m_userData = new ContactEvent(*this);
    asteroideFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);


    body->CreateFixture(&asteroideFixtureDef);
}

void Asteroide::Update() {

    body->SetLinearVelocity(b2Vec2(velocityAsteroideX, -1 * speed)); // Make the asteroide move in a linear way (direction given in constructor)
    b2Vec2 position = body->GetPosition();
    sf::Vector2f graphicPosition = MetersToPixels(position);
    asteroideShape.setPosition(graphicPosition);
}

void Asteroide::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(asteroideShape, states);
}

Asteroide::~Asteroide() {
    _world.DestroyBody(body);
}

Asteroide& Asteroide::operator=(const Asteroide& other) {
    Asteroide asteroide(other);
    return asteroide;
}