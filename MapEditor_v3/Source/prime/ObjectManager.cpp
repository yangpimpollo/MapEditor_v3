#include "prime/ObjectManager.h"

wl::ObjectManager* wl::ObjectManager::instance_;

wl::ObjectManager::ObjectManager() {}
wl::ObjectManager::~ObjectManager() { std::cout << "delete Object Manager" << std::endl; }

wl::ObjectManager* wl::ObjectManager::getInstance()
{
	if (instance_ == nullptr) instance_ = new wl::ObjectManager();
	return instance_;
}

void wl::ObjectManager::loadRoomObjects(std::string name)
{
	as1 = AShape(
		sf::Vector2f(200.f, 200.f),
		sf::Vector2f(100.f, 100.f),
		&res->getTexture("scene1", "pixel5"),
		200.f
	);

	as2 = AShape(
		sf::Vector2f(400.f, 200.f),
		sf::Vector2f(100.f, 100.f),
		&res->getTexture("scene1", "pixel2"),
		200.f
	);
}

void wl::ObjectManager::update(sf::Time deltaTime)
{
	
	as1.update(deltaTime);
	as2.update(deltaTime);
}

void wl::ObjectManager::processEvents(sf::Event event)
{
	
	as1.processEvents(event);
	as2.processEvents(event);
}

void wl::ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->as1);
	target.draw(this->as2);
}
