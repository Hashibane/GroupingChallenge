#pragma once
#include <vector>

template <typename Child, typename Specimen, typename Generator>
class BaseMutator
{
protected:
	int upperBound;
	int size;
	Generator& generator;
public:
	BaseMutator(Generator& g);
	void mutate(std::vector<Specimen>& specimens);
	void init(int s, int upperBound);
};

template <typename Specimen, typename Generator>
class BasicMutator : public BaseMutator<BasicMutator<Specimen, Generator>, Specimen, Generator>
{
private:
	using Base = BaseMutator<BasicMutator<Specimen, Generator>, Specimen, Generator>;
	typename Generator::result_type _mutationNumber = constants::pMutationLow * Generator::max();
public:
	BasicMutator(Generator& g);
	void mutate(std::vector<Specimen>& specimens);
	void init(int s, int upperBound);
	void setProba(double proba);
};


#include "Mutator.tpp"