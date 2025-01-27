
template<typename T>
ThreadController<T>::ThreadController(int workerCount) : lock(mtx), workerCount(workerCount) 
{
	//ciekawe czy mozna zamiast pointerow przechowywac po prostu thready
	workers.reserve(workerCount);
	for (size_t i = 0; i < workerCount; ++i)
	{
		workers.push_back(new T(this, i));
	}
}

template<typename T>
ThreadController<T>::~ThreadController()
{
	for (auto i : workers)
	{
		i->kill();
	}
}

template<typename T>
void ThreadController<T>::signalDone()
{
	{
		std::lock_guard lock{ mtx };
		++doneCount;
	}
	if (doneCount == workerCount)
	{
		cv.notify_one();
	}
}

template<typename T>
void ThreadController<T>::waitAll()
{
	cv.wait(lock, [this] {return doneCount == workerCount; });
	doneCount = 0;
}

template<typename T>
void ThreadController<T>::reserve(int n)
{
	workers.reserve(n);
}

template<typename T>
std::vector <T*>& ThreadController<T>::getWorkers() { return workers; }