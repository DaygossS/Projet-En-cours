#include "Joueur.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <stdexcept>

using namespace sf;
using namespace std;

namespace game {

    Joueur::Joueur()
        : Personnage(100, 10, 250.f)
        , arme_(make_unique<Arme>(500.f, 0.25f, Color::Cyan))
    {
        chargerTexture();
        sprite_ = make_unique<Sprite>(texture_); // construction explicite avec texture
        sprite_->setPosition({ 400.f, 550.f });
    }

    void Joueur::chargerTexture() {
        if (!texture_.loadFromFile("C:\Users\Tony\source\repos\Projet En cours\x64\Debug\assets\player.png")) {
            throw runtime_error("Impossible de charger assets/player.png");
        }
    }

    void Joueur::handleInput() {
        Vector2f movement(0.f, 0.f);

        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            movement.x -= vitesse_;
        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            movement.x += vitesse_;

        sprite_->move(movement * (1.f / 60.f));

        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            arme_->tirer(sprite_->getPosition(), { 0.f, -1.f });
    }

    void Joueur::update(float deltaTime) {
        handleInput();
        arme_->update(deltaTime);

        for (auto& buff : buffsActifs_)
            buff.update(deltaTime);

        buffsActifs_.erase(remove_if(buffsActifs_.begin(), buffsActifs_.end(),
            [](const Buff& b) { return b.estExpire(); }),
            buffsActifs_.end());
    }

    void Joueur::draw(RenderTarget& target) const {
        target.draw(*sprite_);
        arme_->draw(target);
    }

    void Joueur::appliquerBuff(const Buff& buff) {
        buffsActifs_.push_back(buff);
    }

} // namespace game
