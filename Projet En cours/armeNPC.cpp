#include "armeNPC.hpp"

using namespace sf;
using namespace game;

ArmeNPC::ArmeNPC(float vitesse)
    : Arme(false, vitesse)  // false = tir vers le bas
{
}

void ArmeNPC::tirer(const Vector2f& position, float scale)
{
    RectangleShape laser;

    // Tir rectangulaire vert orienté vers le bas
    laser.setSize(Vector2f(4.f * scale, 18.f * scale));
    laser.setFillColor(Color(0, 255, 64)); // vert néon
    laser.setOutlineThickness(1.f);
    laser.setOutlineColor(Color(128, 255, 128));
    laser.setPosition(Vector2f(position.x, position.y + 10.f));

    projectiles_.push_back(laser);
}
