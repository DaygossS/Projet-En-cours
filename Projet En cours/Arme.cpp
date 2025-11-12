#include "Arme.hpp"
#include <algorithm>

using namespace sf;
using namespace game;

Arme::Arme(bool versLeHaut, float vitesse)
    : versLeHaut_(versLeHaut),
    vitesseProjectile_(vitesse)
{
}

void Arme::tirer(const Vector2f& position, float scale)
{
    RectangleShape laser;
    laser.setSize(Vector2f(3.f * scale, 18.f * scale));
    laser.setFillColor(versLeHaut_ ? Color::Red : Color(0, 255, 64));
    laser.setOutlineThickness(0.3f);
    laser.setOutlineColor(Color::Red);
    laser.setPosition(position);

    projectiles_.push_back(laser);
}

void Arme::update(float deltaTime)
{
    const float direction = versLeHaut_ ? -1.f : 1.f;

    for (auto& projectile : projectiles_)
        projectile.move(sf::Vector2f(0.f, vitesseProjectile_ * deltaTime * direction));

    projectiles_.erase(
        std::remove_if(projectiles_.begin(), projectiles_.end(),
            [direction](const RectangleShape& p)
            {
                const float y = p.getPosition().y;
                return (direction < 0.f && y < -20.f) || (direction > 0.f && y > 600.f);
            }),
        projectiles_.end());
}

void Arme::draw(RenderWindow& window)
{
    for (auto& projectile : projectiles_)
        window.draw(projectile);
}
