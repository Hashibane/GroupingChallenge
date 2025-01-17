#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"
#include "MyOwnEvaluator.hpp"
#include "PopulationManager.hpp"
#include "Strategies.hpp"
#include "Settings.hpp"
#include "WorkerThread.hpp"

#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using Strategy = population::RandomSpecimen;

namespace NGroupingChallenge
{
	class COptimizer
	{
	public:
		COptimizer(CGroupingEvaluator& cEvaluator);
		~COptimizer();

		void vInitialize();
		void vRunIteration();

		std::vector<int>* pvGetCurrentBest() { return &v_current_best; }

	private:
		CGroupingEvaluator& c_evaluator; 
		Evaluator* evaluator;

		ThreadController<GraphicThread>* graphicMan;
		ThreadController<PopulationThread<Strategy>>* populationMan;
		std::vector<population::PopulationManager<Strategy>> managers;

		double d_current_best_fitness;
		vector<int> v_current_best;

		mt19937 c_random_engine;
	};
}

#endif