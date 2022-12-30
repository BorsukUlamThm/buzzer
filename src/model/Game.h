#pragma once

#include <string>
#include <vector>

struct Team
{
    std::string name;
    int score = 0;
    std::string buzz_sound_file;
};


struct Game
{
    // Attributes
    Team team1;
    Team team2;

    std::vector<std::string> musics;

    // Constructors
    Game() = default;
    explicit Game(const std::string& file);

    // Functions
    void increase_team1_score();
    void increase_team2_score();
    void decrease_team1_score();
    void decrease_team2_score();

private:
    void save_log() const;
};

