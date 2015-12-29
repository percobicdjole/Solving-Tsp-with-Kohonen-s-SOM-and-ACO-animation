#pragma once
class Ant;
#include "PheromoneGraph.h"
#include "acoDialog.h"
class Ant
{
public:
	Ant();
	Ant(const Ant&);
	Ant(Ant&&);
	Ant& operator= (Ant&);
	Ant& operator= (Ant&& a);
	~Ant();
    void walk(const PheromoneGraph*);
	int getTabu(int) const;
	void setNumberOfVerticesTraversed(int);
	void setWayWeight(float);
	float calculate_pheromones() const;
	void change_edge_randomly();
	void resetTabu();
    void setN(const int);
    friend class PheromoneGraph;
    friend class AntSim;
private:
	int i;        // #edges traversed
	static int n;
	int edge;
	int* tabu;
	int* lookUpTabu;
	float wayWeight;
};
