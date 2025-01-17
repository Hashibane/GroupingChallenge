#include "RenderingCode.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
std::vector<sf::CircleShape> toDraw(const std::vector<NGroupingChallenge::CPoint>& points, std::vector<int>& solution, int groups)
{
    std::vector<sf::Color> colors;
    std::vector<sf::CircleShape> circles;

    for (int i = 1; i <= groups; ++i)
    {
        colors.push_back(sf::Color(255 / i , 0, 255 / i));
    }

    int j = 0;
    for (auto& i : points)
    {
        sf::CircleShape shape(pointSize);
        shape.setPosition(i.FgetCoordinates()[0]*scale, i.FgetCoordinates()[1]*scale);
        shape.setFillColor(colors[solution[j]-1]);
        circles.push_back(shape);
        ++j;
    }

    return circles;
}

void WindowManager::draw(const std::vector<NGroupingChallenge::CPoint>& points, std::vector<int>& solution, int groups)
{
    std::vector<sf::CircleShape> circles = toDraw(points, solution, groups);
    while (window.isOpen())
    {
        window.clear();
        for (auto& c : circles)
        {
            window.draw(c);
        }
        window.display();
    }

}

WindowManager::WindowManager() : window(sf::RenderWindow(sf::VideoMode(1920, 960), "SFML works!"))
{}
WindowManager::~WindowManager() 
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}