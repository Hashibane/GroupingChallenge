#pragma once
#include <vector>
#include "MyOwnEvaluator.hpp"
#include <random>

namespace population
{
	static mt19937 random_engine;

	template <class Child>
	class BaseSpecimen
	{
	protected:
		Evaluator& evaluator;
		
		//dzielimy grupy wzgledem odleglosci wewnatrz grupy
		std::vector<double> groupScore;
	public:
		BaseSpecimen(Evaluator& e) : evaluator(e) {}

		inline std::vector<int> soulution()
		{
			static_cast<Child*>(this)->soulution();
		}
	};

	class RandomSpecimen : BaseSpecimen<RandomSpecimen>
	{
	public:
		RandomSpecimen(Evaluator& e) : BaseSpecimen(e) {}

		inline std::vector<int> soulution()
		{
			vector<int> next(evaluator.getNumberOfPoints());

			uniform_int_distribution<int> candidate_distribution(evaluator.lowerBound(), evaluator.upperBound());

			for (size_t i = 0; i < next.size(); i++)
			{
				next[i] = candidate_distribution(random_engine);
			}

			return next;
		}
	};

}