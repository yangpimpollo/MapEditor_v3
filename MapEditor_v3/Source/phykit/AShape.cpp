#include "phykit/AShape.h"

wl::AShape::AShape() { }
wl::AShape::~AShape() { }

wl::AShape::AShape(sf::Vector2f position, sf::Vector2f size, sf::Texture* tex, float z, std::string id)
	: wl::AEntity(position, size, id), tex(*tex)
{
	setZbuffer(z);
	rectShape.setPosition(position);
	rectShape.setSize(size);
	rectShape.setTexture(tex); anim = wl::Animation();
}

void wl::AShape::update(sf::Time deltaTime)
{
	rectShape.setPosition(position);
	rectShape.setSize(size);
	if (anim.getIsActive()) {
		anim.update(deltaTime);
		rectShape.setTextureRect(anim.getFrameRec());
	}
}

void wl::AShape::processEvents(sf::Event event)
{
}

void wl::AShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectShape);
}

void wl::AShape::setAnimation(sf::Texture* tex, sf::Vector2f frameSize, int framesNum, sf::Time switchTime)
{
	rectShape.setTexture(tex);
	anim = wl::Animation(tex->getSize(), frameSize, framesNum, switchTime);
}
