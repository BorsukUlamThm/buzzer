#include "model/Game.h"
#include "view/Canvas.h"

int main()
{
    Game game("test");

    Canvas canvas(game);
    canvas.start_game();
}
