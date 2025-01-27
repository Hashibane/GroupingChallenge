#pragma once
#include "Point.h"

class Evaluator
{
private:
	const std::vector<NGroupingChallenge::CPoint>* points;
	std::vector<std::vector<double>> distances;
	int groups;
	int numberOfPoints;
public:
	Evaluator(const std::vector<NGroupingChallenge::CPoint>& points, int groups);
	Evaluator(const Evaluator& other);

	double evaluate(std::vector<int>& solution);	
	double evaluate(std::vector<int>&& solution);

	int lowerBound();
	int upperBound();
	const std::vector<NGroupingChallenge::CPoint>& getPoints();


	int getNumberOfPoints();

};



