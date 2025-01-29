#include "WorkerThread.hpp"

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

	void close();

	void setRenderData(const std::vector<NGroupingChallenge::CPoint>* pts, int groups);
	sf::RenderWindow& getWindow();

	friend class WorkerThread<GraphicThread>;
};