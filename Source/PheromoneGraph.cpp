#include <iostream>
#include "PheromoneGraph.h"

using namespace heuristic_constants;

float euclidean_distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

PheromoneGraph::PheromoneGraph(const int n, float** X) : number_of_edges(n)
{
	// CREATION OF DISTANCE AND PHEROMONE MATRIX;
	matrix = new float*[n];
	pheromoneMatrix = new float*[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new float[n];
		pheromoneMatrix[i] = new float[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			matrix[i][j] = euclidean_distance(X[i][0], X[i][1], X[j][0], X[j][1]);
			matrix[j][i] = matrix[i][j];
			pheromoneMatrix[i][j] = rand()/(double)RAND_MAX;
			pheromoneMatrix[j][i] = rand()/(double)RAND_MAX; // DA LI JE OVO PAMETNO -- MOZDA ISTE DA STAVIM
		}
	}
	// CREATION OF ARTIFICIAL ANTS
    Ant::n = n;
	ant = new Ant[NUMBER_OF_ANTS];
	nearest_neightbour_weight();
}

PheromoneGraph::~PheromoneGraph()
{
    for (int i = 0; i < number_of_edges; i++)
    {
        delete[] matrix[i];
        delete[] pheromoneMatrix[i];
    }
    delete[] pheromoneMatrix;
    delete[] matrix;
    delete[] ant;
}

inline void PheromoneGraph::nearest_neightbour_weight()
{
	int* lookUpTable = new int[number_of_edges]();
	int weight = 0, edge;
	int best_node, best_node_weight;
    T0 = INFINITI;
	for (int i = 0; i < NUMBER_OF_ITERATIONS_FOR_NN; i++)
	{
        edge = qrand() % number_of_edges;
		lookUpTable[edge] = 1;
		for (int j = 0; j < number_of_edges -1; j++)
		{
            best_node_weight = INFINITI;
			for(int k = 0; k < number_of_edges; k++)
			{
				if (matrix[edge][k] < best_node_weight &&  lookUpTable[k] == 0)
				{
					best_node_weight = matrix[edge][k];
					best_node = k;
				}
			}
			weight+= best_node_weight;
			edge = best_node;
			lookUpTable[edge] = 1;
		}
		memset(lookUpTable, 0, number_of_edges*sizeof(int));
		if (weight < T0)
			T0 = weight;
	}
	delete[] lookUpTable;
	T0 = 1/(T0*number_of_edges);
}

// FUNCTION THAT USES ANT COLONY OPTIMIZATION ALGORITHM DO SOLVE TSP
/*void PheromoneGraph::ant_colony_optimization()
{
	for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
	{
		for (int j = 0; j < number_of_edges-1; j++)
		{
			for (int k = 0; k < NUMBER_OF_ANTS; k++)
				ant[k].walk(*this);
			pheromone_localUpdate();
		}
		pheromone_globalUpdate();
		Ant bestAnt(ant[0]);
		for (int j = 1; j < NUMBER_OF_ANTS; j++)
		{
			if (ant[j].calculate_pheromones() < bestAnt.calculate_pheromones())
				bestAnt = ant[j];           // Da ne bi kopirao stalno sve iskopiraj samo stvari koje ti trebaju
		}
		for (int j = 0; j < NUMBER_OF_ANTS; j++)
		{
			ant[j].change_edge_randomly();
			ant[j].setWayWeight(0.0);
			ant[j].setNumberOfVerticesTraversed(0);
			ant[j].resetTabu();
		}
	}
}*/

// SMANJI -- MOZDA NE PUCA OVDJE
void PheromoneGraph::pheromone_globalUpdate(const int antNumber)
{
	// POPRAVI NIZ ZA MRAVE DA POCETNI ELEMENT POKAZUJE NA IVICU OD KOJE SU KRENULI
        float weight = 1/ant[antNumber].calculate_pheromones();
        for (int j = 0; j < number_of_edges-1; j++)
		{
            pheromoneMatrix[ant[antNumber].getTabu(j)][ant[antNumber].getTabu(j+1)]*= (1-ALPHA);
            pheromoneMatrix[ant[antNumber].getTabu(j)][ant[antNumber].getTabu(j+1)]+= (ALPHA*weight);
		}
}

void PheromoneGraph::pheromone_localUpdate(int j, int i) // Da LI Da LI
{
    pheromoneMatrix[ant[i].getTabu(j)][ant[i].getTabu(j+1)]*= (1-ALPHA);
    pheromoneMatrix[ant[i].getTabu(j)][ant[i].getTabu(j+1)]+= (ALPHA*T0);
}
