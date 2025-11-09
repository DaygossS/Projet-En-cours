#include "World.hpp"
#include <iostream>

using namespace std;
using namespace game;

int main()
{
    try
    {
        World world;
        world.run();
    }
    catch (const exception& e)
    {
        cerr << "Erreur : " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
