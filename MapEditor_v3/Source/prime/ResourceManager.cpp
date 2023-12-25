#include "prime/ResourceManager.h"

wl::ResourceManager* wl::ResourceManager::instance_;


wl::ResourceManager::ResourceManager() {}
wl::ResourceManager::~ResourceManager() { std::cout << "delete Resource Manager" << std::endl; }

wl::ResourceManager* wl::ResourceManager::getInstance()
{
	if (instance_ == nullptr) instance_ = new wl::ResourceManager();
	return instance_;
}

void wl::ResourceManager::loadRoom(std::string name)
{
	if (!std::binary_search(all_rooms.begin(), all_rooms.end(), name)) {
		std::cout << "load scene:" << name << " resources" << std::endl;

		std::string datatext;
		std::fstream initFile;
		initFile.open("./rooms/" + name + ".room");  //, std::ios::in | std::ios::out | std::ios::app);
		if (!initFile) {
			std::cout << "Error occurred: file not loaded" << std::endl;
			exit(-1);
		}

		while (std::getline(initFile, datatext)) {
			importRes(name, datatext);
		}
		initFile.close();

		all_rooms.push_back(name);
		std::cout << "loaded " << name << " : complete" << std::endl;
	}
	else {
		std::cout << "ya esta cargado" << std::endl;
	}
}

void wl::ResourceManager::saveRoom(std::string name)
{
}

void wl::ResourceManager::closeRoom(std::string name)
{
	auto it = std::find(all_rooms.begin(), all_rooms.end(), name);
	if (it != all_rooms.end()) {
		all_rooms.erase(it);

		str_header.erase(name);
		str_string.erase(name);
		str_object.erase(name);

		font.erase(name);
		texture.erase(name);
		sound.erase(name);

		en_pack.erase(name);
		zh_pack.erase(name);
		sp_pack.erase(name);

		std::cout << "clear: " << name << " resources" << std::endl;
	}
}

void wl::ResourceManager::importRes(std::string name, std::string datatext)
{
	Type type = LabelType(datatext);
	std::string _id = findLabel("id", datatext);

	switch (type)
	{
	case Type::None: break;
	case Type::Header:
		if (str_header.contains(name)) { str_header.at(name).push_back(datatext); }
		else { str_header[name] = std::vector<std::string>{ datatext }; } break;

	case Type::Font: {
		sf::Font res_;
		if (!res_.loadFromFile("./res/" + name + "/" + findLabel("dat", datatext))) {}

		if (font.contains(name)) { font.at(name)[_id] = std::make_pair(datatext, res_); }
		else { font[name] = std::map<std::string, std::pair <std::string, sf::Font>>{ {_id, std::make_pair(datatext, res_)} }; }

		std::cout << "   -" << _id << std::endl;
	}break;

	case Type::Texture: {
		sf::Texture res_;
		if (!res_.loadFromFile("./res/" + name + "/" + findLabel("dat", datatext))) {}

		if (texture.contains(name)) { texture.at(name)[_id] = std::make_pair(datatext, res_); }
		else { texture[name] = std::map<std::string, std::pair <std::string, sf::Texture>>{ {_id, std::make_pair(datatext, res_)} }; }

		std::cout << "   -" << _id << std::endl;
	}break;

	case Type::Sound: {
		sf::SoundBuffer res_;
		if (!res_.loadFromFile("./res/" + name + "/" + findLabel("dat", datatext))) {}

		if (sound.contains(name)) { sound.at(name)[_id] = std::make_pair(datatext, res_); }
		else { sound[name] = std::map<std::string, std::pair <std::string, sf::SoundBuffer>>{ {_id, std::make_pair(datatext, res_)} }; }

		std::cout << "   -" << _id << std::endl;
	}break;

	case Type::String: {
		if (str_string.contains(name)) { str_string.at(name).push_back(datatext); }
		else {
			str_string[name] = std::vector<std::string>{ datatext };

			if (en_pack.contains(name)) {
				en_pack.at(name)[_id] = to_wstring(findLabel("EN", datatext));
				zh_pack.at(name)[_id] = to_wstring(findLabel("ZH", datatext));
				sp_pack.at(name)[_id] = to_wstring(findLabel("SP", datatext));
			}
			else {
				en_pack[name] = std::map<std::string, std::wstring>{ {_id, to_wstring(findLabel("EN", datatext))} };
				zh_pack[name] = std::map<std::string, std::wstring>{ {_id, to_wstring(findLabel("ZH", datatext))} };
				sp_pack[name] = std::map<std::string, std::wstring>{ {_id, to_wstring(findLabel("SP", datatext))} };
			}
		}
	}break;

	case Type::Object: {
		if (str_object.contains(name)) { str_object.at(name).push_back(datatext); }
		else { str_object[name] = std::vector<std::string>{ datatext }; }

		std::cout << "   -" << _id << std::endl;
	}  break;

	default: {} break;
	}

}

void wl::ResourceManager::deleteRes(std::string name, Type type, std::string id)
{
	switch (type)
	{
	case Type::Font: font[name].erase(id); break;
	case Type::Texture: texture[name].erase(id); break;
	case Type::Sound: sound[name].erase(id); break;

	case Type::Object: break;
	default: break;
	}
}

//----------------------------- tools -------------------------------


wl::ResourceManager::Type wl::ResourceManager::LabelType(std::string arg)
{
	auto ini = arg.find("<") + 1;
	auto end = arg.find(" ", ini + 1);
	std::string result = arg.substr(ini, end - ini);

	if (result == "!--" || result == "room") { return Type::Header; }
	else if (result == "font") { return Type::Font; }
	else if (result == "texture") { return Type::Texture; }
	else if (result == "sound") { return Type::Sound; }
	else if (result == "string") { return Type::String; }
	else if (result == "object") { return Type::Object; }
	else { return Type::None; }
}

std::string wl::ResourceManager::findLabel(std::string name, std::string arg)
{
	if (arg.find(name + "='") != std::string::npos) {
		auto ini = arg.find(name + "='") + name.size() + 2;
		auto end = arg.find("'", ini + 1);
		return  arg.substr(ini, end - ini);
	}
	else { return ""; }
}

std::wstring wl::ResourceManager::to_wstring(std::string str)
{
	using convert_t = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_t, wchar_t> strconverter;
	return strconverter.from_bytes(str);
}
