#include "prime/Window.h"

wl::Window* wl::Window::instance_;

wl::Window* wl::Window::getInstance()
{
	if (instance_ == nullptr) instance_ = new wl::Window();
	return instance_;
}

void wl::Window::processEvents(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		this->close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		this->close();
}

wl::Window::Window()
{
	std::cout << "create game window" << std::endl;

	int WIDTH = 900;
	int HEIGHT = 600;
	int winStyle = 1;
	std::string TITLE = "wild_mapEditor";

	sf::ContextSettings settings; settings.antialiasingLevel = 8;
	sf::Image cursorImg = res->getTexture("global", "cursor").copyToImage();
	cursor.loadFromPixels(cursorImg.getPixelsPtr(), sf::Vector2u(20, 20), sf::Vector2u(0, 0));

	this->create(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Default, settings);
	this->setIcon(64, 64, sf::Image(res->getTexture("global", "icon").copyToImage()).getPixelsPtr());
	this->setMouseCursor(cursor);

}

wl::Window::~Window()
{
	std::cout << "delete game window" << std::endl;
}
