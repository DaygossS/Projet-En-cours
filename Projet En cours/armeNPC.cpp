#include "ArmeNPC.hpp"
#include <algorithm>
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    ArmeNPC::ArmeNPC() {}

    void ArmeNPC::tirer(const Vector2f& position)
    {
        RectangleShape laser;
        laser.setSize(Vector2f(4.f, 18.f));       // tir fin
        laser.setFillColor(Color(0, 255, 64)); // vert néon
        laser.setOutlineThickness(1.f);
        laser.setOutlineColor(Color(128, 255, 128));     // rouge impérial
        laser.setPosition(Vector2f(position.x, position.y + 10.f));
        projectiles_.push_back(laser);
    }

    void ArmeNPC::update(float deltaTime)
    {
        for (auto& projectile : projectiles_)
        {
            projectile.move(Vector2f(0.f, vitesse_ * deltaTime)); // descend
        }

        // Supprime les tirs sortis de l’écran
        projectiles_.erase(
            remove_if(projectiles_.begin(), projectiles_.end(),
                [](const RectangleShape& p)
                {
                    return p.getPosition().y > 600.f; // hauteur fenêtre
                }),
            projectiles_.end());
    }

    void ArmeNPC::draw(RenderWindow& window)
    {
        for (auto& projectile : projectiles_)
            window.draw(projectile);
        //std::cout << "Tirs NPC : " << projectiles_.size() << std::endl;
    }
}
