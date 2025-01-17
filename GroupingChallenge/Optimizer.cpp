#include "Optimizer.h"
#include "Strategies.hpp"

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
	delete graphicMan;
	delete populationMan;
	delete evaluator;
}

void COptimizer::vInitialize()
{
	//thread local?
	evaluator = new Evaluator(c_evaluator.vGetPoints(), c_evaluator.iGetUpperBound());
	d_current_best_fitness = numeric_limits<double>::max();

	populationMan = new ThreadController<PopulationThread<Strategy>>(constants::populations);
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

	double fitness;
	std::vector<int>* solution;
	auto& workers = populationMan->getWorkers();
	int j = 0;
	for (auto& i : workers)
	{
		i->setJob();
	}

	populationMan->waitAll();

	for (auto& i : workers)
	{
		solution = &i->getSolution();
		fitness = evaluator->evaluate(*solution);
		if (fitness < d_current_best_fitness)
		{
			v_current_best = *solution;
			d_current_best_fitness = fitness;
		}
		graphicMan->getWorkers()[j]->setJob(solution);
		++j;
	}

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
	std::cout << d_current_best_fitness << "\n";
}

