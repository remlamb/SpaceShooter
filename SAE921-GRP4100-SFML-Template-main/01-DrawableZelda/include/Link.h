#pragma once
#include "SFML\Graphics.hpp"

class Link : public sf::Drawable
{
private:
	//loading file as texture
	sf::Texture up;
	sf::Texture down;
	sf::Texture left;
	sf::Texture right;

	sf::Sprite linkSprite;

public:
	Link();

	void Moveup();
	void Movedown();
	void MoveLeft();
	void MoveRight();

	void Move(const sf::Vector2f&);
	void ChangeTexture(const sf::Vector2f&);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
