#include "missile.h"

#include <box2d/b2_polygon_shape.h>

long Missile::m_localIdMissile = 0;

Missile::Missile(b2World& world_, const sf::Vector2f startPos_, const float angle_) : Box2DEntity(world_)
{
    createFixture(pixelsToMeters(texManager->getMissileTexture().getSize().x), pixelsToMeters(texManager->getMissileTexture().getSize().y));

    TextureManager* texManager = TextureManager::Instance();
    m_sprite.setTexture(texManager->getMissileTexture());

    m_sprite.setOrigin(0.5f * texManager->getMissileTexture().getSize().x, 0.5f * texManager->getMissileTexture().getSize().y);

    // Defing the box 2D elements
    m_body->SetFixedRotation(true);
    m_body->SetType(b2_kinematicBody);
    m_body->SetAngularDamping(0.0f);
    m_body->SetLinearDamping(0.0f);
    
    // Set Datas
    m_userData->setLocalId(getGlobalId());
    m_userData->setType(UserDataType::MISSILE);

    // Set angle, velocity and position -----------------------------
    b2Vec2 physicalStartPos = b2Vec2(pixelsToMeters(startPos_).x, pixelsToMeters(startPos_).y + 0.15f);
    m_body->SetTransform(physicalStartPos, degToRad(angle_ - 90.0f));

    b2Vec2 initialVelocity = m_body->GetLocalVector(b2Vec2(5.0f , 0.0f));
    m_body->SetLinearVelocity(initialVelocity);

    update();

}

//Missile::~Missile()
//{
//	
//}

void Missile::createFixture(const float sizeX, const float sizeY)
{
    // Shape of the physical (A box)
    b2PolygonShape hitBox;
    hitBox.SetAsBox(pixelsToMeters(texManager->getMissileTexture().getSize().x * 0.5f), pixelsToMeters(texManager->getMissileTexture().getSize().y * 0.5f));

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &hitBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit
    playerFixtureDef.isSensor = true;

    m_body->CreateFixture(&playerFixtureDef);

}


void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Missile::update()
{

    // Get the position of the body
    b2Vec2 bodyPos = m_body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = metersToPixels(bodyPos);

    // Set the position of the Graphic object
    setPosition(graphicPosition);

    float angle = m_body->GetAngle();
    setRotation(radToDeg(angle));

}
void Missile::setIsDead()
{
    m_isDead = true;
}
bool Missile::getIsDead()
{
    return m_isDead;
}

long Missile::getLocalId()
{
    return m_userData->getLocalId();
}

long Missile::getGlobalId()
{
    return m_localIdMissile++;
}