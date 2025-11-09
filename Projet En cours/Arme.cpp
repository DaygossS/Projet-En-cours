#include "Arme.hpp"
#include <algorithm>

using namespace sf;
using namespace std;

namespace game {

    Arme::Arme(float vitesseProjectile, float cadenceTir, Color couleurProjectile)
        : vitesseProjectile_(vitesseProjectile)
        , cadenceTir_(cadenceTir)
        , couleurProjectile_(couleurProjectile)
        , tempsDepuisDernierTir_(0.f)
    {
    }

    void Arme::tirer(const Vector2f& position, const Vector2f& direction) {
        if (horloge_.getElapsedTime().asSeconds() >= cadenceTir_) {
            CircleShape projectile(5.f);
            projectile.setFillColor(couleurProjectile_);
            projectile.setPosition(position);
            projectiles_.push_back(projectile);
            directions_.push_back(direction);
            horloge_.restart();
        }
    }

    void Arme::update(float deltaTime) {
        for (size_t i = 0; i < projectiles_.size(); ++i) {
            Vector2f movement = directions_[i] * vitesseProjectile_ * deltaTime;
            projectiles_[i].move(movement);  // ✅ version SFML 3
        }

        // Suppression des projectiles hors écran
        for (size_t i = 0; i < projectiles_.size();) {
            if (projectiles_[i].getPosition().y < 0) {
                projectiles_.erase(projectiles_.begin() + i);
                directions_.erase(directions_.begin() + i);
            }
            else {
                ++i;
            }
        }
    }

    void Arme::draw(RenderTarget& target) const {
        for (const auto& projectile : projectiles_) {
            target.draw(projectile);
        }
    }

} // namespace game
