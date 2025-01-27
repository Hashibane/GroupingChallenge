#pragma once
#include <vector>
#include <bitset>
#include "Random.hpp"
//for future use!
/*
template<typename Child, int ResultSize>
class CrossingStrategy
{
protected:
	int size;
	std::vector<std::vector<int>>& args;
public:
	void init(int size);
	void setArgs(std::vector<std::vector)
	std::vector<std::vector<int>> cross();
};
*/

template<typename Specimen, typename Generator = std::mt19937>
class Uniform //: public CrossingStrategy<Uniform<Generator>>
{
private:
	int size;
	Randomizer < uint_fast64_t > generator;
	//buffers
	std::vector <int> newSolution;
	std::vector<int>* p1;
	std::vector<int>* p2;
public:
	Uniform(Generator& gen);
	void cross(std::vector<Specimen*>&& selected, Specimen* output);
	void init(int s);
};

template<typename Specimen>
class ThreeParents // : public CrossingStrategy<OrderCoded>
{
private:
	int size;
public:
	void cross(Specimen* begin, Specimen* end, Specimen* output);
	void init(int s);
};

#include "Breeding.tpp"