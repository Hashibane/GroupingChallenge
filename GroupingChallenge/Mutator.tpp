#include "Mutator.hpp"


template <typename Child, typename Specimen, typename Generator>
BaseMutator<Child, Specimen, Generator>::BaseMutator(Generator& g) : generator(g) {}

template <typename Child, typename Specimen, typename Generator>
void BaseMutator<Child, Specimen, Generator>::mutate(std::vector<Specimen>& specimens)
{
	static_cast<Child*>(this)->mutate(specimens);
}

template <typename Child, typename Specimen, typename Generator>
void BaseMutator<Child, Specimen, Generator>::init(int size, int upperBound)
{
	this->size = size;
	this->upperBound = upperBound;
}

template <typename Specimen, typename Generator>
BasicMutator<Specimen, Generator>::BasicMutator(Generator& g) : Base(g) {}

template <typename Specimen, typename Generator>
void BasicMutator<Specimen, Generator>::mutate(std::vector<Specimen>& specimens)
{
	for (auto& i : specimens)
	{
		if (Base::generator() < _mutationNumber)
		{
			auto& solution = *(i.getSolutionAddr());
			for (int j = 0 ; j < Base::size ; ++j)
			{
				if (Base::generator() < _geneNumber)
				{
					solution[j] = Base::generator() % Base::upperBound + 1;
				}
			}
		}
	}
}


template <typename Specimen, typename Generator>
void BasicMutator<Specimen, Generator>::init(int size, int upperBound)
{
	Base::init(size, upperBound);
}