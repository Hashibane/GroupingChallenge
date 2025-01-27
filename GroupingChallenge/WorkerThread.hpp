#pragma once
#include "ThreadController.hpp"
#include <condition_variable>
#include "MyOwnEvaluator.hpp"
#include "RenderingCode.hpp"
#include "Settings.hpp"
#include <random>
template <typename Child>
class WorkerThread
{
protected:
	int id;
	ThreadController<Child>* master;
	std::thread thread;
	std::condition_variable cv;
	std::mutex mtx;
	//shared mem
	bool hasJob;
	bool dying;

	void run();
	bool condition();
	constexpr bool isAsync();
public:
	WorkerThread(ThreadController<Child>* master, int id);
};

class GraphicThread : public WorkerThread<GraphicThread>
{
private:
	std::vector<int>* solution;
	const std::vector<NGroupingChallenge::CPoint>* points;
	int numberOfGroups;

	sf::RenderWindow* window;

protected:
	void run();
	bool condition();


public:
	GraphicThread(ThreadController<GraphicThread>* master, int id);

	void setJob(std::vector<int>* solution);
	void kill();

	void setRenderData(const std::vector<NGroupingChallenge::CPoint>* pts, int groups);
	sf::RenderWindow& getWindow();

	friend class WorkerThread<GraphicThread>;
};



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
	//todo implementacja i argumenty
	void setJob();
	void kill();

	void setComputingData(Evaluator* e);

	std::vector<int>& getSolution();
	double getBestScore();

	std::vector<Specimen>& getSpecimens();

	friend class WorkerThread<PopulationThread<Specimen, Selection, Breeding, Mutator>>;
};


#include "WorkerThread.tpp"