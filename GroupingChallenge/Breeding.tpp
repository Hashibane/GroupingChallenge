#include "Breeding.hpp"

template<typename Specimen, typename Generator>
Uniform<Specimen, Generator>::Uniform(Generator& gen) : generator(gen) {}

//OrderCoded::OrderCoded(int sz) : size(sz) {}

// not thread safe! not safe at all even
template<typename Specimen, typename Generator>
void Uniform<Specimen, Generator>::cross(std::vector<Specimen*>& selected, Specimen* output)
{
	std::vector <int> newSolution( size, 0 );
	std::vector<int>* p1;
	std::vector<int>* p2;
	int it;
	for (it = 0 ; it < selected.size() - 1 ; ++it)
	{
		p1 = selected[it]->getSolutionAddr();
		p2 = selected[it+1]->getSolutionAddr();
		for (int i = 0; i < size; ++i)
		{
			if (generator())
			{
				newSolution[i] = ((*p1)[i]);
			}
			else
			{
				newSolution[i] = ((*p2)[i]);
			}
		}
		output->setSolution(newSolution);
		++output;
	} 

	p1 = selected[it]->getSolutionAddr();
	p2 = selected[0]->getSolutionAddr();
	for (int i = 0; i < size; ++i)
	{
		if (generator())
		{
			newSolution[i] = ((*p1)[i]);
		}
		else
		{
			newSolution[i] = ((*p2)[i]);
		}
	}
	output->setSolution(newSolution);
	++output;
}

template<typename Specimen, typename Generator>
void Uniform<Specimen, Generator>::init(int s)
{
	size = s;
}

template <typename Specimen>
void ThreeParents<Specimen>::cross(Specimen* begin, Specimen* end, Specimen* output)
{
	std::vector<std::vector<int>> newSolution{ size, 0 };
	int cache;

	Specimen* iterator = begin;
	Specimen* _end = end - 2;
	std::vector<int>* p1;
	std::vector<int>* p2;
	std::vector<int>* p3;
	int i = 0;
	do
	{
		// rip kod
		// todo : na pewno usprawnic, smierdzi na kilometr
		p1 = iterator->getSolution();
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cache = (*(p1 + (int)(p1+i)%3))[j];
				if (cache == (*(p1 + 2 + (int)(p1 + i) % 3))[j])
				{
					newSolution[i].push_back(cache);
				}
				else
				{
					newSolution[i].push_back((*p3)[j]);
				}
			}
			output->setSolution(newSolution);
			++output;
		}
		
		iterator += 3;
	} while (iterator < _end);


}

template<typename Specimen>
void ThreeParents<Specimen>::init(int s)
{
	size = s;
}