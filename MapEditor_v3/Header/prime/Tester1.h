#pragma once
#ifndef TESTER1_H_INCLUDED
#define TESTER1_H_INCLUDED

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "prime/ObjectManager.h"
#include "prime/ResourceManager.h"
#include "prime/Window.h"

#include "phykit/AEditTool.h"
#include "phykit/AShape.h"

namespace wl
{
	class Tester1 : public sf::Drawable
	{
	public:
		static wl::Tester1* getInstance();
		void update(sf::Time deltaTime);
		void processEvents(sf::Event event);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		Tester1();
		~Tester1();
		static wl::Tester1* instance_;

		sf::View viewTest;

		wl::AEditTool miTool;
	};


} // namespace wl

#endif
