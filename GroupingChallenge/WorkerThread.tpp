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


