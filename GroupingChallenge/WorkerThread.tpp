#include "WorkerThread.hpp"
#include <iostream>
template <typename Child>
WorkerThread<Child>::WorkerThread(ThreadController<Child>* master, int id) :  master(master), id(id), hasJob(false), dying(false), thread(&WorkerThread<Child>::run, this) {}

template <typename Child>
void WorkerThread<Child>::run()
{
	std::unique_lock lock{ mtx };
	while (this->condition())
	{
		cv.wait(lock, [this] {return hasJob || dying; });
		if (dying)
		{
			return;
		}
		static_cast<Child*>(this)->run();
		hasJob = false;
		master->signalDone();
	}
}

template <typename Child>
bool WorkerThread<Child>::condition()
{
	return static_cast<Child*>(this)->condition();
}

template <typename Child>
constexpr bool WorkerThread<Child>::isAsync()
{
	return static_cast<Child*>(this)->isAsync();
}


template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
PopulationThread<Specimen, Selection, Breeding, Mutator>::PopulationThread(ThreadController<PopulationThread>* master, int id) : evaluator(nullptr), WorkerThread<PopulationThread>(master, id), bestScore(std::numeric_limits<double>::max()), selectionStrategy(engine), breedingStrategy(engine), mutator(engine) {}

template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
void PopulationThread<Specimen, Selection, Breeding, Mutator>::run()
{
	double score;
	vector<int> candidate;
	for (auto& i : specimens)
	{
		candidate = i.getSolution();
		score = evaluator->evaluate(candidate);
		if (score < bestScore)
		{
			this->bestScore = score;
			this->solution = candidate;
		}
		
	}
	std::vector<Specimen*> selected = selectionStrategy.select(constants::populationSize);

	breedingStrategy.cross(selected, &next[0]);
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
		i.init(e->lowerBound(), e->upperBound(), e->getNumberOfPoints());
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