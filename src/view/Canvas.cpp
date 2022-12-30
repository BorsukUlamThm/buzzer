#include "Canvas.h"

#include <utility>
#include <iostream>


void Canvas::setup()
{
    font.loadFromFile("../data/fonts/arial.ttf");

    std::string sound_dir = "../data/sounds/";
    team1_sound_buffer.loadFromFile(sound_dir + game.team1.buzz_sound_file);
    team1_sound.setBuffer(team1_sound_buffer);
    team2_sound_buffer.loadFromFile(sound_dir + game.team2.buzz_sound_file);
    team2_sound.setBuffer(team2_sound_buffer);

    if(game.musics.empty())
    { return; }
    music.openFromFile(sound_dir + game.musics[music_index]);
}

Canvas::Canvas(Game game):
    game(std::move(game))
{
    setup();
}


void Canvas::open()
{
    window.clear(sf::Color::White);
    if (window.isOpen())
    { return; }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode::getDesktopMode(),
                  "HEXA QUIZZ",
                  sf::Style::Default,
                  settings);

    size_x = float(window.getSize().x);
    size_y = float(window.getSize().y);
}

void Canvas::setup_view()
{
    float box_size = 1.0f;
    float x_min = -box_size;
    float x_max = box_size;
    float y_min = -box_size;
    float y_max = box_size;

    float window_format = size_x / size_y;
    float figure_format = (x_max - x_min) / (y_max - y_min);
    float x_length = (x_max - x_min);
    float y_length = (y_max - y_min);

    if (window_format < figure_format)
    { view.setSize(x_length, x_length / window_format); }
    else
    { view.setSize(y_length * window_format, y_length); }

    view.setCenter((x_min + x_max) / 2, (y_min + y_max) / 2);
    window.setView(view);
}

void Canvas::start_game()
{
    open();
    setup_view();
    while (window.isOpen())
    {
        handle_events();

        display_teams();

        window.display();
    }
}

void Canvas::display_teams()
{
    display_team(game.team1, true, team1_col);
    display_team(game.team2, false, team2_col);
}

void Canvas::display_team(const Team& team,
                          bool left,
                          const sf::Color& col)
{
    float xm, xM;
    float ym = -1, yM = 1;
    if(left)
    {
        xm = -10;
        xM = 0;
    }
    else
    {
        xm = 0;
        xM = 10;
    }
    display_rectangle(xm, xM, ym, yM, col);

    display_team_name(team, left);
    display_team_score(team, left);
}

void Canvas::display_rectangle(float xm, float xM,
                               float ym, float yM,
                               const sf::Color& col)
{
    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = sf::Vector2f(xm, ym);
    quad[1].position = sf::Vector2f(xm, yM);
    quad[2].position = sf::Vector2f(xM, yM);
    quad[3].position = sf::Vector2f(xM, ym);

    for(unsigned i = 0; i < 4; ++i)
    {
        quad[i].color = col;
    }

    window.draw(quad);
}

void Canvas::display_team_name(const Team &team,
                               bool left)
{
    sf::Text shape;
    shape.setFont(font);
    shape.setCharacterSize(name_font_size);
    shape.setString(team.name);

    float ratio = view.getSize().x / size_x;
    shape.setScale(ratio, ratio);
    shape.setFillColor(sf::Color::Black);

    if(left)
    {
        shape.move(-1.7, -0.5);
    }
    else
    {
        shape.move(0.1, -0.5);
    }

    window.draw(shape);
}

void Canvas::display_team_score(const Team &team,
                                bool left)
{
    sf::Text shape;
    shape.setFont(font);
    shape.setCharacterSize(score_font_size);
    shape.setString(std::to_string(team.score));

    float ratio = view.getSize().x / size_x;
    shape.setScale(ratio, ratio);
    shape.setFillColor(sf::Color::Black);

    if(left)
    {
        shape.move(-1.4, 0);
    }
    else
    {
        shape.move(0.4, 0);
    }

    window.draw(shape);
}

void Canvas::handle_events()
{
    sf::Event event {};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                size_x = float(event.size.width);
                size_y = float(event.size.height);
                setup_view();
                break;

            case sf::Event::KeyPressed:
                handle_key_pressed_event(event);
                break;

            case sf::Event::MouseButtonPressed:
                mouse_button_pressed_event(event);
                break;

            default:
                break;
        }
    }
}

void Canvas::handle_key_pressed_event(const sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Escape:
            window.clear();
            window.close();
            break;

        case sf::Keyboard::Enter:
            hard_reset();
            break;

        case sf::Keyboard::Space:
            reset();
            break;

        case sf::Keyboard::Left:
            if(music_index == 0)
            { break; }

            music_index--;
            std::cout << "music index (starting from 1) : "
            << music_index + 1 << std::endl;
            hard_reset();
            break;

        case sf::Keyboard::Right:
            if(music_index == game.musics.size  () - 1)
            { break; }

            music_index++;
            std::cout << "music index (starting from 1) : "
            << music_index + 1 << std::endl;
            hard_reset();
            break;

        case sf::Keyboard::Z:
            game.increase_team1_score();
            break;

        case sf::Keyboard::A:
            game.decrease_team1_score();
            break;

        case sf::Keyboard::S:
            game.increase_team2_score();
            break;

        case sf::Keyboard::Q:
            game.decrease_team2_score();
            break;

/*
        case sf::Keyboard::A:
            team1_buzz();
            break;

        case sf::Keyboard::P:
            team2_buzz();
            break;*/

        default:
            break;
    }
}

void Canvas::mouse_button_pressed_event(const sf::Event& event)
{
    switch (event.mouseButton.button)
    {/*
        case sf::Mouse::Left:
            increase_score(float(event.mouseButton.x));
            break;

        case sf::Mouse::Right:
            decrease_score(float(event.mouseButton.x));
            break;*/

        case sf::Mouse::Left:
            team1_buzz();
            break;

        case sf::Mouse::Right:
            team2_buzz();
            break;
/*
        case sf::Mouse::Middle:
            reset();
            break;*/

        default:
            break;
    }

}

void Canvas::team1_buzz()
{
    if(state != PENDING)
    { return; }

    music.pause();
    team1_sound.play();

    team1_col = sf::Color(255, 51, 51);
    state = BUZZED;
}

void Canvas::team2_buzz()
{
    if(state != PENDING)
    { return; }

    music.pause();
    team2_sound.play();

    team2_col = sf::Color(51, 153, 255);
    state = BUZZED;
}

void Canvas::reset()
{
    music.play();

    team1_col = sf::Color::White;
    team2_col = sf::Color::White;
    state = PENDING;
}

void Canvas::hard_reset()
{
    music.stop();
    setup();

    team1_col = sf::Color::White;
    team2_col = sf::Color::White;
    state = BLOCKED;
}

void Canvas::increase_score(float x)
{
    if(x < size_x / 2)
    {
        game.increase_team1_score();
    }
    else
    {
        game.increase_team2_score();
    }
}

void Canvas::decrease_score(float x)
{
    if(x < size_x / 2)
    {
        game.decrease_team1_score();
    }
    else
    {
        game.decrease_team2_score();
    }
}



