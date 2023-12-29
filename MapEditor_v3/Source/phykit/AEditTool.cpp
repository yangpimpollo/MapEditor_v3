#include "phykit/AEditTool.h"

wl::AEditTool::AEditTool()
{
	edgeShape.setFillColor(sf::Color(255, 0, 255, 50));
	edgeShape.setOutlineThickness(1.f);
	edgeShape.setOutlineColor(color);

	zShape.setSize(sf::Vector2f(5.f, 4.f));
	zShape.setFillColor(color);
	zShape.setOutlineThickness(1.f);
	zShape.setOutlineColor(color);

	//zLine.setSize(sf::Vector2f(1.f, z_module));
	zLine.setFillColor(color);

	//--------------------------
	id_tx.setFont(res->getFont("global", "CascadiaMono300"));
	id_tx.setCharacterSize(10);
	id_tx.setFillColor(color);
	w_tx.setFont(res->getFont("global", "CascadiaMono300"));
	w_tx.setCharacterSize(10);
	w_tx.setFillColor(color);
	h_tx.setFont(res->getFont("global", "CascadiaMono300"));
	h_tx.setCharacterSize(10);
	h_tx.setFillColor(color);
	x_tx.setFont(res->getFont("global", "CascadiaMono300"));
	x_tx.setCharacterSize(10);
	x_tx.setFillColor(color);
	y_tx.setFont(res->getFont("global", "CascadiaMono300"));
	y_tx.setCharacterSize(10);
	y_tx.setFillColor(color);
	z_tx.setFont(res->getFont("global", "CascadiaMono300"));
	z_tx.setCharacterSize(10);
	z_tx.setFillColor(color);
	//--------------------------
}

wl::AEditTool::~AEditTool()
{
}

void wl::AEditTool::update(sf::Time deltaTime)
{
	if (selectEnt != nullptr) {
		//std::cout << "update tool" << std::endl;
		edgeShape.setSize(_size);
		edgeShape.setPosition(_position);

		zShape.setPosition(_position.x - 3.f, _position.y + _z_module);
		zLine.setPosition(sf::Vector2f(_position.x - 1.f, _position.y));
		zLine.setSize(sf::Vector2f(1.f, _z_module));

		//--------------------------
		id_tx.setPosition(_position.x, _position.y - 15.f);
		id_tx.setString(selectEnt->getID());
		w_tx.setPosition(_position.x + _size.x + 5.f, _position.y);
		w_tx.setString("w:" + std::to_string((int)_size.x));
		h_tx.setPosition(_position.x + _size.x + 5.f, _position.y + 15.f);
		h_tx.setString("h:" + std::to_string((int)_size.y));
		x_tx.setPosition(_position.x + _size.x + 5.f, _position.y + 30.f);
		x_tx.setString("x:" + std::to_string((int)_position.x));
		y_tx.setPosition(_position.x + _size.x + 5.f, _position.y + 45.f);
		y_tx.setString("y:" + std::to_string((int)_position.y));
		z_tx.setPosition(_position.x + _size.x + 5.f, _position.y + 60.f);
		z_tx.setString("z:" + std::to_string((int)selectEnt->getZbuffer()));
		//--------------------------

		lineL[0] = sf::Vertex(selectEnt->getCenter() - sf::Vector2f(5.f, 5.f), color);
		lineL[1] = sf::Vertex(selectEnt->getCenter() + sf::Vector2f(5.f, 5.f), color);
		lineR[0] = sf::Vertex(selectEnt->getCenter() - sf::Vector2f(5.f, -5.f), color);
		lineR[1] = sf::Vertex(selectEnt->getCenter() + sf::Vector2f(5.f, -5.f), color);

		//--------------------------
	}
}

void wl::AEditTool::processEvents(sf::Event event)
{
	//selectEnt = obj_mng->getObject();

	if (!isSelected && !activeEdit && !isDragging) {
		for (int i = obj_mng->getIntervals()->size() - 1; i >= 0; i--) {
			if ((*obj_mng->getAllobj()).at((*obj_mng->getIntervals())[i].first)->CursorIn()) {
				selectEnt = (*obj_mng->getAllobj()).at((*obj_mng->getIntervals())[i].first);
				break;
			}
		}
	}

	if (selectEnt != nullptr) {
		_position = selectEnt->getPosition();
		_size = selectEnt->getSize();
		_z_module = selectEnt->getZModule();

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (selectEnt->CursorInZgizmo()) {
				isDragZQuad = true;
				mouseOffset = win->getCursorPos();
				z_moduleOffset0 = _z_module;
			}
			else if (selectEnt->CursorInCorner() && activeEdit) {
				isScale = true;
				mouseOffset = win->getCursorPos();
				sizeOffset = _size;
			}
			else if (selectEnt->CursorIn()) {
				isDragging = true;
				mouseOffset = win->getCursorPos() - _position;
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			//std::cout << "click" << std::endl;
			isSelected = (selectEnt->CursorIn() || selectEnt->CursorInZgizmo()) ? true : false;
			mouseOffset = sf::Vector2f(0.f, 0.f);
			isDragging = false;
			isScale = false;
			isDragZQuad = false;

		}
		else if (event.type == sf::Event::MouseMoved) {

			if (isDragZQuad) {
				float delta = win->getCursorPos().y - mouseOffset.y;
				_z_module = z_moduleOffset0 + delta;
				selectEnt->setZModule(_z_module);
			}
			else if (isScale) {
				sf::Vector2f delta = win->getCursorPos() - mouseOffset;
				if ((sizeOffset + delta).x > 10.f && (sizeOffset + delta).y > 10.f) {
					_size = sizeOffset + delta;
				}
				selectEnt->setSize(_size);
			}
			else if (isDragging) {
				_position = win->getCursorPos() - mouseOffset;
				selectEnt->setPosition(_position);
			}

		}

		//--------------------------
		if (isSelected) {
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::E)
				setToggle();
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
				setToggle();
		}
		else {
			setEnabled(false);
		}

		if (selectEnt->CursorInCorner() && activeEdit) {
			sf::Cursor cursorSize;
			cursorSize.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
			win->setMouseCursor(cursorSize);
		}
		else {
			win->setDefaultCursor();
		}

		if (selectEnt->CursorInZgizmo() && activeEdit) {
			zShape.setFillColor(sf::Color::Transparent);
		}
		else {
			zShape.setFillColor(color);
		}

		if (activeEdit) {
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::D) {
				isDelete = true;
				std::cout << "delete: " << selectEnt->getID() << std::endl;
			}
		}
	}
}

void wl::AEditTool::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//std::cout << "draw tool" << std::endl;
	if (activeEdit) {
		target.draw(edgeShape);
		target.draw(zShape);
		target.draw(id_tx);
		target.draw(w_tx);
		target.draw(h_tx);
		target.draw(x_tx);
		target.draw(y_tx);
		target.draw(z_tx);
		target.draw(zLine);
	}

	if (isSelected) {
		target.draw(lineL, 2, sf::Lines);
		target.draw(lineR, 2, sf::Lines);
	}
}
