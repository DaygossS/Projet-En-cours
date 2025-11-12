#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
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
        // --- Boucle principale ---
        void processEvents();
        void update(float deltaTime);
        void render();

        // --- Logique ---
        void handleCollisions();
        bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);
        void loadWave(int wave);
        void resetGame();
        void showIntro();

        // --- Données principales ---
        sf::RenderWindow window_;
        std::unique_ptr<Joueur> joueur_;
        std::unique_ptr<Formation> formation_;

        // --- HUD ---
        std::unique_ptr<sf::Text> vieText_;
        std::unique_ptr<sf::Text> waveText_;
        std::unique_ptr<sf::Text> gameOverText_;
        sf::RectangleShape vieBar_;
        sf::RectangleShape vieBarBackground_;

        // --- Police et polices spéciales ---
        sf::Font font_;
        sf::Font titleFont_;

        // --- Intro Star Wars ---
        bool introActive_ = true;
        std::unique_ptr<sf::Text> titleText_;
        std::unique_ptr<sf::Text> crawlText_;

        // --- État du jeu ---
        bool gameStarted_ = false;
        bool gameOver_ = false;
        int currentWave_ = 1;
        float speedMultiplier_ = 1.f;
    };
}
