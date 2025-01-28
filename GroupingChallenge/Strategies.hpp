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
		double score;
		std::vector<int> solution;
	public:
		BaseSpecimen() : solution() {}
		BaseSpecimen(std::vector<int>& s) : solution(s) {}
		BaseSpecimen(std::vector<int>&& s) : solution(s) {}
		inline void init(std::vector<int>&& s)
		{
			solution = s;
		}
		inline std::vector<int>& getSolution()
		{
			return static_cast<Child*>(this)->soulution();
		}
		inline void setSolution(std::vector<int>& solution)
		{
			static_cast<Child*>(this)->setSolution(solution);
		}
		inline std::vector<int>* getSolutionAddr() { return &solution; }
		inline double getScore() { return score; }
		inline double evaluate(Evaluator* e) { 
			score = e->evaluate(solution); 
			return score; 
		}
	};
	/*
	class RandomSpecimen : BaseSpecimen<RandomSpecimen>
	{
	public:
		RandomSpecimen(Evaluator& e) : BaseSpecimen(e) {}

		inline std::vector<int> getSolution()
		{
			vector<int> next(evaluator.getNumberOfPoints());

			uniform_int_distribution<int> candidate_distribution(evaluator.lowerBound(), evaluator.upperBound());

			for (size_t i = 0; i < next.size(); i++)
			{
				next[i] = candidate_distribution(random_engine);
			}

			solution = next;
			return next;
		}
		inline void setSolution(std::vector<int>& solution) 
		{
			this->solution = solution;
		}
	};
	*/
	class BreedableSpecimen : public BaseSpecimen<BreedableSpecimen>
	{
	public:
		BreedableSpecimen() {}
		BreedableSpecimen(std::vector<int>& s) : BaseSpecimen(s) {}
		BreedableSpecimen(std::vector<int>&& s) : BaseSpecimen(s) {}

		inline std::vector<int>& getSolution()
		{
			return solution;
		}

		inline void setSolution(std::vector<int>& solution)
		{
			this->solution = solution;
		}

		inline void init(std::vector<int>&& s)
		{
			BaseSpecimen::init(std::move(s));
		}
		inline std::vector<int>* getSolutionAddr()
		{
			return BaseSpecimen::getSolutionAddr();
		}
		inline double evaluate(Evaluator* e)
		{
			return BaseSpecimen::evaluate(e);
		}
		inline double getScore()
		{
			return BaseSpecimen::getScore();
		}
	};

}