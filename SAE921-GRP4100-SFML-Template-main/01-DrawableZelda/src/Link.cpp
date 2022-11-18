#include "Link.h"

const float SPEED = 8.0f;

Link::Link() {

    up.loadFromFile("data/sprites/up.png");
    down.loadFromFile("data/sprites/down.png");
    left.loadFromFile("data/sprites/left.png");
    right.loadFromFile("data/sprites/right.png");

    linkSprite.setTexture(down);
    linkSprite.setOrigin(up.getSize().x / 2.0f, up.getSize().y / 2.0f);
    linkSprite.setPosition(400, 300);
}

void Link::Moveup() {
    std::cout << " up " << std::endl;
    linkSprite.setTexture(down);
    //position.y -= SPEED;
    //spriteLink.setPosition(position);
}

void Link::Movedown() {
    std::cout << " down " << std::endl;
    linkSprite.setTexture(up);
    //position.y += SPEED;
    //spriteLink.setPosition(position);
}

void Link::MoveLeft() {
    std::cout << " Left " << std::endl;
    linkSprite.setTexture(left);
    //position.x -= SPEED;
    //spriteLink.setPosition(position);
}

void Link::MoveRight() {
    std::cout << " Right " << std::endl;
    linkSprite.setTexture(right);
    //position.x += SPEED;
    //spriteLink.setPosition(position);
}

void Link::Move(const sf::Vector2f& direction) {

    ChangeTexture();

    auto position = getPosition();
    position += (direction * SPEED);
    setPosition(position);
}

void Link::ChangeTexture(const sf::Vector2f& direction) {
    if (direction.x > 0)
        linkSprite.setTexture(right);
    if (direction.x < 0)
        linkSprite.setTexture(left);
    if (direction.y > 0)
        linkSprite.setTexture(down);
    if (direction.y < 0)
        linkSprite.setTexture(up);
}


void Link::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}
