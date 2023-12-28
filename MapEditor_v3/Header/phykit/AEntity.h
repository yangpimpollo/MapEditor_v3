#pragma once
#ifndef AENTITY_H_INCLUDED
#define AENTITY_H_INCLUDED


#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "util/Math.h"
#include "prime/ResourceManager.h"
#include "prime/Window.h"

namespace wl
{
	class AEntity : public sf::Drawable
	{
	public:
		AEntity();
		~AEntity();
		AEntity(sf::Vector2f position, sf::Vector2f size, std::string id = "");
		virtual void update(sf::Time deltaTime) = 0;
		virtual void processEvents(sf::Event event) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		inline bool operator==(const AEntity& other) const { return this == &other; };
		inline bool equals(const AEntity& other) const { return *this == other; };

		inline void setID(std::string arg) { this->objectId = arg; };
		inline void setPosition(sf::Vector2f arg) { this->position = arg; };
		inline void setSize(sf::Vector2f arg) { this->size = arg; };
		inline void setZModule(float arg) { this->z_module = arg; };
		inline void setZbuffer(float arg) { this->z_module = arg - position.y; };

		inline std::string getID() { return objectId; };
		inline sf::Vector2f getPosition() { return this->position; };
		inline sf::Vector2f getSize() { return this->size; };
		inline float getZModule() { return z_module; }
		inline float getZbuffer() { return position.y + z_module; }

		inline void generateID() { this->objectId = wl::Math::genID(); };
		inline sf::Vector2f getCenter() { return position + size / 2.f; }

		inline bool CursorIn();
		inline bool CursorInCorner();
		inline bool CursorInZgizmo();

	protected:
		std::string objectId;
		sf::Vector2f position, size;
		float z_module;                // distance z to origin

	};

	inline AEntity::AEntity()
	{
	}

	inline AEntity::~AEntity()
	{
	}

	inline AEntity::AEntity(sf::Vector2f position, sf::Vector2f size, std::string id)
		: position(position), size(size), objectId(id)
	{
		if (id.empty()) generateID(); else objectId = id;
	}

	inline bool AEntity::CursorIn()
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*win);

		if (mouse_pos.x > position.x && mouse_pos.x < position.x + size.x) {
			if (mouse_pos.y > position.y && mouse_pos.y < position.y + size.y) return true;
		}
		return false;
	}

	inline bool AEntity::CursorInCorner()
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*win);
		sf::Vector2f cornerPos = (position + size) - sf::Vector2f(3.f, 3.f);

		if (mouse_pos.x > cornerPos.x && mouse_pos.x < cornerPos.x + 6.f) {
			if (mouse_pos.y > cornerPos.y && mouse_pos.y < cornerPos.y + 6.f) return true;
		}
		return false;
	}

	inline bool AEntity::CursorInZgizmo()
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*win);
		sf::Vector2f ZQuadPos = sf::Vector2f(position.x - 3.f, position.y + z_module);

		if (mouse_pos.x > ZQuadPos.x && mouse_pos.x < ZQuadPos.x + 5.f) {
			if (mouse_pos.y > ZQuadPos.y && mouse_pos.y < ZQuadPos.y + 4.f) return true;
		}
		return false;
	}


} // namespace wl


#endif
