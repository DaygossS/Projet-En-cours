#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

namespace game
{
    class Arme
    {
    public:
        struct Projectile
        {
            RectangleShape shape;
            float vitesse = 0.f;
        };

        // versLeHaut = true -> joueur (rouge, monte)
        // versLeHaut = false -> NPC (vert, descend)
        explicit Arme(bool versLeHaut = true);

        // crée un projectile à la position donnée
        void tirer(const Vector2f& position);

        // met à jour tous les projectiles
        void update(float deltaTime);

        // dessine tous les projectiles
        void draw(RenderWindow& window) const;

        std::vector<Projectile>& getProjectiles() { return projectiles_; }
        
        const std::vector<Projectile>& getProjectiles() const { return projectiles_; }

    private:
        vector<Projectile> projectiles_;
        bool versLeHaut_;   // direction logique des projectiles
        float vitesseProjectile_ = 400.f;
    };
}
