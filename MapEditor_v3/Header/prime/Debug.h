#pragma once
#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

#include "game_core.h"
#include "prime/ResourceManager.h"
#include "prime/Window.h"

#define debug wl::Debug::getInstance()

namespace wl
{
	class Debug : public sf::Drawable
	{
	public:
		static wl::Debug* getInstance();
		void update(sf::Time deltaTime);
		void processEvents(sf::Event event);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		Debug();
		~Debug();
		static wl::Debug* instance_;

		//sf::View viewTest;
		sf::Text fps_txt, mouse_X, mouse_Y;
	};

} // namespace wl

#endif