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
        void showIntro();
        void showWaveMessage(const std::string& message); //  texte personnalisé entre vagues
        void processEvents();
        void update(float deltaTime);
        void render();
        void handleCollisions();
        bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);
        void loadWave(int wave);
        void resetGame();

        sf::RenderWindow window_;
        sf::Font font_;
        sf::Font titleFont_;

        std::unique_ptr<Joueur> joueur_;
        std::unique_ptr<Formation> formation_;

        std::unique_ptr<sf::Text> vieText_;
        std::unique_ptr<sf::Text> waveText_;
        std::unique_ptr<sf::Text> gameOverText_;
        std::unique_ptr<sf::Text> titleText_;
        std::unique_ptr<sf::Text> crawlText_;

        sf::RectangleShape vieBar_;
        sf::RectangleShape vieBarBackground_;

        bool introActive_ = false;
        bool gameStarted_ = false;
        bool gameOver_ = false;

        int currentWave_ = 1;
        float speedMultiplier_ = 1.f;
    };
}
