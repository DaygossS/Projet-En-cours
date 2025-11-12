#pragma once
#include "Personnage.hpp"
#include "armeNPC.hpp"
#include <memory>

namespace game
{
    class NPC : public Personnage
    {
    public:
        NPC(sf::Vector2f position);
        void update(float deltaTime) override;
        void draw(sf::RenderWindow& window) override;

        void updateControlled(float deltaTime);

        sf::Vector2f getPosition() const { return sprite_.getPosition(); }
        sf::FloatRect getGlobalBounds() const { return sprite_.getGlobalBounds(); }
        void setPosition(const sf::Vector2f& pos) { sprite_.setPosition(pos); }
        void move(const sf::Vector2f& offset) { sprite_.move(offset); }

        ArmeNPC& getArme() { return *arme_; }
        const ArmeNPC& getArme() const { return *arme_; }

        float getVie() const { return vie_; }
        void setVie(float v) { vie_ = v; }

    protected:
        std::unique_ptr<ArmeNPC> arme_;
        float direction_ = 1.f;
        float cadenceTir_ = 1.5f;
        float fireTimer_ = 0.f;
    };
}
