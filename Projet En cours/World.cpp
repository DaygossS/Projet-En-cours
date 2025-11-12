#include "World.hpp"
#include <iostream>
#include <algorithm>
#include "Enemy2.hpp"
#include "Boss.hpp"

using namespace sf;
using namespace std;

namespace game
{
    World::World()
        : window_(VideoMode({ 800u, 600u }), "Stars Invaders - SFML 3.0.2"),
        joueur_(make_unique<Joueur>())
    {
        window_.setFramerateLimit(60);

        if (!font_.openFromFile("assets/fonts/Arial.ttf"))
            cerr << "Erreur : Impossible de charger Arial.ttf\n";

        if (!titleFont_.openFromFile("assets/fonts/Starjedi.otf"))
            cerr << "Erreur : Impossible de charger Starjedi.otf\n";

        // --- HUD Vie ---
        vieText_ = make_unique<Text>(font_);
        vieText_->setString("Vie : 100");
        vieText_->setCharacterSize(24);
        vieText_->setFillColor(Color::White);
        vieText_->setPosition({ 620.f, 10.f });

        // --- HUD Vague ---
        waveText_ = make_unique<Text>(font_);
        waveText_->setString("Vague : 1");
        waveText_->setCharacterSize(24);
        waveText_->setFillColor(Color::White);
        waveText_->setPosition({ 20.f, 10.f });

        // --- Barre de vie ---
        vieBarBackground_.setSize({ 150.f, 20.f });
        vieBarBackground_.setFillColor(Color(50, 50, 50));
        vieBarBackground_.setPosition({ 620.f, 40.f });

        vieBar_.setSize({ 150.f, 20.f });
        vieBar_.setFillColor(Color::Green);
        vieBar_.setPosition({ 620.f, 40.f });

        // --- Texte Game Over ---
        gameOverText_ = make_unique<Text>(font_);
        gameOverText_->setString("GAME OVER\n\nAppuyez sur R pour rejouer");
        gameOverText_->setCharacterSize(36);
        gameOverText_->setFillColor(Color::Red);
        gameOverText_->setStyle(Text::Bold);
        {
            FloatRect gb = gameOverText_->getLocalBounds();
            gameOverText_->setOrigin({ gb.size.x / 2.f, gb.size.y / 2.f });
            gameOverText_->setPosition({ window_.getSize().x / 2.f, window_.getSize().y / 2.f });
        }

        // --- Intro - Title ---
        titleText_ = make_unique<Text>(titleFont_);
        titleText_->setString("STARS INVADERS");
        titleText_->setCharacterSize(60);
        titleText_->setFillColor(Color::Yellow);
        {
            FloatRect tb = titleText_->getLocalBounds();
            titleText_->setOrigin({ tb.size.x / 2.f, tb.size.y / 2.f });
            titleText_->setPosition({ window_.getSize().x / 2.f, window_.getSize().y / 2.f + 100.f });
        }

        // --- Intro - Crawl ---
        crawlText_ = make_unique<Text>(font_);
        crawlText_->setString(
            "Il y a bien longtemps, dans une galaxie lointaine...\n\n"
            "Les envahisseurs stellaires ont declare la guerre.\n"
            "Un seul pilote se dresse contre eux : VOUS !\n\n"
            "Defendez la Terre des vagues ennemies,\n"
            "et triomphez du redoutable BOSS final !");
        crawlText_->setCharacterSize(22);
        crawlText_->setFillColor(Color::White);
        {
            FloatRect cb = crawlText_->getLocalBounds();
            crawlText_->setOrigin({ cb.size.x / 2.f, cb.size.y / 2.f });
            crawlText_->setPosition({ window_.getSize().x / 2.f, window_.getSize().y + 100.f });
        }
    }

    void World::showIntro()
    {
        introActive_ = true;
        Clock clock;

        auto pressKey = make_unique<Text>(font_);
        pressKey->setString("Appuyez sur ESPACE pour commencer");
        pressKey->setCharacterSize(24);
        pressKey->setFillColor(Color::Cyan);
        {
            FloatRect pb = pressKey->getLocalBounds();
            pressKey->setOrigin({ pb.size.x / 2.f, pb.size.y / 2.f });
            pressKey->setPosition({ window_.getSize().x / 2.f, 500.f });
        }

        while (window_.isOpen() && introActive_)
        {
            float deltaTime = clock.restart().asSeconds();
            window_.clear(Color::Black);

            // Titre qui monte lentement
            if (titleText_->getPosition().y > 150.f)
                titleText_->move({ 0.f, -20.f * deltaTime });

            // Fondu du titre
            if (titleText_->getPosition().y < 200.f)
            {
                Color c = titleText_->getFillColor();
                if (c.a > 3)
                    c.a -= 3;
                titleText_->setFillColor(c);
            }

            // Défilement du texte façon Star Wars
            crawlText_->move({ 0.f, -40.f * deltaTime });
            float y = crawlText_->getPosition().y;
            float scale = max(0.4f, 1.0f - (700.f - y) / 1200.f);
            crawlText_->setScale({ scale, scale });
            

            window_.draw(*titleText_);
            window_.draw(*crawlText_);

            if (crawlText_->getPosition().y < 200.f)
                window_.draw(*pressKey);

            window_.display();

            while (auto eventOpt = window_.pollEvent())
            {
                const Event& event = *eventOpt;
                if (event.is<Event::Closed>())
                    window_.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                introActive_ = false;
                gameStarted_ = true;
                loadWave(1);
            }
        }
    }

