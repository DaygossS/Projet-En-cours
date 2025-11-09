#include "World.hpp"
#include "Joueur.hpp"
#include "Formation.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Color.hpp>

using namespace sf;
using namespace std;

namespace game {

    World::World()
        : window_(RenderWindow::Settings(VideoMode(800, 600), "Space Invaders - SFML 3.0.2"))
        , joueur_(make_unique<Joueur>())
        , formation_(make_unique<Formation>(80.f, 50.f, 40.f, 40.f))
    {
        window_.setFramerateLimit(60);
    }

    void World::run() {
        Clock clock;

        while (window_.isOpen()) {
            while (auto eventOpt = window_.pollEvent()) {
                const auto& event = *eventOpt;
                if (event.is<Event::Closed>())
                    window_.close();
            }

            float dt = clock.restart().asSeconds();
            update(dt);
            render();
        }
    }

    void World::update(float deltaTime) {
        joueur_->update(deltaTime);
        formation_->update(deltaTime, window_);
    }

    void World::render() {
        window_.clear(Color::Black);
        joueur_->draw(window_);
        formation_->draw(window_);
        window_.display();
    }

} // namespace game
