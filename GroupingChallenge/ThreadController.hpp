#pragma once
#include <vector>
#include <thread>
#include <condition_variable>

// for future use
template<typename Worker>
class ThreadController
{
private:
	std::condition_variable cv;
	std::mutex mtx;
	std::unique_lock<std::mutex> lock;
	int workerCount;
	std::vector<Worker*> workers;
	//shared
	int doneCount;
public:
	ThreadController(int workerCount);
	~ThreadController();

	void reserve(int n);
	void signalDone();
	void waitAll();

	std::vector<Worker*>& getWorkers();
};

#include "ThreadController.tpp"