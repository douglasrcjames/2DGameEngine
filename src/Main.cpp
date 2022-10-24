#include "Game.h"

int main(int argc, char* argv[]) {
    Game game; // if "new" used here, this object will NOT be destroyed at the end

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}