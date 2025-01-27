#pragma once

#include <queue>

template <typename Specimen>
struct Compare
{
	bool operator()(const std::pair<double, Specimen*>& l, const std::pair<double, Specimen*>& r) { return l.first < r.first; }
};

template <typename Specimen>
class ContainerQueue final : public std::priority_queue< std::pair<double, Specimen*>, std::vector<std::pair<double, Specimen*>>, Compare<Specimen >> 
{
public:
	using Base = std::priority_queue< std::pair<double, Specimen*>, std::vector<std::pair<double, Specimen*>>, Compare<Specimen >>;
	std::vector<std::pair<double, Specimen*>>& getContainer()
	{
		return Base::c;
	}
	void clear()
	{
		Base::c.clear();
	}
};