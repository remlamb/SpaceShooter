#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Explosion : public sf::Drawable
{
public:
	Explosion(sf::Vector2f startpos_);

	bool getIsDead();
	void update();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite _sprite;

};
