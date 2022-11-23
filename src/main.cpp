#include "libs.hpp"

#include "game.hpp"

#include "renderer.hpp"

#include "king.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "knight.hpp"
#include "pawn.hpp"

int main()
{
    Game game;
    game.initialize();

    try {
        while (game.isRunning())
        {
            game.update();
        }
    } catch (const std::exception& exception) {
        std::cerr << "Unexpected exception=" << exception.what() << '\n';
    }

    return EXIT_SUCCESS;
}
