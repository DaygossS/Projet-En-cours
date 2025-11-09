#include "World.hpp"

#include <iostream>
#include <exception>

using namespace sf;
using namespace std;
using namespace game;

int main() {
    try {
        World world;
        world.run();
    }
    catch (const exception& e) {
        cerr << "Erreur fatale : " << e.what() << endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        cerr << "Erreur inconnue." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
