#include "Joueur.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>

using namespace sf;
using namespace std;

namespace game
{
    Joueur::Joueur()
        : Personnage(100.f, 10.f, 200.f)
    {
        if (!texture_.loadFromFile("assets/player.png"))
        {
            throw runtime_error("Impossible de charger assets/player.png");
        }

        sprite_ = Sprite(texture_);
        sprite_.setScale(Vector2f(0.07f, 0.07f));

        // Calcule la taille du sprite
        auto rect = sprite_.getTextureRect();
        Vector2f spriteSize(rect.position.x * sprite_.getScale().x,
            rect.position.y * sprite_.getScale().y);

        // Position centrée horizontalement
        sprite_.setPosition(Vector2f{ 400.f - spriteSize.x / 20.f, 550.f });
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

        // --- Tir automatique double-canon ---
        static sf::Clock tirClock; // contrôle la cadence
        static bool leftSide = true; // alterne les côtés du vaisseau

        if (tirClock.getElapsedTime().asSeconds() > 0.2f) // cadence de tir (ajuste selon ton goût)
        {
            auto rect = sprite_.getTextureRect();
            sf::Vector2f spriteSize(
                rect.size.x * sprite_.getScale().x,
                rect.size.y * sprite_.getScale().y
            );

            // Position du tir : gauche ou droite du vaisseau
            sf::Vector2f spawnPos(
                sprite_.getPosition().x + (leftSide ? 8.f : spriteSize.x - 12.f),
                sprite_.getPosition().y - 8.f
            );

            arme_.tirer(spawnPos);

            leftSide = !leftSide;      // alterne pour le tir suivant
            tirClock.restart();        // remet le compteur à zéro
        }


    }


    void Joueur::update(float deltaTime)
    {
        handleInput(deltaTime);
        arme_.update(deltaTime);

        const float windowWidth = 800.f;
        const float windowHeight = 600.f;

        auto rect = sprite_.getTextureRect();
        float spriteWidth = static_cast<float>(rect.size.x) * sprite_.getScale().x;
        float spriteHeight = static_cast<float>(rect.size.y) * sprite_.getScale().y;

        Vector2f pos = sprite_.getPosition();

        // Empêche le joueur de sortir de la fenêtre
        pos.x = std::clamp(pos.x, 0.f, windowWidth - spriteWidth);
        pos.y = std::clamp(pos.y, 0.f, windowHeight - spriteHeight);

        sprite_.setPosition(pos);
    }

    void Joueur::draw(RenderWindow& window)
    {
        window.draw(sprite_);
        arme_.draw(window);
    }
}