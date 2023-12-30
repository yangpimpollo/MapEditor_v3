#include "game_core.h"

wl::game_core* wl::game_core::instance_;

wl::game_core::game_core(){}
wl::game_core::~game_core(){}

wl::game_core* wl::game_core::getInstance()
{
    if (instance_ == nullptr) instance_ = new wl::game_core();
    return instance_;
}

void wl::game_core::start()
{
    std::cout << "start wild_mapEditor_v3" << std::endl;
    do {
        init();
        cicles();
    } while (this->resetRequest);
    std::cout << "end of cycle" << std::endl;
}

void wl::game_core::init()
{
    res->loadRoom("global");
    
}

void wl::game_core::cicles()
{
    const int _fps = 60;
    sf::Time update_time = sf::microseconds(1000000 / _fps);
    sf::Clock clock;

    sf::Time ref_update = clock.getElapsedTime();
    sf::Time ref_counter = clock.getElapsedTime();

    sf::Time time_elapsed;
    sf::Time delta;

    fps_counter = 0;
    while (wl::Window::getInstance()->isOpen())
    {
        sf::Time cycle_start = clock.getElapsedTime();
        time_elapsed = cycle_start - ref_update;
        ref_update = cycle_start;

        delta += time_elapsed;

        processEvents();
        update(time_elapsed);

        if (delta >= update_time) {
            render();
            fps_counter++;
            delta -= update_time;
        }

        if (clock.getElapsedTime() - ref_counter > sf::microseconds(1000000)) {
            fps = fps_counter;
            fps_counter = 0;
            ref_counter = clock.getElapsedTime();
        }
    }
}

void wl::game_core::processEvents()
{
    sf::Event event;
    while (win->pollEvent(event))
    {
        win->processEvents(event);
        debug->processEvents(event);
        //wl::SceneManager::getInstance()->processEvents(event);
        wl::Tester1::getInstance()->processEvents(event);  
        ///wl::Tester2::getInstance()->processEvents(event);
        ///wl::Tester3::getInstance()->processEvents(event);
    }
}

void wl::game_core::update(sf::Time deltaTime)
{
    debug->update(deltaTime);
    wl::Tester1::getInstance()->update(deltaTime);
}

void wl::game_core::render()
{
    win->clear(sf::Color(22, 22, 22));
    win->draw(*debug);
    //wl::Window::getInstance()->draw(*wl::SceneManager::getInstance());
    wl::Window::getInstance()->draw(*wl::Tester1::getInstance());
    //wl::Window::getInstance()->draw(*wl::Tester2::getInstance());
    //wl::Window::getInstance()->draw(*wl::Tester3::getInstance());
    win->display();
}
