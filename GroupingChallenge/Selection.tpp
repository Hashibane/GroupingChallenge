#include "Selection.hpp"

template<typename Child, typename Specimen, typename Generator>
BaseSelection<Child, Specimen, Generator>::BaseSelection(Generator& g) : generator(g), evaluator(nullptr) {}

template<typename Child, typename Specimen, typename Generator>
std::vector<Specimen*> BaseSelection<Child, Specimen, Generator>::select(int k)
{
	static_cast<Child*>(this)->select(k);
}

template<typename Child, typename Specimen, typename Generator>
void BaseSelection<Child, Specimen, Generator>::init(std::vector<Specimen>* specimens, Evaluator* e)
{
	evaluator = e;
	this->specimens = specimens;
	this->specimenSize = specimens->size();
}

template<typename Specimen, typename Generator>
RandomSelection<Specimen, Generator>::RandomSelection(Generator& g) : Base(g) {}


template<typename Specimen, typename Generator>
std::vector<Specimen*> RandomSelection<Specimen, Generator>::select(int k)
{
	std::vector<Specimen*> result{};
	result.reserve(Base::specimenSize);
	int index;
	while (result.size() != k)
	{
		index = Base::generator() % Base::specimenSize;
		result.push_back(&(*Base::specimens)[index]);

	}
	return result;
}


template<typename Specimen, typename Generator>
void RandomSelection<Specimen, Generator>::init(std::vector<Specimen>* specimens, Evaluator* e)
{
	Base::init(specimens, e);
}

template<typename Specimen, typename Generator>
TournamentSelection<Specimen, Generator>::TournamentSelection(Generator& g) : Base(g), rs(g) {}

//todo : kolejka priorytetowa najlepszych!
template<typename Specimen, typename Generator>
std::vector<Specimen*> TournamentSelection<Specimen, Generator>::select(int k)
{
	std::vector<Specimen*> specimens;
	std::vector<Specimen*> result;
	int specSize = specimens.size();

	double buff;
	int selected = 0;
	auto container = bests.getContainer();
	while (true)
	{
		bests.clear();
		specimens = rs.select(constants::tournamentSize);
		for (auto i : specimens)
		{
			buff = i->getScore();
			if (bests.size() == constants::tournamentWinners)
			{
				if (bests.top().first > buff)
				{
					bests.pop();
					bests.emplace(buff, i);
				}
			}
			else
			{
				bests.emplace(buff, i);
			}
		}

	
		result.reserve(constants::tournamentWinners);
		container = bests.getContainer();
		for (auto& i : container)
		{
			result.push_back(i.second);
			if (++selected >= k)
				return result;
		}
	}
	return result;
}

template<typename Specimen, typename Generator>
void TournamentSelection<Specimen, Generator>::init(std::vector<Specimen>* specimens, Evaluator* e)
{
	rs.init(specimens, e);
	Base::init(specimens, e);
}


template<typename Specimen, typename Generator>
MixedSelection<Specimen, Generator>::MixedSelection(Generator& g) : Base(g), ts(g), rs(g) {}

//todo : zamienic na stale!
template<typename Specimen, typename Generator>
std::vector<Specimen*> MixedSelection<Specimen, Generator>::select(int k)
{
	if (Base::generator() > _tournamentNumber)
	{
		return rs.select(k);
	}
	else
	{
		return ts.select(k);
	}
}

template<typename Specimen, typename Generator>
void MixedSelection<Specimen, Generator>::init(std::vector<Specimen>* specimens, Evaluator* e)
{
	ts.init(specimens, e);
	rs.init(specimens, e);
	Base::init(specimens, e);
}
