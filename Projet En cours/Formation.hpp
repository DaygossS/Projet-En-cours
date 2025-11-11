#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "NPC.hpp"

using namespace sf;
using namespace std;

namespace game
{
    class Formation
    {
    public:
        // --- Constructeur complet (5 paramètres) ---
        Formation(unsigned int cols, unsigned int rows, Vector2f startPos, float spacingX, float spacingY);

        void update(float deltaTime);
        void draw(RenderWindow& window);

        // Accès aux NPC
        vector<unique_ptr<NPC>>& getNPCs() { return npcs_; }

    private:
        vector<unique_ptr<NPC>> npcs_;
        float vitesse_ = 60.f;
        float direction_ = 1.f;
        float descente_ = 20.f;
    };
}
