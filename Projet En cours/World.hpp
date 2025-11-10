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
        sf::Font font_;
        std::unique_ptr<sf::Text> vieText_;
        std::unique_ptr<sf::Text> gameOverText_;
        sf::RectangleShape vieBar_;
        sf::RectangleShape vieBarBackground_;

        bool gameOver_ = false;

        void processEvents();
        void update(float deltaTime);
        void render();
        void handleCollisions();
        void resetGame(); // redémarrage
        bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);
    };
}
