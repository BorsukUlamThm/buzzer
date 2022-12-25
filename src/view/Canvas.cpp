#include "Canvas.h"


void Canvas::open()
{
    font.loadFromFile("../data/fonts/arial.ttf");

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

void Canvas::display_game(const Game &game)
{
    open();
    setup_view();
    while (window.isOpen())
    {
        handle_events();

        display_teams(game);

        window.display();
    }
}

void Canvas::display_teams(const Game &game)
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

        case sf::Keyboard::A:
            team1_buzz();
            break;

        case sf::Keyboard::P:
            team2_buzz();
            break;

        case sf::Keyboard::Space:
            reset();
            break;

        default:
            break;
    }
}

void Canvas::team1_buzz()
{
    if(state == STOPPED)
    { return; }

    team1_col = sf::Color(255, 51, 51);
    state = STOPPED;
}

void Canvas::team2_buzz()
{
    if(state == STOPPED)
    { return; }

    team2_col = sf::Color(51, 153, 255);
    state = STOPPED;
}

void Canvas::reset()
{
    team1_col = sf::Color::White;
    team2_col = sf::Color::White;
    state = PENDING;
}



