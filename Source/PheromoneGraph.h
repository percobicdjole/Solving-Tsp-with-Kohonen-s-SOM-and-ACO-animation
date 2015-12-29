#pragma once
class PheromoneGraph;
#include "acoDialog.h"
#include "ant.h"
#include "antsim.h"

namespace heuristic_constants
{
	const float ALPHA = 0.1;
	const int BETA = 2;
	const float Q0 = 0.9;
	const int NUMBER_OF_ITERATIONS_FOR_NN = 5;
    const int INFINITI = 10000000;
    const int NUMBER_OF_ANTS = 8;
    const int NUMBER_OF_ITERATIONS = 10;
    const float PI = 3.14159265;
}

class PheromoneGraph
{
public:
	PheromoneGraph(const int n, float** X);
    ~PheromoneGraph();
	friend class Ant;
    friend class Aco;
    friend class AntSim;
private:
	Ant* ant;
	float T0;
	float** pheromoneMatrix;
	float** matrix;
	const int number_of_edges;
	void nearest_neightbour_weight();
    void pheromone_globalUpdate(const int antNumber);
    void pheromone_localUpdate(int j, int i);
};

float euclidean_distance(float x1, float y1, float x2, float y2);
