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
		bool computed;
		double score;
		std::vector<int> solution;
		std::vector<int> genRandom(int low, int high, int size)
		{
			uniform_int_distribution<int> candidate_distribution(low, high);

			std::vector<int> next;
			for (size_t i = 0; i < size; i++)
			{
				next.push_back(candidate_distribution(random_engine));
			}

			return next;
		}
	public:
		BaseSpecimen() : solution(), computed(false) {}
		BaseSpecimen(std::vector<int>& s) : solution(s), computed(false) {}
		BaseSpecimen(std::vector<int>&& s) : solution(s), computed(false) {}
		inline void init(int low, int high, int size)
		{
			solution = genRandom(low, high, size);
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
		inline void setComputed(bool b) { computed = b; }
		inline bool getComputed() { return computed; }
		inline void setScore(double s) { score = s; }
		inline double getScore() { return score; }
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

		inline void init(int low, int high, int size)
		{
			BaseSpecimen::init(low, high, size);
		}
		inline std::vector<int>* getSolutionAddr()
		{
			return BaseSpecimen::getSolutionAddr();
		}
	};

}