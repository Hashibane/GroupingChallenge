#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <vector>

constexpr const float pointSize = 3.;
constexpr const float scale = 10;
std::vector<sf::CircleShape> toDraw(const std::vector<NGroupingChallenge::CPoint>& points, std::vector<int>& soulution, int groups);

class WindowManager
{
private:
	sf::RenderWindow window;
public:
	WindowManager();
	~WindowManager();
	void draw(const std::vector<NGroupingChallenge::CPoint>& points, std::vector<int>& soulution, int groups);
};

