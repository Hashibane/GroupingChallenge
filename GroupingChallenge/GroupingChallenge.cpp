#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "Optimizer.h"
#include "GroupingEvaluator.h"
#include "Handler.hpp"
using namespace NGroupingChallenge;

int main()
{
	
	CGaussianGroupingEvaluatorFactory c_evaluator_factory(5, 10000, 5);
	//meanMin, meanMax, stdMin, stdMax
	c_evaluator_factory
		.cAddDimension(-100, 100, 1.0, 3.0)
		.cAddDimension(-100, 100, 1.0, 1.0);
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0)
		//.cAddDimension(-100, 100, 1.0, 1.0);
		/*
	Handler h{ "data.txt" };
	CGroupingEvaluator* pc_evaluator = new CGroupingEvaluator(10, h.read());
	*/
	CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);
	COptimizer c_optimizer(*pc_evaluator);

	c_optimizer.vInitialize();
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++)
		{
			c_optimizer.vRunIteration();
		}


		delete pc_evaluator;
		// Record the end time
		auto end = std::chrono::high_resolution_clock::now();

		// Calculate the elapsed time in milliseconds
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		// Print the duration
		std::cout << "TOTAL: " << duration.count() << " ms" << std::endl;

		return 0;
	}