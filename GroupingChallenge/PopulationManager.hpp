#pragma once
#include <vector>
#include "Settings.hpp"
#include "RenderingCode.hpp"
namespace population
{
	template <typename Specimen>
	class PopulationManager
	{
	private:		
		Evaluator evaluator;

		double bestScore;
		std::vector<int> solution;
	
		int size;
		std::vector<Specimen> specimens;


		//1000
		//std::vector<std::vector<int>> solutionCache;
	public:
		PopulationManager(int size, Evaluator& e);
		void step();
		std::vector<int>& getSolution();
		
	};
}

#include "PopulationManager.tpp"