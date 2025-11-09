#include "Joueur.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>

using namespace sf;
using namespace std;

namespace game
{
    Joueur::Joueur()
        : Personnage(100.f, 10.f, 300.f)
    {
        if (!texture_.loadFromFile("assets/player.png"))
        {
            throw runtime_error("Impossible de charger assets/player.png");
        }

        sprite_ = Sprite(texture_);

        // Calcule la taille du sprite
        auto rect = sprite_.getTextureRect();
        Vector2f spriteSize(rect.position.x * sprite_.getScale().x,
            rect.position.y * sprite_.getScale().y);

        // Position centrée horizontalement
        sprite_.setPosition(Vector2f{ 0.f - spriteSize.x / 20.f, 50.f });
    }


    void Joueur::handleInput(float deltaTime)
    {
        Vector2f movement(0.f, 0.f);

        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            movement.x -= vitesse_ * deltaTime;
        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            movement.x += vitesse_ * deltaTime;
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            movement.y -= vitesse_ * deltaTime;
        if (Keyboard::isKeyPressed(Keyboard::Key::Down))
            movement.y += vitesse_ * deltaTime;

        sprite_.move(movement);
    }

    void Joueur::update(float deltaTime)
    {
        handleInput(deltaTime);
    }

    void Joueur::draw(RenderWindow& window)
    {
        window.draw(sprite_);
    }
}
