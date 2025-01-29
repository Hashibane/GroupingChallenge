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

	WorkerThread(const WorkerThread<Child>& other) = delete;
	WorkerThread(WorkerThread<Child>&& other) = delete;

	WorkerThread& operator=(const WorkerThread<Child>& other) = delete;
	WorkerThread& operator=(WorkerThread<Child>&& other) = delete;

};



#include "WorkerThread.tpp"