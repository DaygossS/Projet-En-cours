#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "NPC.hpp"

namespace game
{
    class Formation
    {
    public:
        Formation(); //  constructeur par défaut
        Formation(unsigned int cols, unsigned int rows, sf::Vector2f startPos, float spacingX, float spacingY);

        void update(float deltaTime);
        void draw(sf::RenderWindow& window);

    private:
        float direction_ = 1.f; // 1 = droite, -1 = gauche
        float vitesse_ = 50.f;
        float descente_ = 20.f;
        std::vector<std::unique_ptr<NPC>> npcs_;
    };
}
