#pragma once
#ifndef ASHAPE_H_INCLUDED
#define ASHAPE_H_INCLUDED

#include "phykit/AEntity.h"

namespace wl
{
	class AShape : public wl::AEntity
	{
	public:
		AShape();
		~AShape();
		AShape(sf::Vector2f position, sf::Vector2f size, sf::Texture* tex, float z, std::string id = "");
		void update(sf::Time deltaTime);
		void processEvents(sf::Event event);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		inline void setTexId(std::string arg) { this->texid = arg; };
		inline std::string getTexId() { return texid; };

	private:
		sf::RectangleShape rectShape;
		sf::Texture tex;
		std::string texid;
	};


} // namespace wl

#endif
