#include "WorkerThread.hpp"

GraphicThread::GraphicThread(ThreadController<GraphicThread>* master) : WorkerThread<GraphicThread>(master), points(nullptr), numberOfGroups(0), solution(nullptr), window(nullptr) {}


void GraphicThread::run()
{


	window->clear();
	std::vector<sf::CircleShape> pts = toDraw(*points, *solution, numberOfGroups);
	for (auto& i : pts)
	{
		window->draw(i);
	}
	window->display();
	solution = nullptr;

}

bool GraphicThread::condition()
{
	return (window == nullptr || window->isOpen());
}


sf::RenderWindow& GraphicThread::getWindow() { return *window; }

void GraphicThread::setJob(std::vector<int>* solution)
{
	{
		std::lock_guard lock{ mtx };
		hasJob = true;
		this->solution = solution;
	}

	cv.notify_one();
}

void GraphicThread::kill()
{
	{
		std::lock_guard lock{ mtx };
		dying = true;
	}

	cv.notify_one();
}

void GraphicThread::setRenderData(const std::vector<NGroupingChallenge::CPoint>* pts, int groups)
{
	{
		std::lock_guard lock{ mtx };
		points = pts;
		numberOfGroups = groups;
		window = new sf::RenderWindow(sf::VideoMode({ constants::windowWidth, constants::windowHeight }), "Pop x");
		window->setActive(false);
	}
}