#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <vector>

constexpr const float pointSize = 3.;
std::vector<sf::CircleShape> toDraw(const std::vector<NGroupingChallenge::CPoint>& points, std::vector<int>& soulution, int groups);

