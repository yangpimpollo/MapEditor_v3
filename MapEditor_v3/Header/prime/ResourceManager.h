#pragma once
#ifndef RESOURCE_MANAGER_H_INCLUDED
#define RESOURCE_MANAGER_H_INCLUDED

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <codecvt>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define res wl::ResourceManager::getInstance()

namespace wl
{
	class ResourceManager
	{
	public:
		enum Lang { EN, ZH, SP };
		enum Type { None, Header, Font, Texture, Sound, String, Object };

		static wl::ResourceManager* getInstance();
		void loadRoom(std::string name);
		void saveRoom(std::string name);
		void closeRoom(std::string name);

		void importRes(std::string name, std::string datatext);
		void deleteRes(std::string name, Type type, std::string id);
		void listRes(std::string name);

		inline void setObjects(std::string name, std::vector<std::string> arg) { str_object[name] = arg;  };

		inline sf::Font& getFont(std::string name, std::string id) { return font.at(name).at(id).second; };
		inline sf::Texture& getTexture(std::string name, std::string id) { return texture.at(name).at(id).second; };
		inline sf::SoundBuffer& getSound(std::string name, std::string id) { return sound.at(name).at(id).second; };
		inline std::wstring& getStr(Lang lang, std::string name, std::string id);
		inline std::vector<std::string>& getObjects(std::string name) { return str_object.at(name); };

	private:
		ResourceManager();
		~ResourceManager();
		static wl::ResourceManager* instance_;
		//void addResource(std::string name, Type type, std::string datatext);
		//void loadResource(std::string name, Type type, std::string datatext);

		//------------------ tools ----------------------

		Type LabelType(std::string arg);
		std::string findLabel(std::string name, std::string arg);
		std::wstring to_wstring(std::string str);

		//------------------ arrays ---------------------

		std::map<std::string, std::vector<std::string>> str_header;
		std::map<std::string, std::vector<std::string>> str_string;
		std::map<std::string, std::vector<std::string>> str_object;

		std::map < std::string, std::map < std::string, std::pair <std::string, sf::Font>>> font;
		std::map <std::string, std::map<std::string, std::pair <std::string, sf::Texture>>> texture;
		std::map <std::string, std::map<std::string, std::pair <std::string, sf::SoundBuffer>>> sound;

		std::map <std::string, std::map<std::string, std::wstring>> en_pack;
		std::map <std::string, std::map<std::string, std::wstring>> zh_pack;
		std::map <std::string, std::map<std::string, std::wstring>> sp_pack;

		std::vector<std::string> all_rooms;

	};

	inline std::wstring& wl::ResourceManager::getStr(Lang lang, std::string name, std::string id)
	{
		switch (lang)
		{
		case Lang::EN: return en_pack.at(name).at(id); break;
		case Lang::ZH: return zh_pack.at(name).at(id); break;
		case Lang::SP: return sp_pack.at(name).at(id); break;
		}
	}


} // namespace wl

#endif