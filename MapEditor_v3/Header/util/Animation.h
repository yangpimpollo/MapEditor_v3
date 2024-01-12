#pragma once
#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace wl
{
	class Animation
	{
	public:
		Animation();
		Animation(sf::Vector2u texSize, sf::Vector2f frameSize, int num_frames, sf::Time switchTime);
		~Animation();
		void update(sf::Time  deltaTime);
		inline sf::IntRect getFrameRec() { return framesRec[frameCount]; };
		inline bool getIsActive() { return isActive; };

	private:
		bool isActive = false;
		int frameCount = 0;
		std::vector<sf::IntRect> framesRec;
		sf::Time switchTime, totalTime;
	};

	inline Animation::Animation()
	{
	}

	inline Animation::Animation(sf::Vector2u texSize, sf::Vector2f frameSize, int num_frames, sf::Time switchTime)
		: switchTime(switchTime)
	{
		isActive = true;
		int count = 0;

		for (int j = 0; j < (texSize.y / frameSize.y); j++) {
			for (int i = 0; i < (texSize.x / frameSize.x); i++) {
				if(count<num_frames) framesRec.push_back(sf::IntRect(i* frameSize.x, j* frameSize.y, frameSize.x, frameSize.y));
				count += 1;
			}
		}


	}

	inline Animation::~Animation()
	{
	}

	inline void Animation::update(sf::Time deltaTime)
	{
		totalTime += deltaTime;

		if (totalTime >= switchTime) {
			totalTime -= switchTime;
			frameCount++;
			if (frameCount >= framesRec.size()) frameCount = 0;
		}
	}

} // namespace wl

#endif