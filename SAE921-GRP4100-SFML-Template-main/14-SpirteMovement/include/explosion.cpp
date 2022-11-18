#include "explosion.h"

#include <SFML/Graphics/RenderTarget.hpp>

Explosion::Explosion(sf::Vector2f startpos_)
{

}

bool Explosion::getIsDead()
{
	return false;
}
void Explosion::update()
{

}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
