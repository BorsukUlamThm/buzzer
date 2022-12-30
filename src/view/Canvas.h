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
    Game game;

    float size_x = 0;
    float size_y = 0;

    sf::Font font;
    unsigned name_font_size = 120;
    unsigned score_font_size = 300;

    sf::Color team1_col = sf::Color::White;
    sf::Color team2_col = sf::Color::White;

    enum State
    {
        BLOCKED,
        PENDING,
        BUZZED
    };
    State state = BLOCKED;

    sf::SoundBuffer team1_sound_buffer;
    sf::SoundBuffer team2_sound_buffer;
    sf::Sound team1_sound;
    sf::Sound team2_sound;
    sf::Music music;

public:
    Canvas() = default;
    explicit Canvas(Game game);
    void start_game();

protected:
    void setup();
    void open();
    void setup_view();

    void display_teams();
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
    void mouse_button_pressed_event(const sf::Event& event);

    void team1_buzz();
    void team2_buzz();
    void reset();
    void hard_reset();

    void increase_score(float x);
    void decrease_score(float x);
};

