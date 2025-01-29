#include "WorkerThread.hpp"

//Todo - ruszyc best score i solution gdzie indziej
template <typename Specimen, typename Selection, typename Breeding, typename Mutator>
class PopulationThread : public WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>
{
private:
	double bestScore;
	std::vector<int> solution;

	int size;
	std::vector<Specimen> specimens;
	std::vector<Specimen> next;
	std::mt19937 engine;

	Selection selectionStrategy;
	Breeding breedingStrategy;
	Mutator mutator;

	Evaluator* evaluator;
	//std::vector<std::vector<int>> solutionCache;
protected:
	void run();
	bool condition();
public:
	PopulationThread(ThreadController<PopulationThread<Specimen, Selection, Breeding, Mutator>>* master, int id);
	PopulationThread(const PopulationThread<Specimen, Selection, Breeding, Mutator>& other) = delete;
	PopulationThread(const PopulationThread<Specimen, Selection, Breeding, Mutator>&& other) = delete;

	PopulationThread<Specimen, Selection, Breeding, Mutator>& operator=(const PopulationThread<Specimen, Selection, Breeding, Mutator>& other) = delete;
	PopulationThread<Specimen, Selection, Breeding, Mutator>& operator=(PopulationThread<Specimen, Selection, Breeding, Mutator>&& other) = delete;
	//todo implementacja i argumenty
	void setJob();
	void kill();

	void setComputingData(Evaluator* e);

	std::vector<int>& getSolution();
	double getBestScore();

	std::vector<Specimen>& getSpecimens();

	friend class WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>;
};

#include "PopulationThread.tpp"