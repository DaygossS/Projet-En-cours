#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Joueur.hpp"
#include "Formation.hpp"

using namespace sf;
using namespace std;

namespace game
{
    class World
    {
    public:
        World();
        void run();

    private:
        RenderWindow window_;
        Font font_;

        unique_ptr<Joueur> joueur_;
        unique_ptr<Formation> formation_;

        // Textes dynamiques (SFML 3.0.2 compatible)
        unique_ptr<Text> vieText_;
        unique_ptr<Text> introText_;
        unique_ptr<Text> gameOverText_;

        RectangleShape vieBar_;
        RectangleShape vieBarBackground_;

        bool gameOver_ = false;
        bool showIntro_ = true;
        bool gameStarted_ = false;

        void processEvents();
        void update(float deltaTime);
        void render();
        void handleCollisions();
        void resetGame();
        void showIntro();
        void loadWave(int wave);
        bool checkCollision(const FloatRect& a, const FloatRect& b);
    };
}
