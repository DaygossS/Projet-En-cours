#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Joueur.hpp"
#include "Formation.hpp"

namespace game
{
    class World
    {
    public:
        World();
        void run();

    private:
        sf::RenderWindow window_;
        std::unique_ptr<Joueur> joueur_;
        std::unique_ptr<Formation> formation_;

        void processEvents();
        void update(float deltaTime);
        void render();
    };
}
