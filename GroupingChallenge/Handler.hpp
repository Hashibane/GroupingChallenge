#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Point.h"
struct Handler
{
	int dim = 2;
	std::ifstream file;
	Handler(std::string path)
	{
		file.open(path);
	}
	std::vector<NGroupingChallenge::CPoint> read()
	{
		std::vector<NGroupingChallenge::CPoint> points;
        std::string line;
		double buff;
		std::string token;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			NGroupingChallenge::CPoint p;
			for (int i = 0; i < dim; ++i)
			{
				std::getline(ss, token, ',');
				std::stringstream(token) >> buff;
				p.vAddCoordinate(buff);
			}
			points.push_back(p);
		}

 
		file.close();
		return points;
	}
	
};