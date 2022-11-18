#include "GameLimit.h"
#include "SFMLToBox2D.h"

GameLimit::GameLimit() {

}


void GameLimit::SetUpBordure(b2World& world, sf::RenderWindow& window) {
    SetUpABordure(window.getSize().x, -1 * (window.getSize().y/ 2), 1, window.getSize().y, world); //right
    SetUpABordure(0, -1 * (window.getSize().y /2), 1, window.getSize().y, world); //lefft
    SetUpABordure(window.getSize().x /2, -1, window.getSize().x, 1, world);//top
    SetUpABordure(window.getSize().x /2, -1 * window.getSize().y, window.getSize().x, 1, world); //bottom 
}

void GameLimit::SetUpABordure(int posX, int posY, int sizeX, int sizeY, b2World& world) {

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 windowSize = b2Vec2(1280, -1 * 720);
    bodyDef.position.Set(PixelsToMeters(posX), PixelsToMeters(posY));
    body = world.CreateBody(&bodyDef);
    // Shape of the physical
    b2PolygonShape limitBox;
    limitBox.SetAsBox(PixelsToMeters(sizeX * 0.5), PixelsToMeters(sizeY * 0.5));
    // The fixture is what it defines the physic react
    b2FixtureDef limitFixtureDef;
    limitFixtureDef.shape = &limitBox;
    limitFixtureDef.density = 0.0f;
    limitFixtureDef.friction = 1.0f;

    ContactEvent* m_userData = new ContactEvent(*this);
    limitFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    body->CreateFixture(&limitFixtureDef);
}
