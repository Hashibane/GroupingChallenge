#pragma once
#include <vector>
#include <stdarg.h>
#include "ContainerQueue.hpp"
#include "Settings.hpp"
#include "MyOwnEvaluator.hpp"
template<typename Child, typename Specimen, typename Generator>
class BaseSelection
{
protected:
	Generator& generator;
	Evaluator* evaluator;
	std::vector<Specimen>* specimens;
	int specimenSize;
public:
	BaseSelection(Generator& g);
	std::vector<Specimen*> select(int k);
	void init(std::vector<Specimen>* specimens, Evaluator* e);
};

//todo : losowanie serio losowe a nie od poczatku, wybieramy k
template<typename Specimen, typename Generator = std::mt19937>
class RandomSelection : public BaseSelection<RandomSelection<Specimen, Generator>, Specimen, Generator>
{
public:
	using Base = BaseSelection<RandomSelection<Specimen, Generator>, Specimen, Generator>;
	RandomSelection(Generator& g);
	std::vector<Specimen*> select(int k);
	void init(std::vector<Specimen>* specimens, Evaluator* e);
};

template<typename Specimen, typename Generator>
class TournamentSelection : public BaseSelection<TournamentSelection<Specimen, Generator>, Specimen, Generator>
{
private:
	RandomSelection<Specimen, Generator> rs;
	//buffer
	ContainerQueue<Specimen> bests;
public:
	using Base = BaseSelection<TournamentSelection<Specimen, Generator>, Specimen, Generator>;
	TournamentSelection(Generator& g);
	std::vector<Specimen*> select(int k);
	void init(std::vector<Specimen>* specimens, Evaluator* e);
};

template<typename Specimen, typename Generator>
class MixedSelection : public BaseSelection<MixedSelection<Specimen, Generator>, Specimen, Generator>
{
private:
	TournamentSelection<Specimen, Generator> ts;
	RandomSelection<Specimen, Generator> rs;
	typename const Generator::result_type _tournamentNumber = constants::pTournament * Generator::max();
public:
	using Base = BaseSelection<MixedSelection<Specimen, Generator>, Specimen, Generator>;
	MixedSelection(Generator& g);
	std::vector<Specimen*> select(int k);
	void init(std::vector<Specimen>* specimens, Evaluator* e);
};


#include "Selection.tpp"