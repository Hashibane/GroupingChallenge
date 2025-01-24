#include "WorkerThread.hpp"

template <typename Child>
WorkerThread<Child>::WorkerThread(ThreadController<Child>* master) : master(master), hasJob(false), dying(false), thread(&WorkerThread<Child>::run, this) {}

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


template <typename Specimen>
PopulationThread<Specimen>::PopulationThread(ThreadController<PopulationThread>* master) : evaluator(nullptr), WorkerThread<PopulationThread>(master), bestScore(std::numeric_limits<double>::max()) {}

template <typename Specimen>
void PopulationThread<Specimen>::run()
{
	double score;
	vector<int> candidate;
	for (auto& i : specimens)
	{
		candidate = i.soulution();
		score = evaluator->evaluate(candidate);
		if (score < bestScore)
		{
			this->bestScore = score;
			this->solution = candidate;
		}
	}

}

template <typename Specimen>
bool PopulationThread<Specimen>::condition()
{
	return true;
}

template <typename Specimen>
void PopulationThread<Specimen>::setJob()
{
	{
		std::lock_guard lock{ WorkerThread<PopulationThread<Specimen>>::mtx };
		WorkerThread<PopulationThread<Specimen>>::hasJob = true;
	}
	WorkerThread<PopulationThread<Specimen>>::cv.notify_one();
}

template <typename Specimen>
void PopulationThread<Specimen>::kill()
{
	{
		std::lock_guard lock{ WorkerThread<PopulationThread<Specimen>>::mtx };
		WorkerThread<PopulationThread<Specimen>>::dying = true;
	}
	WorkerThread<PopulationThread<Specimen>>::cv.notify_one();
}

template <typename Specimen>
void PopulationThread<Specimen>::setComputingData(Evaluator* e)
{
	evaluator = e;
	specimens = std::vector<Specimen>(constants::populationSize, Specimen(*e));
}

template <typename Specimen>
std::vector<int>& PopulationThread<Specimen>::getSolution()
{
	return solution;
}

template <typename Specimen>
double PopulationThread<Specimen>::getBestScore()
{
	return bestScore;
}