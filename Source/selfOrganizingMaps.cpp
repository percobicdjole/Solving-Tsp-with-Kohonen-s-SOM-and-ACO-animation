#include <iostream>
#include "KohonenNetwork.h"
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace kohonen;

KohonenNetwork::KohonenNetwork(int i, float** X) : INPUT_SIZE(i)
{
    LAMBDA = 500;
    weights = new float*[INPUT_SIZE];
    lookUp = new int[INPUT_SIZE]();
	d = new int[INPUT_SIZE];
    for (int i = 0; i < INPUT_SIZE; i++)
		weights[i] = new float[2];
	x = X;
    counter = 0;
	Initiate();
    if (INPUT_SIZE <= 100)
    {
        LEARNING_RATE = 0.2;
        UPDATE_LEARNING_RATE = 0.9997;
        UPDATE_LAMBDA = 0.999;
    }
    else
    {
        LEARNING_RATE = 0.7;
        UPDATE_LEARNING_RATE = 0.999985;
        UPDATE_LAMBDA = 0.9994;
    }
}

KohonenNetwork::~KohonenNetwork()
{
    for (int i = 0; i < INPUT_SIZE; i++)
		delete[] weights[i];
	delete[] weights;
	delete[] d;
	delete[] lookUp;
}

inline void KohonenNetwork::Initiate()
{
    for (int j = 0; j < INPUT_SIZE; j++)
    {
        weights[j][0] = rand()/(double)RAND_MAX*50 + 425;
        weights[j][1] = rand()/(double)RAND_MAX*50 + 425;
    }
}

void KohonenNetwork::FeedForward(const int i)   // Da odradim potez sa jednim pa nastavim od drugog tek tada
{
    float min;
    double k;
    //lookUp = new int[INPUT_SIZE]();
        min = INFINITI;
        for (int j = 0; j < INPUT_SIZE; j++)
		{
            k = euclidean_distance(x[i][0], x[i][1], weights[j][0], weights[j][1]);
            if (k < min && lookUp[j] == 0)
			{ 
				min = k;
				d[i] = j;
			}
		}
        lookUp[d[i]] = 1;
}

inline float learn(float w, float x, float n)
{
    return (w+n*(x-w));
}

void KohonenNetwork::Adaptation(const int i)
{
        weights[d[i]][0] = learn(weights[d[i]][0], x[i][0], LEARNING_RATE);
        weights[d[i]][1] = learn(weights[d[i]][1], x[i][1], LEARNING_RATE);
        if (d[i] > 0 && euclidean_distance(weights[d[i]-1][0], weights[d[i]-1][1], x[i][0], x[i][1]) <= LAMBDA)
        {
            weights[d[i]-1][0] = learn(weights[d[i]-1][0], x[i][0], LEARNING_RATE);
            weights[d[i]-1][1] = learn(weights[d[i]-1][1], x[i][1], 2*LEARNING_RATE);
        }
        if (d[i] < INPUT_SIZE-1 && euclidean_distance(weights[d[i]+1][0], weights[d[i]+1][1], x[i][0], x[i][1]) <= LAMBDA)
        {
            weights[d[i]+1][0] = learn(weights[d[i]+1][0], x[i][0], LEARNING_RATE);
            weights[d[i]+1][1] = learn(weights[d[i]+1][1], x[i][1], 2*LEARNING_RATE);
        }
}

void KohonenNetwork::UpdateLearningRate()
{
    LEARNING_RATE*= UPDATE_LEARNING_RATE;
}

void KohonenNetwork::UpdateLambda()
{
    LAMBDA*= UPDATE_LAMBDA;
}

void KohonenNetwork::deleteNeuron(int& i, int& number_of_neurons)
{
    for (int j = i; j < number_of_neurons-1; j++)
    {
        weights[j][0] = weights[j+1][0];
        weights[j][1] = weights[j+1][1];
    }
    number_of_neurons--;
    i--;
}

int KohonenNetwork::findClosestInput(const int neuron)
{
    float min = INFINITI;
    float t;
    int closestNode;
    for (int j = 0; j < INPUT_SIZE; j++)
    {
        t = euclidean_distance(x[j][0], x[j][1], weights[neuron][0], weights[neuron][1]);
        if (t < min)
        {
            min = t;
            closestNode = j;
        }
    }   // postavi weights = x
    weights[neuron][0] = x[closestNode][0];
    weights[neuron][1] = x[closestNode][1];
    return closestNode;
}

void KohonenNetwork::Repair()
{
    int number_of_neurons = INPUT_SIZE;
    int inp;
    for (int i = 0; i < number_of_neurons; i++)
    {
            inp = findClosestInput(i);
            if (lookUp[inp] == 1)
                deleteNeuron(i, number_of_neurons);
            else
                lookUp[inp] = 1;
    }

    for (int i = 0; i < INPUT_SIZE && number_of_neurons != INPUT_SIZE; i++)
    {
        if (lookUp[i] == 0)
        {
            int x1, y1;
            x1 = x[i][0];
            y1 = x[i][1];
            int min = INFINITI;
            int minNeuron;
            float mini;
            for (int j = 0; j < number_of_neurons; j++)
            {
                mini = euclidean_distance(weights[j][0], weights[j][1], x1, y1);
                if (mini < min)
                {
                    minNeuron = j;
                    min = mini;
                }
            }
            mini = 0;
            min = 0;
            if (minNeuron > 0)
            {
                 mini = euclidean_distance(weights[minNeuron-1][0], weights[minNeuron-1][1], x1, y1);
                 min = 0;
            }
            if (minNeuron < number_of_neurons-1)
            {
                if (mini > euclidean_distance(weights[minNeuron+1][0], weights[minNeuron+1][1], x1, y1))
                    mini = euclidean_distance(weights[minNeuron+1][0], weights[minNeuron+1][1], x1, y1);
                min = 1;
            }
            for (int j = number_of_neurons-1; j > minNeuron; j--)
            {
                weights[j+1][0] = weights[j][0];
                weights[j+1][1] = weights[j][1];
            }
            if (min == 0)
            {
                weights[minNeuron+1][0] = weights[minNeuron][0];
                weights[minNeuron+1][1] = weights[minNeuron][1];
                weights[minNeuron][0] = x1;
                weights[minNeuron][1] = y1;
            }
            else
            {
                weights[minNeuron+1][0] = x1;
                weights[minNeuron+1][1] = y1;
            }
            number_of_neurons++;

            lookUp[i] = 1;
        }
    }
}

void KohonenNetwork::setLookUp(const int value)
{
    memset(lookUp, value, INPUT_SIZE*sizeof(int));
}
