#include "PopulationManager.hpp"

template <typename Specimen>
inline population::PopulationManager<Specimen>::PopulationManager(int size, Evaluator& e) : size(size), evaluator(e), bestScore(numeric_limits<double>::max()), specimens(std::vector<Specimen>(size, Specimen(e)))
{
	
}


template <typename Specimen>
inline void population::PopulationManager<Specimen>::step()
{
	double score;
	vector<int> candidate;
	for (auto& i : specimens)
	{
		candidate = i.soulution();
		score = evaluator.evaluate(candidate);
		if (score < bestScore)
		{
			this->bestScore = score;
			this->solution = candidate;
		}
	}
	//windowMan.draw(evaluator.getPoints(), this->solution, evaluator.upperBound());
}

template <typename Specimen>
inline std::vector<int>& population::PopulationManager<Specimen>::getSolution()
{
	return this->solution;
}

