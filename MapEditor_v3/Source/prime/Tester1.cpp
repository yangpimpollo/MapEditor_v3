#include "prime/Tester1.h"

wl::Tester1* wl::Tester1::instance_;

wl::Tester1* wl::Tester1::getInstance()
{
	if (instance_ == nullptr) instance_ = new wl::Tester1();
	return instance_;
}

wl::Tester1::Tester1()
{
	//-----------
	viewTest = sf::View(sf::FloatRect(0.f, 0.f, 900, 600));
	viewTest.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	//-----------

	obj_mng->loadRoomObjects("scene1");
}

wl::Tester1::~Tester1()
{
}

void wl::Tester1::update(sf::Time deltaTime)
{
	miTool.update(deltaTime);
	obj_mng->update(deltaTime);
}

void wl::Tester1::processEvents(sf::Event event)
{
	if (event.type == sf::Event::Resized)
	{
		viewTest.setSize(event.size.width, event.size.height);
		viewTest.setCenter(event.size.width / 2, event.size.height / 2);
	}

	//--------------------------
	miTool.processEvents(event);
	obj_mng->processEvents(event);
}

void wl::Tester1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(viewTest);

	//--------------------------
	target.draw(*obj_mng);
	target.draw(this->miTool);
}


