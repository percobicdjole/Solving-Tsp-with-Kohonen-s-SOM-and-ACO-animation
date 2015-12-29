#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "ant.h"
using namespace heuristic_constants;

int Ant::n = 0;

Ant::Ant()
{
    edge = qrand() % n;
	wayWeight = 0;
    tabu = new int[n]();
    tabu[0] = edge;
    i = 1;
    lookUpTabu = new int[n]();
	lookUpTabu[edge] = 1;
}

Ant::Ant(const Ant& a)
{
	i = a.i;
	edge = a.edge;
	tabu = new int[n];
	memcpy(tabu, a.tabu, n*sizeof(int));
	lookUpTabu = new int[n];
	memcpy(lookUpTabu, a.lookUpTabu, n*sizeof(int));
	wayWeight = a.wayWeight;
}

Ant::Ant(Ant&& a)
{
	i = a.i;
	edge = a.edge;
	tabu = a.tabu;
	a.tabu = nullptr;
	lookUpTabu = a.lookUpTabu;
	a.lookUpTabu = nullptr;
	wayWeight = a.wayWeight;
}

Ant& Ant::operator= (Ant& a)
{
	if (this == &a)
	{
		return a;
	}
		i = a.i;
		edge = a.edge;
		memcpy(tabu, a.tabu, n*sizeof(int));
		memcpy(lookUpTabu, a.lookUpTabu, n*sizeof(int));
		wayWeight = a.wayWeight;
		return a;
}

Ant& Ant::operator= (Ant&& a)
{
		i = a.i;
		edge = a.edge;
		tabu = a.tabu;
		lookUpTabu = a.lookUpTabu;
		a.tabu = nullptr;
		a.lookUpTabu = nullptr;
		wayWeight = a.wayWeight;
		return a;
}

Ant::~Ant()
{
	delete[] tabu;
	delete[] lookUpTabu;
	tabu = nullptr;
	lookUpTabu = nullptr;
}

void Ant::setN(const int x)
{
	n = x;
}

// MAKING NEXT STEP OF AN ARTIFICIAL ANT
void Ant::walk(const PheromoneGraph* PG)
{
	int best_edge = 0;
    float best_value = -INFINITI;
	float prob;
    float q = qrand()/((double)RAND_MAX);
	if (q < Q0)
	{
		for (int i = 0; i < n; i++)
		{
			if (i != edge && lookUpTabu[i] == 0)
			{
                prob = PG->pheromoneMatrix[edge][i]*pow(1/ PG->matrix[edge][i], BETA);
				if (prob > best_value)
				{
                    best_value = prob;
                    best_edge = i;
				}
			}
		}
	}
	else
	{
        int k = qrand() % (n-i);
		int j = 0;
        while (k > 0 || lookUpTabu[j] != 0)
		{
            if (lookUpTabu[j] == 0)
				k--;
			j++;
		}
		best_edge = j;
	}
	tabu[i] = best_edge;
    lookUpTabu[best_edge] = 1;
    wayWeight+= PG->matrix[edge][best_edge];
	edge = best_edge;
	i++;
    if (i == PG->number_of_edges)
        wayWeight+= PG->matrix[edge][tabu[0]];
}

int Ant::getTabu(int j) const
{
	return tabu[j];
}

void Ant::setNumberOfVerticesTraversed(int a)
{
	i = a;
}

void Ant::setWayWeight(float a)
{
	wayWeight = a;
}

float Ant::calculate_pheromones() const
{
	return wayWeight;
}

void Ant::change_edge_randomly()
{
    edge = qrand() % n;
    tabu[0] = edge;
    lookUpTabu[edge] = 1;
}

void Ant::resetTabu()
{
    memset(lookUpTabu, 0, n*sizeof(int));
}
