#include "Arme.hpp"
#include <algorithm>

using namespace sf;
using namespace std;

namespace game
{
    Arme::Arme(bool versLeHaut)
        : versLeHaut_(versLeHaut)
    {
        // vitesseProjectile_ déjà initialisée dans l'en-tête
    }

    void Arme::tirer(const Vector2f& position)
    {
        Projectile p;
        p.shape.setSize(Vector2f(3.f, 14.f));
        p.shape.setFillColor(versLeHaut_ ? Color::Red : Color::Green);
        p.shape.setPosition(position);
        p.vitesse = versLeHaut_ ? -vitesseProjectile_ : vitesseProjectile_;
        projectiles_.push_back(std::move(p));
    }

    void Arme::update(float deltaTime)
    {
        // déplacer
        for (auto& p : projectiles_)
        {
            p.shape.move(Vector2f(0.f, p.vitesse * deltaTime));
        }

        // nettoyage des projectiles hors écran (hauteur fenêtre 600)
        projectiles_.erase(
            std::remove_if(projectiles_.begin(), projectiles_.end(),
                [](const Projectile& pr)
                {
                    float y = pr.shape.getPosition().y;
                    return (y < -50.f || y > 650.f);
                }),
            projectiles_.end()
        );
    }

    void Arme::draw(RenderWindow& window) const
    {
        for (const auto& p : projectiles_)
            window.draw(p.shape);
    }
}
