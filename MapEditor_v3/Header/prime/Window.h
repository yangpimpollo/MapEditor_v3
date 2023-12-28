#pragma once
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

#include "prime/ResourceManager.h"

#define win wl::Window::getInstance()

namespace wl
{
	class Window : public sf::RenderWindow
	{
	public:
		static wl::Window* getInstance();
		void processEvents(sf::Event event);

		//inline sf::Vector2i getCursorPos() { return sf::Mouse::getPosition(*this); };
		sf::Vector2f getCursorPos();
		inline void setDefaultCursor() { this->setMouseCursor(cursor); };

	private:
		Window();
		~Window();

		static wl::Window* instance_;
		sf::Cursor cursor;

	};

} // namespace wl

#endif