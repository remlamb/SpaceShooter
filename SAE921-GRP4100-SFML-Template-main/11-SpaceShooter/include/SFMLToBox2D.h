#pragma once
#include "SFML/Graphics.hpp"
#include <box2d/b2_math.h>


constexpr float PIXELS_METERS_RATIO = 100.0f;

static b2Vec2 PixelsToMeters(sf::Vector2f pixels) {
	return b2Vec2(pixels.x / PIXELS_METERS_RATIO, 1.0f * pixels.y / PIXELS_METERS_RATIO);
}

static b2Vec2 PixelsToMeters(sf::Vector2u pixels) {
	return b2Vec2(pixels.x / PIXELS_METERS_RATIO, 1.0f * pixels.y / PIXELS_METERS_RATIO);
}

static float PixelsToMeters(float pixels){
	return pixels / PIXELS_METERS_RATIO;
}

static sf::Vector2f MetersToPixels(b2Vec2 meters) {
	return sf::Vector2f(meters.x * PIXELS_METERS_RATIO, -1 * meters.y * PIXELS_METERS_RATIO);
}
