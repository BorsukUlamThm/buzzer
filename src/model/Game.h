#pragma once

#include <string>
#include <vector>

class Game
{
private:
    std::string team1_name;
    std::string team2_name;
    int team1_score = 0;
    int team2_score = 0;

public:
    Game() = default;
    explicit Game(const std::string& file);

    void increase_team1_score();
    void increase_team2_score();

private:
    void save_log() const;
};

