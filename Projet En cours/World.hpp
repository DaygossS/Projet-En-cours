#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

namespace game
{
    class World
    {
    public:
        World();
        void run();

    private:
        RenderWindow window_;
        void processEvents();
        void update(float deltaTime);
        void render();
    };
}
