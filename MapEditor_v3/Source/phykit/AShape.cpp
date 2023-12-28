#include "phykit/AShape.h"

wl::AShape::AShape() { }
wl::AShape::~AShape() { }

wl::AShape::AShape(sf::Vector2f position, sf::Vector2f size, sf::Texture* tex, float z, std::string id)
	: wl::AEntity(position, size, id), tex(*tex)
{
	setZbuffer(z);
	rectShape.setPosition(position);
	rectShape.setSize(size);
	rectShape.setTexture(tex);
}

void wl::AShape::update(sf::Time deltaTime)
{
	rectShape.setPosition(position);
	rectShape.setSize(size);
}

void wl::AShape::processEvents(sf::Event event)
{
}

void wl::AShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectShape);
}
