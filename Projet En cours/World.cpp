#include "World.hpp"
#include <algorithm>
#include <iostream>

using namespace sf;
using namespace std;

namespace game
{
    World::World()
        : window_(VideoMode({ 800, 600 }), "Space Invaders - SFML 3.0.2"),
        joueur_(make_unique<Joueur>()),
        formation_(make_unique<Formation>(6, 4, Vector2f(100.f, 100.f), 90.f, 70.f))
    {
        window_.setFramerateLimit(60);

        if (!font_.openFromFile("assets/fonts/Arial.ttf"))
        {
            cerr << "Erreur : Impossible de charger la police arial.ttf\n";
        }

        // --- Texte de vie (construction SFML 3.0.2 compatible) ---
        vieText_ = make_unique<Text>(font_);
        vieText_->setString("Vie : 100");
        vieText_->setCharacterSize(24);
        vieText_->setFillColor(Color::White);
        vieText_->setPosition(Vector2f(620.f, 10.f));

        // --- Barre de vie ---
        vieBarBackground_.setSize(Vector2f(150.f, 20.f));
        vieBarBackground_.setFillColor(Color(50, 50, 50));
        vieBarBackground_.setPosition(Vector2f(620.f, 40.f));

        vieBar_.setSize(Vector2f(150.f, 20.f));
        vieBar_.setFillColor(Color::Green);
        vieBar_.setPosition(Vector2f(620.f, 40.f));

        // --- Texte Game Over (construction SFML 3.0.2 compatible) ---
        gameOverText_ = make_unique<Text>(font_);
        gameOverText_->setString("GAME OVER\n\nAppuyez sur R pour rejouer");
        gameOverText_->setCharacterSize(36);
        gameOverText_->setFillColor(Color::Red);
        gameOverText_->setStyle(Text::Bold);

        FloatRect gb = gameOverText_->getLocalBounds();
        gameOverText_->setOrigin(Vector2f(gb.size.x / 2.f, gb.size.y / 2.f));
        gameOverText_->setPosition(Vector2f(window_.getSize().x / 2.f, window_.getSize().y / 2.f));
    }

    void World::run()
    {
        Clock clock;
        while (window_.isOpen())
        {
            processEvents();
            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
            render();
        }
    }

    void World::processEvents()
    {
        while (auto eventOpt = window_.pollEvent())
        {
            const Event& event = *eventOpt;
            if (event.is<Event::Closed>())
                window_.close();

            if (gameOver_ && Keyboard::isKeyPressed(Keyboard::Key::R))
            {
                resetGame();
            }
        }
    }

    void World::update(float deltaTime)
    {
        if (gameOver_)
            return;

        joueur_->update(deltaTime);
        formation_->update(deltaTime);
        handleCollisions();

        // --- Actualisation HUD ---
        int vie = static_cast<int>(joueur_->getVie());
        vieText_->setString("Vie : " + to_string(vie));

        float ratio = vie / 100.f;
        vieBar_.setSize(Vector2f(150.f * ratio, 20.f));
        vieBar_.setFillColor(ratio > 0.3f ? Color::Green : Color::Red);

        if (joueur_->getVie() <= 0.f)
            gameOver_ = true;
    }

    void World::render()
    {
        window_.clear(Color::Black);

        formation_->draw(window_);
        joueur_->draw(window_);

        // HUD
        window_.draw(vieBarBackground_);
        window_.draw(vieBar_);
        window_.draw(*vieText_);

        if (gameOver_)
            window_.draw(*gameOverText_);

        window_.display();
    }

    void World::handleCollisions()
    {
        auto& tirsJoueur = joueur_->getArme().getProjectiles();
        auto& npcs = formation_->getNPCs();

        // --- Collisions tirs joueur / NPC ---
        for (auto itTir = tirsJoueur.begin(); itTir != tirsJoueur.end(); )
        {
            bool hit = false;
            for (auto& npc : npcs)
            {
                if (checkCollision(itTir->shape.getGlobalBounds(), npc->getGlobalBounds()))
                {
                    npc->setVie(npc->getVie() - joueur_->getDegats());
                    itTir = tirsJoueur.erase(itTir);
                    hit = true;
                    break;
                }
            }
            if (!hit)
                ++itTir;
        }

        // Supprimer NPC morts
        npcs.erase(remove_if(npcs.begin(), npcs.end(),
            [](const unique_ptr<NPC>& npc) { return npc->getVie() <= 0.f; }),
            npcs.end());

        // --- Collisions tirs NPC / Joueur ---
        for (auto& npc : npcs)
        {
            auto& tirsNPC = npc->getArme().getProjectiles();
            for (auto itTir = tirsNPC.begin(); itTir != tirsNPC.end(); )
            {
                if (checkCollision(itTir->shape.getGlobalBounds(), joueur_->getGlobalBounds()))
                {
                    joueur_->setVie(joueur_->getVie() - npc->getDegats());
                    itTir = tirsNPC.erase(itTir);
                }
                else
                    ++itTir;
            }
        }

        // --- Collision directe joueur / NPC ---
        for (auto& npc : npcs)
        {
            if (checkCollision(joueur_->getGlobalBounds(), npc->getGlobalBounds()))
            {
                joueur_->setVie(0.f);
                gameOver_ = true;
                return;
            }
        }
    }

    bool World::checkCollision(const FloatRect& a, const FloatRect& b)
    {
        Vector2f aMin(a.position.x, a.position.y);
        Vector2f aMax(a.position.x + a.size.x, a.position.y + a.size.y);
        Vector2f bMin(b.position.x, b.position.y);
        Vector2f bMax(b.position.x + b.size.x, b.position.y + b.size.y);

        return (aMin.x < bMax.x && aMax.x > bMin.x &&
            aMin.y < bMax.y && aMax.y > bMin.y);
    }

    void World::resetGame()
    {
        joueur_ = make_unique<Joueur>();
        formation_ = make_unique<Formation>(6, 4, Vector2f(100.f, 100.f), 90.f, 70.f);
        gameOver_ = false;
    }
}
