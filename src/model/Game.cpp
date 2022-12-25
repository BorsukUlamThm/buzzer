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
            team2.name = line;
            std::getline(ifs, line);
            team2.score = std::stoi(line);
            return;
        }
        else
        {
            team1.name = line;
            std::getline(ifs, line);
            team1.score = std::stoi(line);
            team1_done = true;
        }
    }
}

void Game::increase_team1_score()
{
    team1.score++;
    save_log();
}

void Game::increase_team2_score()
{
    team2.score++;
    save_log();
}

void Game::decrease_team1_score()
{
    team1.score--;
    save_log();
}

void Game::decrease_team2_score()
{
    team2.score--;
    save_log();
}

void Game::save_log() const
{
    std::ofstream ofs ("../data/logs/game");
    ofs << team1.name << std::endl
    << team1.score << std::endl
    << std::endl
    << team2.name << std::endl
    << team2.score << std::endl
    << std::endl;
}



