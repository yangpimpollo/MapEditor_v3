#pragma once
#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <iostream>
#include <random>

namespace wl
{
	class Math
	{
	public:
		inline static std::string genID();

	};

	inline std::string Math::genID()
	{
		const std::string allChar = "3M80z9j375694LD6uGa1ngR6307h19i0472594HYP122eC08Nc5E260pldQ5643sZBFKrO85wX3Amx1bW1UI7t42qvTo8S78yfV9Jk";

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, allChar.size() - 1);

		std::string uniqueId = "_@";

		for (int i = 0; i < 8; ++i) {
			char character = allChar[distrib(gen)];
			uniqueId += character;
		}
		return uniqueId;
	}

} // namespace wl

#endif