#include "MyOwnEvaluator.hpp"
#include <iostream>
Evaluator::Evaluator(const std::vector<NGroupingChallenge::CPoint>& points, int groups) : points(&points), groups(groups), numberOfPoints(points.size()), distances(std::vector<std::vector<double>>(points.size(), std::vector<double>(points.size())))
{
	double buffer;
	for (int i = 0; i < numberOfPoints; ++i)
	{
		for (int j = i+1; j < numberOfPoints; ++j)
		{
			buffer = points[i].dCalculateDistance(points[j]);
			distances[i][j] = buffer;
			distances[j][i] = buffer;
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

	return 2 * d_distance_sum;
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