    void World::run()
    {
        showIntro();
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
                resetGame();
        }
    }

    void World::update(float deltaTime)
    {
        if (gameOver_ || !gameStarted_)
            return;

        joueur_->update(deltaTime);
        if (formation_)
            formation_->update(deltaTime);

        if (currentWave_ == 1) speedMultiplier_ = 1.f;
        else if (currentWave_ == 2) speedMultiplier_ = 1.25f;
        else if (currentWave_ == 3) speedMultiplier_ = 1.5f;
        else if (currentWave_ == 4) speedMultiplier_ = 1.2f;
        else speedMultiplier_ = 0.9f;

        if (formation_) formation_->setSpeedMultiplier(speedMultiplier_);

        handleCollisions();

        if (formation_)
        {
            auto& npcs = formation_->getNPCs();
            for (auto& npc : npcs)
            {
                float bottom = npc->getGlobalBounds().position.y + npc->getGlobalBounds().size.y;
                if (bottom >= window_.getSize().y - 50.f)
                {
                    gameOver_ = true;
                    break;
                }
            }
        }

        int vie = static_cast<int>(joueur_->getVie());
        vieText_->setString("Vie : " + to_string(vie));
        float ratio = vie / 100.f;
        vieBar_.setSize({ 150.f * ratio, 20.f });
        vieBar_.setFillColor(ratio > 0.3f ? Color::Green : Color::Red);

        if (joueur_->getVie() <= 0.f)
            gameOver_ = true;

        if (formation_ && formation_->getNPCs().empty() && !gameOver_)
        {
            currentWave_++;
            if (currentWave_ > 5)
            {
                gameOver_ = true;
                gameOverText_->setString("VICTOIRE !\n\nAppuyez sur R pour rejouer");
            }
            else
                loadWave(currentWave_);

            waveText_->setString("Vague : " + to_string(currentWave_));
        }
    }

    void World::loadWave(int wave)
    {
        formation_.reset();

        switch (wave)
        {
        case 1:
            formation_ = make_unique<Formation>(8, 3, Vector2f(100.f, 50.f), 80.f, 60.f);
            break;
        case 2:
            formation_ = make_unique<Formation>(9, 4, Vector2f(80.f, 50.f), 70.f, 60.f);
            formation_->getNPCs().push_back(make_unique<Enemy2>(Vector2f(400.f, 100.f)));
            break;
        case 3:
            formation_ = make_unique<Formation>(8, 3, Vector2f(100.f, 60.f), 80.f, 55.f);
            for (int i = 0; i < 3; ++i)
                formation_->getNPCs().push_back(make_unique<Enemy2>(Vector2f(150.f + i * 200.f, 140.f)));
            break;
        case 4:
            formation_ = make_unique<Formation>(8, 1, Vector2f(100.f, 80.f), 80.f, 55.f);
            formation_->getNPCs().clear();
            for (int i = 0; i < 8; ++i)
                formation_->getNPCs().push_back(make_unique<Enemy2>(Vector2f(100.f + i * 80.f, 100.f)));
            break;
        case 5:
            formation_ = make_unique<Formation>(0, 0, Vector2f(0.f, 0.f), 0.f, 0.f);
            formation_->getNPCs().push_back(make_unique<Boss>(Vector2f(400.f, 80.f)));
            for (int i = 0; i < 4; ++i)
                formation_->getNPCs().push_back(make_unique<Enemy2>(Vector2f(280.f + i * 80.f, 200.f)));
            break;
        default:
            formation_ = make_unique<Formation>(8, 3, Vector2f(100.f, 50.f), 80.f, 60.f);
            break;
        }
    }

    void World::resetGame()
    {
        joueur_ = make_unique<Joueur>();
        formation_.reset();
        currentWave_ = 1;
        gameOver_ = false;
        introActive_ = true;
        gameStarted_ = false;
        if (waveText_) waveText_->setString("Vague : 1");
        if (vieText_) vieText_->setString("Vie : 100");
        showIntro();
    }

    void World::render()
    {
        window_.clear(Color::Black);

        if (formation_) formation_->draw(window_);
        joueur_->draw(window_);

        window_.draw(vieBarBackground_);
        window_.draw(vieBar_);
        window_.draw(*vieText_);
        window_.draw(*waveText_);

        if (gameOver_) window_.draw(*gameOverText_);

        window_.display();
    }

    void World::handleCollisions()
    {
        if (!formation_) return;

        auto& tirsJoueur = joueur_->getArme().getProjectiles();
        auto& npcs = formation_->getNPCs();

        for (auto it = tirsJoueur.begin(); it != tirsJoueur.end();)
        {
            bool hit = false;
            for (auto& npc : npcs)
            {
                if (checkCollision(it->getGlobalBounds(), npc->getGlobalBounds()))
                {
                    npc->setVie(npc->getVie() - joueur_->getDegats());
                    it = tirsJoueur.erase(it);
                    hit = true;
                    break;
                }
            }
            if (!hit) ++it;
        }

        npcs.erase(remove_if(npcs.begin(), npcs.end(),
            [](const unique_ptr<NPC>& n) { return n->getVie() <= 0.f; }),
            npcs.end());

        for (auto& npc : npcs)
        {
            auto& tirsNPC = npc->getArme().getProjectiles();
            for (auto it = tirsNPC.begin(); it != tirsNPC.end();)
            {
                if (checkCollision(it->getGlobalBounds(), joueur_->getGlobalBounds()))
                {
                    joueur_->setVie(joueur_->getVie() - npc->getDegats());
                    it = tirsNPC.erase(it);
                }
                else
                    ++it;
            }
        }

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
        Vector2f aMin = a.position;
        Vector2f aMax = a.position + a.size;
        Vector2f bMin = b.position;
        Vector2f bMax = b.position + b.size;

        return (aMin.x < bMax.x && aMax.x > bMin.x &&
            aMin.y < bMax.y && aMax.y > bMin.y);
    }
}
