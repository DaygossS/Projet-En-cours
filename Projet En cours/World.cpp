#include "World.hpp"

using namespace sf;
using namespace std;

namespace game
{
    World::World()
        : window_(RenderWindow(VideoMode({ 800, 600 }), "Space Invaders - SFML 3.0.2")),
        joueur_(make_unique<Joueur>())
    {
        window_.setFramerateLimit(60);
    }

    void World::run()
    {
        Clock clock;

        while (window_.isOpen())
        {
            processEvents();
            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
            render();
        }
    }

    void World::processEvents()
    {
        while (auto eventOpt = window_.pollEvent())
        {
            const Event& event = *eventOpt;
            if (event.is<Event::Closed>())
                window_.close();
        }
    }

    void World::update(float deltaTime)
    {
        joueur_->update(deltaTime);
    }

    void World::render()
    {
        window_.clear(Color::Black);
        joueur_->draw(window_);
        window_.display();
    }
}
