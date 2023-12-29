#pragma once
#ifndef AEDIT_TOOL_H_INCLUDED
#define AEDIT_TOOL_H_INCLUDED

#include <iostream>
#include <SFML/Graphics.hpp>

#include "prime/ObjectManager.h"
#include "prime/ResourceManager.h"
#include "phykit/AEntity.h"

namespace wl
{

	class AEditTool : public sf::Drawable
	{
	public:
		AEditTool();
		~AEditTool();
		void update(sf::Time deltaTime);
		void processEvents(sf::Event event);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setEnabled(bool arg) { this->activeEdit = arg; };
		void setToggle() { this->activeEdit = !activeEdit; };

	private:
		AEntity* selectEnt;
		sf::Vector2f _position, _size;
		float _z_module;

		bool activeEdit = false;
		bool isDragging = false;
		bool isScale = false;
		bool isDragZQuad = false;
		bool isSelected = false;
		float z_moduleOffset0;
		sf::Vector2f mouseOffset;
		sf::Vector2f sizeOffset;

		sf::RectangleShape edgeShape, zShape, zLine;
		sf::Vertex lineL[2], lineR[2];

		sf::Color color = sf::Color::Magenta;

		sf::Text id_tx, w_tx, h_tx, x_tx, y_tx, z_tx;
	};



} // namespace wl

#endif