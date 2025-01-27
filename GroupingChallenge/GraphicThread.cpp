#include "WorkerThread.hpp"

GraphicThread::GraphicThread(ThreadController<GraphicThread>* master, int id) : WorkerThread<GraphicThread>(master, id), points(nullptr), numberOfGroups(0), solution(nullptr), window(nullptr) {}


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
	delete points;
	cv.notify_one();
}

void GraphicThread::setRenderData(const std::vector<NGroupingChallenge::CPoint>* pts, int groups)
{
	{
		std::lock_guard lock{ mtx };
		points = pts;
		std::vector<NGroupingChallenge::CPoint>* toCopy = new std::vector<NGroupingChallenge::CPoint>{};
		toCopy->reserve(pts->size());

		double xmin = numeric_limits<double>::max(), xmax = numeric_limits<double>::min(), ymin = numeric_limits<double>::max(), ymax = numeric_limits<double>::min();
		double x, y;
		for (auto i : *pts)
		{
			NGroupingChallenge::CPoint toAdd;
			x = i.FgetCoordinates()[0]; y = i.FgetCoordinates()[1];
			if (x < xmin)
				xmin = x;
			else if (x > xmax)
				xmax = x;
			if (y < ymin)
				ymin = y;
			else if (y > ymax)
				ymax = y;

			toAdd.vAddCoordinate(x);
			toAdd.vAddCoordinate(y);
			toCopy->push_back(toAdd);
		}
		double scale = min(constants::windowWidth / (xmax - xmin), constants::windowHeight / (ymax - ymin));
		for (int i = 0 ; i < toCopy->size() ; ++i)
		{
			NGroupingChallenge::CPoint toSub;
			x = (*toCopy)[i].FgetCoordinates()[0]; y = (*toCopy)[i].FgetCoordinates()[1];
			toSub.vAddCoordinate((x - xmin) * scale);
			toSub.vAddCoordinate((y - ymin) * scale);
			(*toCopy)[i] = toSub;

		}
		points = toCopy;

		numberOfGroups = groups;
		window = new sf::RenderWindow(sf::VideoMode({ constants::windowWidth, constants::windowHeight }), "Pop x");
		window->setActive(false);
	}
}