#pragma once
#ifndef OBJECT_MANAGER_H_INCLUDED
#define OBJECT_MANAGER_H_INCLUDED

#include <iostream>
#include <string> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "prime/ResourceManager.h"

#include "phykit/AShape.h"


#define obj_mng wl::ObjectManager::getInstance()

namespace wl
{
	class ObjectManager : public sf::Drawable
	{
	public:
		static wl::ObjectManager* getInstance();
		void loadRoomObjects(std::string name);

		void update(sf::Time deltaTime);
		void processEvents(sf::Event event);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		inline std::map<std::string, wl::AEntity*>* getAllobj() { return &allObjects; };
		inline std::vector<std::pair <std::string, float>>* getIntervals() { return &intervals; };


		//inline AEntity* getObject() { return &as1; }; /////temp


	private:
		ObjectManager();
		~ObjectManager();
		static wl::ObjectManager* instance_;

		std::map<std::string, wl::AEntity*> allObjects;
		std::vector<std::pair <std::string, float>> intervals;

		std::string findLabel(std::string name, std::string arg);
		void selectionSort(std::vector<std::pair <std::string, float>>& array);


		//wl::AShape as1, as2;
		

	};






} // namespace wl

#endif