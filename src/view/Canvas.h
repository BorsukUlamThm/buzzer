#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../model/Game.h"


class Canvas
{
protected:
    sf::RenderWindow window;
    sf::View view;

    float size_x = 0;
    float size_y = 0;

    sf::Font font;
    unsigned name_font_size = 120;
    unsigned score_font_size = 300;

    enum State
    {
        RUNNING,
        STOPPED
    };
    State state = STOPPED;

public:
    Canvas() = default;
    void display_game(const Game& game);

protected:
    void open();
    void setup_view();

    void display_teams(const Game& game);
    void display_team(const Team& team,
                      bool left,
                      const sf::Color& col);

    void display_rectangle(float xm, float xM,
                           float ym, float yM,
                           const sf::Color& col);
    void display_team_name(const Team& team,
                           bool left);
    void display_team_score(const Team& team,
                            bool left);

    void handle_events();
    void handle_key_pressed_event(const sf::Event& event);

};

