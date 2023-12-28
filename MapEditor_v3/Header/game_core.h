#pragma once
#ifndef GAME_CORE_H_INCLUDED
#define GAME_CORE_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

#include "prime/Debug.h"
#include "prime/ResourceManager.h"
//#include "prime/SceneManager.h"
#include "prime/Tester1.h"
//#include "prime/Tester2.h"
//#include "prime/Tester3.h"
#include "prime/Window.h"

#define core wl::game_core::getInstance()

namespace wl
{
	class game_core
	{
	public:
		static wl::game_core* getInstance();
		void start();
		inline bool setReset(bool arg) { this->resetRequest = arg; };
		inline int getFPS() { return this->fps; };

	private:
		static wl::game_core* instance_;

		game_core();
		~game_core();
		int fps = 0;
		int fps_counter = 0;
		bool resetRequest = false;

		void init();
		void cicles();
		void processEvents();
		void update(sf::Time deltaTime);
		void render();

		sf::Context context;

	};

} // namespace wl

#endif