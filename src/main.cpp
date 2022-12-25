#include <iostream>
#include "model/Game.h"

int main()
{
    Game game("test");

    game.increase_team1_score();
    game.increase_team1_score();
    game.increase_team2_score();

    std::cout << "done" << std::endl;

}
