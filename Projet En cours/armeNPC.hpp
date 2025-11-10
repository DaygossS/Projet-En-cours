#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

namespace game
{
    class ArmeNPC
    {
    public:
        ArmeNPC();

        // Tire un projectile depuis une position donnée
        void tirer(const Vector2f& position);

        // Met à jour la position des projectiles
        void update(float deltaTime);

        // Affiche les projectiles à l’écran
        void draw(RenderWindow& window);

    private:
        vector<RectangleShape> projectiles_;
        float vitesse_ = 400.f; // plus lent que le joueur
    };
}
