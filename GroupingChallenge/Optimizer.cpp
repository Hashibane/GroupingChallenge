#include "Optimizer.h"
#include "Specimens.hpp"

#include <chrono>

using namespace NGroupingChallenge;
using namespace population;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator)
	: c_evaluator(cEvaluator)
{
	random_device c_seed_generator;
	c_random_engine.seed(c_seed_generator());
}

COptimizer::~COptimizer()
{
	for (auto& i : graphicMan->getWorkers())
	{
		i->close();
	}
	delete graphicMan;
	delete populationMan;
	delete evaluator;
}


void COptimizer::vInitialize()
{
	iteration = 0;
	evaluator = new Evaluator(c_evaluator.vGetPoints(), c_evaluator.iGetUpperBound());

	d_current_best_fitness = numeric_limits<double>::max();

	populationMan = new ThreadController<PopulationThread<Strategy, Selection, Breeding, Mutator>>(constants::populations);
	graphicMan = new ThreadController<GraphicThread>(constants::populations);

	for (auto& i : populationMan->getWorkers())
	{
		i->setComputingData(evaluator);
	}
	for (auto& i : graphicMan->getWorkers())
	{
		i->setRenderData(&evaluator->getPoints(), c_evaluator.iGetUpperBound());
	}
}

void COptimizer::vRunIteration()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<int>* solution;
	auto& workers = populationMan->getWorkers();
	int j = 0;
	for (auto& i : workers)
	{
		i->setJob();
	}

	populationMan->waitAll();
	auto mid = std::chrono::high_resolution_clock::now();
	auto processing = std::chrono::duration_cast<std::chrono::milliseconds>(mid - start);
	std::cout << "Processing time: " << processing.count() << " ms" << std::endl;
	for (auto& i : workers)
	{
		solution = &i->getSolution();
		if (i->getBestScore() < d_current_best_fitness)
		{
			v_current_best = *solution;
			d_current_best_fitness = i->getBestScore();
		}
		if (constants::debug)
			graphicMan->getWorkers()[j]->setJob(solution);
		++j;
	}

	++iteration;
	migration();

	if (constants::debug)
	{
		for (auto& i : graphicMan->getWorkers())
		{
			sf::Event e;
			while (i->getWindow().pollEvent(e))
			{
				//event handling 
				if (e.type == sf::Event::Closed)
				{
					i->getWindow().close();
				}
			}
		}
		graphicMan->waitAll();
	}
	auto end = std::chrono::high_resolution_clock::now();

	// Calculate the elapsed time in milliseconds
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
	std::cout << d_current_best_fitness << "\n";

}

void COptimizer::migration()
{
	int p1, p2, index;
	if (iteration == 300)
	{
		for (int i = 0; i < constants::migrations; ++i)
		{
			p1 = c_random_engine() % constants::populations;
			p2 = c_random_engine() % constants::populations;
			for (int j = 0; j < constants::migrationSize; ++j)
			{
				index = c_random_engine() % constants::populationSize;
				std::swap(populationMan->getWorkers()[p1]->getSpecimens()[index], populationMan->getWorkers()[p2]->getSpecimens()[index]);
			}

		}
		iteration = 0;
	}

}