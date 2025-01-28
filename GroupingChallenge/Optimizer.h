#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"
#include "MyOwnEvaluator.hpp"
#include "PopulationManager.hpp"
#include "Strategies.hpp"
#include "Settings.hpp"
#include "WorkerThread.hpp"
#include "Breeding.hpp"
#include "Mutator.hpp"
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include "Selection.hpp"
using Strategy = population::BreedableSpecimen;
using Selection = MixedSelection<Strategy, std::mt19937>;
using Breeding = Uniform<Strategy>;
using Mutator = BasicMutator<Strategy, std::mt19937>;

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
		int iteration;

		CGroupingEvaluator& c_evaluator; 
		Evaluator* evaluator;

		ThreadController<GraphicThread>* graphicMan;
		ThreadController<PopulationThread<Strategy, Selection, Breeding, Mutator>>* populationMan;

		double d_current_best_fitness;
		vector<int> v_current_best;

		mt19937 c_random_engine;

		void migration();
	};
}

#endif