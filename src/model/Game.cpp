#include "Game.h"
#include <fstream>

Game::Game(const std::string &file)
{
    std::string path ("../data/games/");
    path += file;
    std::ifstream ifs(path);

    bool team1_done = false;

    std::string line;
    while(!ifs.eof())
    {
        std::getline(ifs, line);
        if(line[0] == '#')
        { continue; }
        if(line.empty())
        { continue; }

        if(team1_done)
        {
            team2_name = line;
            std::getline(ifs, line);
            team2_score = std::stoi(line);
            return;
        }
        else
        {
            team1_name = line;
            std::getline(ifs, line);
            team1_score = std::stoi(line);
            team1_done = true;
        }
    }
}

void Game::increase_team1_score()
{
    team1_score++;
    save_log();
}

void Game::increase_team2_score()
{
    team2_score++;
    save_log();
}

void Game::save_log() const
{
    std::ofstream ofs ("../data/logs/game");
    ofs << team1_name << std::endl
    << team1_score << std::endl
    << std::endl
    << team2_name << std::endl
    << team2_score << std::endl
    << std::endl;
}



