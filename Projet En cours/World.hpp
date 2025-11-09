#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Formation.hpp"
#include "Joueur.hpp"

namespace game {

    class World {
    public:
        World();
        void run();

    private:
        void update(float deltaTime);
        void render();

        sf::RenderWindow window_;
        std::unique_ptr<Joueur> joueur_;
        unique_ptr<Formation> formation_;
    };

} // namespace game

#endif // GAME_WORLD_HPP
