#pragma once
#include "ThreadController.hpp"
#include <condition_variable>
#include "MyOwnEvaluator.hpp"
#include "RenderingCode.hpp"
#include "Settings.hpp"
template <typename Child>
class WorkerThread
{
protected:
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
	WorkerThread(ThreadController<Child>* master);
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
	GraphicThread(ThreadController<GraphicThread>* master);

	void setJob(std::vector<int>* solution);
	void kill();

	void setRenderData(const std::vector<NGroupingChallenge::CPoint>* pts, int groups);
	sf::RenderWindow& getWindow();

	friend class WorkerThread<GraphicThread>;
};



//Todo - ruszyc best score i solution gdzie indziej
template <typename Specimen>
class PopulationThread : public WorkerThread<PopulationThread<Specimen>>
{
private:
	double bestScore;
	std::vector<int> solution;

	int size;
	std::vector<Specimen> specimens;

	Evaluator* evaluator;
protected:
	void run();
	bool condition();
public:
	PopulationThread(ThreadController<PopulationThread<Specimen>>* master);
	//todo implementacja i argumenty
	void setJob();
	void kill();

	void setComputingData(Evaluator* e);

	std::vector<int>& getSolution();

	friend class WorkerThread<PopulationThread<Specimen>>;
};


#include "WorkerThread.tpp"