#include "somanimation.h"

using namespace kohonen;

somAnimation::somAnimation(int number_of_vertices, float**X, QGraphicsScene* scene) : Net(number_of_vertices, X), scene(scene)
{
    NUMBER_OF_NEURONS = number_of_vertices;
    weights = Net.getWeights();
    graphicsPoint = new Point*[NUMBER_OF_NEURONS];
    for (int i = 0; i < NUMBER_OF_NEURONS; i++)
    {
        graphicsPoint[i] = new Point(i, weights[i][0], weights[i][1]);
        scene->addItem(graphicsPoint[i]);
    }
    graphicsLine = new PointLine*[NUMBER_OF_NEURONS];
    for (int i = 0; i < NUMBER_OF_NEURONS-1; i++)
    {
        graphicsLine[i] = new PointLine(graphicsPoint[i], graphicsPoint[i+1]);
        scene->addItem(graphicsLine[i]);
    }
    graphicsLine[NUMBER_OF_NEURONS-1] = new PointLine(graphicsPoint[NUMBER_OF_NEURONS-1], graphicsPoint[0]);
    scene->addItem(graphicsLine[NUMBER_OF_NEURONS-1]);
    counter = 0;
}

void somAnimation::advance(int phase)
{
    if (!phase) return;
    if (counter == NUMBER_OF_ITERATIONS)
    {
        scene->update();
        return;
    }
    counter++;
    for (int i = 0; i < NUMBER_OF_NEURONS; i++)
    {
        Net.FeedForward(i);
        Net.Adaptation(i);
    }
    Net.UpdateLearningRate();
    Net.UpdateLambda();
    Net.setLookUp(0);
    if (counter == NUMBER_OF_ITERATIONS)
        Net.Repair();
    weights = Net.getWeights();
    for (int i = 0; i < NUMBER_OF_NEURONS; i++)
        graphicsPoint[i]->setPosition(weights[i][0], weights[i][1]);
    for (int i = 0; i < NUMBER_OF_NEURONS; i++)
        graphicsLine[i]->update();
    scene->update();
}

somAnimation::~somAnimation()
{
    for (int i = 0; i < NUMBER_OF_NEURONS; i++)
    {
		scene->removeItem(graphicsPoint[i]);
        delete graphicsPoint[i];
		scene->removeItem(graphicsLine[i]);
        delete graphicsLine[i];
    }
	delete[] graphicsPoint;
	graphicsPoint = nullptr;
    delete[] graphicsLine;
	graphicsLine = nullptr;
}
