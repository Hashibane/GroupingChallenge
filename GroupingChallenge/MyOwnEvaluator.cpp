#include "MyOwnEvaluator.hpp"
#include "Settings.hpp"
#include <random>
#include <iostream>
#include <unordered_map>
Evaluator::Evaluator(const std::vector<NGroupingChallenge::CPoint>& points, int groups) : points(&points), groups(groups), numberOfPoints(points.size()), distances(std::vector<std::vector<double>>(points.size(), std::vector<double>(points.size())))
{
	double buffer;
	if (numberOfPoints < 55000)
	{
		for (int i = 0; i < numberOfPoints; ++i)
		{
			for (int j = i + 1; j < numberOfPoints; ++j)
			{
				buffer = points[i].dCalculateDistance(points[j]);
				distances[i][j] = buffer;
				distances[j][i] = buffer;
			}
		}
	}
	
}

Evaluator::Evaluator(const Evaluator& other) : points(other.points), groups(other.groups), numberOfPoints(other.numberOfPoints) {}
//TODO: Optimize evaluation
//1 - grupowanie grup odleglosciami ? Moze powinien zwracac pare (odleglosci, wynik)?
//2 - caching - tez mozna pary


double Evaluator::evaluate(std::vector<int>& solution)
{
	double d_distance_sum = 0;

	for (size_t i = 0; i + 1 < numberOfPoints; ++i)
	{
		for (size_t j = i + 1; j < numberOfPoints; ++j)
		{
			if (solution[i] == solution[j])
			{
				d_distance_sum += distances[i][j];
			}
		}
	}

	return 2*d_distance_sum;
}

double Evaluator::evaluate(std::vector<int>&& solution)
{
	double d_distance_sum = 0;
	if (numberOfPoints < 55000)
	{
		for (size_t i = 0; i + 1 < numberOfPoints; ++i)
		{
			for (size_t j = i + 1; j < numberOfPoints; ++j)
			{
				if (solution[i] == solution[j])
				{
					d_distance_sum += distances[i][j];
				}
			}
		}
	}
	else
	{
		for (size_t i = 0; i + 1 < numberOfPoints; ++i)
		{
			for (size_t j = i + 1; j < numberOfPoints; ++j)
			{
				if (solution[i] == solution[j])
				{
					d_distance_sum += (*points)[i].dCalculateDistance((*points)[j]);
				}
			}
		}
	}
	

	return d_distance_sum;
}

int Evaluator::lowerBound()
{
	return 1;
}
int Evaluator::upperBound()
{
	return groups;
}

int Evaluator::getNumberOfPoints()
{
	return numberOfPoints;
}

const std::vector<NGroupingChallenge::CPoint>& Evaluator::getPoints()
{
	return *points;
}

std::vector<int> Evaluator::getRandomSolution()
{
	std::vector<int> next(numberOfPoints, 0);
	std::vector<int> randomCenters(groups, 0);
	std::mt19937 eng;
	std::unordered_map<int, bool> map;
	int index;
	eng.seed(rand());
	
	bool bad = true;
	for (int i = 0; i < groups - 1; ++i)
	{
		while (bad)
		{
			index = eng() % numberOfPoints;
			if (map.find(index) == map.end())
			{
				randomCenters[i] = index;
				map[index] = true;
				bad = false;
			}
		}
		bad = true;
	}
	int min_gene = 1;
	double min_distance;
	double distance;
	double greedyProba = mt19937::max()*(constants::greedyProba*numberOfPoints);
	for (int i = 0; i < numberOfPoints; ++i)
	{
		if (eng() < greedyProba)
		{
			min_distance = numeric_limits<double>::max();
			for (int j = 1; j < groups; ++j)
			{
				distance = (*points)[randomCenters[j - 1]].dCalculateDistance((*points)[i]);
				if (min_distance > distance)
				{
					min_gene = j;
					min_distance = distance;
				}
			}
			next[i] = min_gene;
		}
		else
		{
			next[i] = eng() % groups;
		}
	}
	
	return next;
}