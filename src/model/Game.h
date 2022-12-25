#pragma once

#include <string>
#include <vector>

struct Team
{
    std::string name;
    int score = 0;
};


struct Game
{
    // Attributes
    Team team1;
    Team team2;

    // Constructors
    Game() = default;
    explicit Game(const std::string& file);

    // Functions
    void increase_team1_score();
    void increase_team2_score();

private:
    void save_log() const;
};

