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
	std::vector<std::string> str_object = res->getObjects(name);

	for (int i = 0; i < str_object.size(); i++) {

		std::string _id = findLabel("id", str_object[i]);
		std::string _tex = findLabel("tex", str_object[i]);

		float _x = std::stof(findLabel("x", str_object[i]));
		float _y = std::stof(findLabel("y", str_object[i]));
		float _z = std::stof(findLabel("z", str_object[i]));
		float _w = std::stof(findLabel("w", str_object[i]));
		float _h = std::stof(findLabel("h", str_object[i]));
		std::string _u = findLabel("u", str_object[i]);
		std::cout << "uuuu" << _u << std::endl;

		allObjects[_id] = new wl::AShape(
			sf::Vector2f(_x, _y),
			sf::Vector2f(_w, _h),
			&res->getTexture(name, _tex),
			_z,
			_id
		);

		//dynamic_cast<wl::AShape*>(allObjects[_id])->

		dynamic_cast<wl::AShape*>(allObjects[_id])->setTexId(_tex);

		intervals.push_back(std::make_pair(_id, _z));
	}

	//coin = new wl::AShape();
	dynamic_cast<wl::AShape*>(allObjects.at("_@coin"))->setAnimation(
		&res->getTexture(name, "coin"), 
		sf::Vector2f(100, 100),
		7,
		sf::microseconds(200000)
		);

}

std::vector<std::string> wl::ObjectManager::getRoomObjects_str()
{
	std::vector<std::string> str_object;

	for (int i = 0; i < allObjects.size(); i++) {

		//<object id = '_@glRuS233' x = '200' y = '200' z = '200' w = '100' h = '100' tex = 'pixel5' / >

		std::string s1 = "    <object id='" + allObjects.at(intervals[i].first)->getID();
		std::string s2 = "' x='" + std::to_string(allObjects.at(intervals[i].first)->getPosition().x);
		std::string s3 = "' y='" + std::to_string(allObjects.at(intervals[i].first)->getPosition().y);
		std::string s4 = "' z='" + std::to_string(allObjects.at(intervals[i].first)->getZbuffer());
		std::string s5 = "' w='" + std::to_string(allObjects.at(intervals[i].first)->getSize().x);
		std::string s6 = "' h='" + std::to_string(allObjects.at(intervals[i].first)->getSize().y);
		std::string s7 = "' tex='" + dynamic_cast<wl::AShape*>(allObjects.at(intervals[i].first))->getTexId();
		std::string s8 = "' />";

		str_object.push_back(s1+s2+s3+s4+s5+s6+s7+s8);
	}
	return str_object;
}

void wl::ObjectManager::deleteObject(std::string id)
{
	allObjects.erase(id);
	auto it = find_if(intervals.begin(), intervals.end(), [&](std::pair<std::string, float> interval) {
		return interval.first == id;
		});
	if (it != intervals.end()) intervals.erase(it);
}

void wl::ObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < allObjects.size(); i++) {
		allObjects.at(intervals[i].first)->update(deltaTime);
		intervals[i].second = allObjects.at(intervals[i].first)->getZbuffer();
	}

	selectionSort(intervals);
}

void wl::ObjectManager::processEvents(sf::Event event)
{

}

void wl::ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
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
