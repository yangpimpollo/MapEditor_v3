#include "prime/ObjectManager.h"

wl::ObjectManager* wl::ObjectManager::instance_;

wl::ObjectManager::ObjectManager() {}
wl::ObjectManager::~ObjectManager() { std::cout << "delete Object Manager" << std::endl; }

wl::ObjectManager* wl::ObjectManager::getInstance()
{
	if (instance_ == nullptr) instance_ = new wl::ObjectManager();
	return instance_;
}

void wl::ObjectManager::loadRoomObjects(std::string name)
{
	//as1 = AShape(
	//	sf::Vector2f(200.f, 200.f),
	//	sf::Vector2f(100.f, 100.f),
	//	&res->getTexture("scene1", "pixel5"),
	//	200.f
	//);

	//as2 = AShape(
	//	sf::Vector2f(400.f, 200.f),
	//	sf::Vector2f(100.f, 100.f),
	//	&res->getTexture("scene1", "pixel2"),
	//	200.f
	//);

	//-------------------------------------------------------------
	std::vector<std::string> str_object = res->getObjects(name);

	for (int i = 0; i < str_object.size(); i++) {

		std::string _id = findLabel("id", str_object[i]);
		std::string _tex = findLabel("tex", str_object[i]);

		float _x = std::stof(findLabel("x", str_object[i]));
		float _y = std::stof(findLabel("y", str_object[i]));
		float _z = std::stof(findLabel("z", str_object[i]));
		float _w = std::stof(findLabel("w", str_object[i]));
		float _h = std::stof(findLabel("h", str_object[i]));

		allObjects[_id] = new wl::AShape(
			sf::Vector2f(_x, _y),
			sf::Vector2f(_w, _h),
			&res->getTexture(name, _tex),
			_z,
			_id
		);

		intervals.push_back(std::make_pair(_id, _z));
	}
}

void wl::ObjectManager::update(sf::Time deltaTime)
{
	
	//as1.update(deltaTime);
	//as2.update(deltaTime);

	//----------------------------------

	for (int i = 0; i < allObjects.size(); i++) {
		allObjects.at(intervals[i].first)->update(deltaTime);
		intervals[i].second = allObjects.at(intervals[i].first)->getZbuffer();

		//if (dynamic_cast<wl::AShape*>(allObjects.at(intervals[i].first))->getIsDelete()) {
		//	allObjects.erase(intervals[i].first);
		//	intervals.erase(intervals.begin() + i);
		//}
	}

	selectionSort(intervals);
}

void wl::ObjectManager::processEvents(sf::Event event)
{
	
	//as1.processEvents(event);
	//as2.processEvents(event);

	//-----------------------------------


}

void wl::ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(this->as1);
	//target.draw(this->as2);

	//-----------------------------------

	for (int i = 0; i < allObjects.size(); i++) {
		target.draw(*allObjects.at(intervals[i].first));
	}
}

std::string wl::ObjectManager::findLabel(std::string name, std::string arg)
{
	if (arg.find(name + "='") != std::string::npos) {
		auto ini = arg.find(name + "='") + name.size() + 2;
		auto end = arg.find("'", ini + 1);
		return  arg.substr(ini, end - ini);
	}
	else { return ""; }
}

void wl::ObjectManager::selectionSort(std::vector<std::pair<std::string, float>>& array)
{
	int n = array.size();

	for (int i = 0; i < n - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < n; ++j) if (array[j].second < array[minIndex].second) minIndex = j;
		std::swap(array[i], array[minIndex]);
	}
}
