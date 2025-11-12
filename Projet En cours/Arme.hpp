#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace game
{
    class Arme
    {
    public:
        Arme(bool versLeHaut = true, float vitesse = 600.f);

        virtual void tirer(const sf::Vector2f& position, float scale = 1.0f);
        virtual void update(float deltaTime);
        virtual void draw(sf::RenderWindow& window);

        std::vector<sf::RectangleShape>& getProjectiles() { return projectiles_; }
        const std::vector<sf::RectangleShape>& getProjectiles() const { return projectiles_; }

    protected:
        std::vector<sf::RectangleShape> projectiles_;
        float vitesseProjectile_;
        bool versLeHaut_;
    };
}
