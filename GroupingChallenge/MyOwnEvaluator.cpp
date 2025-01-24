#include "MyOwnEvaluator.hpp"

Evaluator::Evaluator(const std::vector<NGroupingChallenge::CPoint>& points, int groups) : points(&points), groups(groups), numberOfPoints(points.size()) {}

Evaluator::Evaluator(const Evaluator& other) : points(other.points), groups(other.groups), numberOfPoints(other.numberOfPoints) {}
//TODO: Optimize evaluation
//1 - grupowanie grup odleglosciami ? Moze powinien zwracac pare (odleglosci, wynik)?
//2 - caching - tez mozna pary
double Evaluator::evaluate(std::vector<int>& solution)
{
	bool b_error = points->empty();

	double d_distance;
	double d_distance_sum = 0;

	for (size_t i = 0; i + 1 < points->size() && !b_error; i++)
	{
		if (solution[i] >= lowerBound() && solution[i] <= upperBound())
		{
			for (size_t j = i + 1; j < points->size(); j++)
			{
				if (solution[i] == solution[j])
				{
					d_distance = (*points)[i].dCalculateDistance((*points)[j]);

					if (d_distance >= 0)
					{
						d_distance_sum += 2.0 * d_distance;
					}
					else
					{
						b_error = true;
					}
				}
			}
		}
		else
		{
			b_error = true;
		}
	}

	if (b_error)
	{
		return -1;
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
