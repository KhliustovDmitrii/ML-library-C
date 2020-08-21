#ifndef NEURALNETWORK_H_INCLUDED
#define NEURALNETWORK_H_INCLUDED
#define eps 0.001
typedef struct neuron
{
int id;//Id of the neuron in the network
int output_number, input_number;//Numbers of neurons connected
double output_val;
double threshold;
double * weight;
double alpha;//the parameter of activation function
struct neuron ** output_id;
struct neuron ** input_id;
} neuron;

int learn(neuron * first, neuron * last, double rate, double alpha, int epoch, double ** data, double ** response);//The first neuron, which we use for navigation in our structure
void output(neuron * n);//We are now concerned only with indicator output function. Later we will be able to expand the set of activation functions
int initialize(neuron * first, neuron * last, int num_layers);
double loss(double * x, double * y, int n);
void work(neuron * first, neuron * last, double * input, int n);

#endif // NEURALNETWORK_H_INCLUDED
