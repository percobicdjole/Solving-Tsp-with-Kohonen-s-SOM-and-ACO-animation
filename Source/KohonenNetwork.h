#ifndef KOHONEN_H
#define KOHONEN_H

namespace kohonen
{
    const long INFINITI = 10000000;
    const int NUMBER_OF_ITERATIONS = 3000;
};

class KohonenNetwork
{
public:
	KohonenNetwork(int, float**);
	~KohonenNetwork();
	void Initiate();
    void FeedForward(const int);
    void Adaptation(const int);
    void Repair();
    float** getWeights() const { return weights; }
    int getInputSize() const
    {
        return INPUT_SIZE;
    }
    void deleteNeuron(int& i, int& number_of_neurons);
    int findClosestInput(const int neuron);
    void setLookUp(const int value);
    void UpdateLearningRate();
    void UpdateLambda();
private:
	const int INPUT_SIZE;
	float** weights;
	float** x;
	int* d;
    int counter;
    float LEARNING_RATE;
    float UPDATE_LEARNING_RATE;
    float LAMBDA;
    float UPDATE_LAMBDA;
    int* lookUp;
};

float euclidean_distance(float x1, float y1, float x2, float y2);
#endif
