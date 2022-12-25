#include <iostream>
#include "model/Game.h"
#include "view/Canvas.h"

int main()
{
    Game game("test");

    game.increase_team1_score();
    game.increase_team1_score();
    game.increase_team2_score();

    Canvas canvas;
    canvas.display_game(game);

}
