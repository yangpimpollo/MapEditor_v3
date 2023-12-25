#include "prime/Debug.h"

wl::Debug* wl::Debug::instance_;

wl::Debug* wl::Debug::getInstance()
{
	if (instance_ == nullptr) instance_ = new wl::Debug();
	return instance_;
}

wl::Debug::Debug() 
{
	fps_txt.setFont(res->getFont("global", "CascadiaMono300"));
	fps_txt.setCharacterSize(15);
	fps_txt.setFillColor(sf::Color::Red);
	fps_txt.setPosition(40.f, 40.f);

	mouse_X.setFont(res->getFont("global", "CascadiaMono300"));
	mouse_X.setCharacterSize(12);
	mouse_X.setFillColor(sf::Color::Red);
	mouse_X.setPosition(40.f, 65.f);

	mouse_Y.setFont(res->getFont("global", "CascadiaMono300"));
	mouse_Y.setCharacterSize(12);
	mouse_Y.setFillColor(sf::Color::Red);
	mouse_Y.setPosition(40.f, 80.f);
}
wl::Debug::~Debug() {}

void wl::Debug::update(sf::Time deltaTime)
{
	std::string fps = std::to_string(core->getFPS());
	fps_txt.setString("fps: " + fps);

	std::string x = std::to_string(sf::Mouse::getPosition(*win).x);
	std::string y = std::to_string(sf::Mouse::getPosition(*win).y);
	this->mouse_X.setString("screen x: " + x);
	this->mouse_Y.setString("screen y: " + y);
}

void wl::Debug::processEvents(sf::Event event)
{
}

void wl::Debug::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->fps_txt);
	target.draw(this->mouse_X);
	target.draw(this->mouse_Y);
}

