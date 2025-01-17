#include "Point.h"

using namespace NGroupingChallenge;

void CPoint::vAddCoordinate(double dCoordinate)
{
	v_coordinates.push_back(dCoordinate);
}

double CPoint::dCalculateDistance(const CPoint& cOther) const
{
	if (v_coordinates.empty() || v_coordinates.size() != cOther.v_coordinates.size())
	{
		return d_WRONG_DISTANCE_VALUE;
	}

	double d_squared_distance = 0;

	for (size_t i = 0; i < v_coordinates.size(); i++)
	{
		d_squared_distance += (v_coordinates[i] - cOther.v_coordinates[i]) * (v_coordinates[i] - cOther.v_coordinates[i]);
	}

	return sqrt(d_squared_distance);
}

const vector<double>& CPoint::FgetCoordinates() const { return v_coordinates; }

//dopisane
CPoint& CPoint::operator=(const CPoint& other)
{
	this->v_coordinates = other.v_coordinates;
	return *this;
}