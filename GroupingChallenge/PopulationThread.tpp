template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
PopulationThread<Specimen, Selection, Breeding, Mutator>::PopulationThread(ThreadController<PopulationThread>* master, int id) : evaluator(nullptr), WorkerThread<PopulationThread>(master, id), bestScore(std::numeric_limits<double>::max()), selectionStrategy(engine), breedingStrategy(engine), mutator(engine) {}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
void PopulationThread<Specimen, Selection, Breeding, Mutator>::run()
{
	double score;
	vector<int>* candidate;
	double max_sc = 0;
	double min_sc = numeric_limits<double>::max();

	for (auto& i : specimens)
	{
		candidate = i.getSolutionAddr();
		score = i.evaluate(evaluator);
		if (score > max_sc)
		{
			max_sc = score;
		}
		else if (score < min_sc)
		{
			min_sc = score;
		}
		if (score < bestScore)
		{
			this->bestScore = score;
			this->solution = *candidate;
		}

	}

	if (max_sc - min_sc < constants::epsilon)
	{
		mutator.setProba(constants::pMutationHigh);
	}
	else
	{
		mutator.setProba(constants::pMutationLow);
	}

	breedingStrategy.cross(selectionStrategy.select(constants::populationSize), &next[0]);
	/*
	int ctr = 0;
	for (auto& i : specimens)
	{
		candidate = i.getSolution();
		score = evaluator->evaluate(candidate);
		std::cout << "SPECIMEN " << ctr << " : " << score<<"\n";
		++ctr;
	}
	*/

	mutator.mutate(next);
	specimens = next;
}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
bool PopulationThread<Specimen, Selection, Breeding, Mutator>::condition()
{
	return true;
}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
void PopulationThread<Specimen, Selection, Breeding, Mutator>::setJob()
{
	{
		std::lock_guard lock{ WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>::mtx };
		WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>::hasJob = true;
	}
	WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>::cv.notify_one();
}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
void PopulationThread<Specimen, Selection, Breeding, Mutator>::kill()
{
	{
		std::lock_guard lock{ WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>::mtx };
		WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>::dying = true;
	}
	WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>::cv.notify_one();
}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
void PopulationThread<Specimen, Selection, Breeding, Mutator>::setComputingData(Evaluator* e)
{
	evaluator = e;
	specimens = std::vector<Specimen>(constants::populationSize);
	next = std::vector<Specimen>(constants::populationSize);
	for (auto& i : specimens)
	{
		i.init(std::move(e->getRandomSolution()));
	}
	//breedingStrategy.init(e->getNumberOfPoints());
	selectionStrategy.init(&specimens, e);
	breedingStrategy.init(evaluator->getNumberOfPoints());
	mutator.init(evaluator->getNumberOfPoints(), evaluator->upperBound());
	engine.seed(std::rand());

}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
std::vector<int>& PopulationThread<Specimen, Selection, Breeding, Mutator>::getSolution()
{
	return solution;
}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
double PopulationThread<Specimen, Selection, Breeding, Mutator>::getBestScore()
{
	return bestScore;
}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
std::vector<Specimen>& PopulationThread<Specimen, Selection, Breeding, Mutator>::getSpecimens()
{
	return specimens;
}