#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNetwork.h"

int learn(neuron * first, neuron * last, double rate, int epoch){
int i;
for(i = 0; i < epoch; i++){

}
}

void output(neuron * n){
double o;
int i;
o = 0;
for(i = 0; i < n.input_number; i++){
    o+=n.input_id[i].output_val*n.weight[i];
}

n.output_val = 1/(1+math.exp(-2*n.alpha*o));
}

int initialize(neuron * first, neuron * last, int num_layers){
    int i, j, k, in, on;
    double * w;
    neuron * current, * next;
    current = first;
    for(i = 0; i < num_layers; i++){
        on = current.output_number;
        for(j = 0; j < on; j++){
            next = current.output_id[j];
            in = next.input_number;
            w = next.weight;
            for(k = 0; k < in; k++){
                w[k] = eps;
            }
            next.threshold = 2*eps;
        }
        current = current.output_id[0];
    }
    return 1;
}
double loss(double * x, double * y, int n){
    int i;
    double res;
    res = 0;
    for(i = 0; i < n; i++){
        res = res + sqrt((x[i]-y[i])*(x[i]-y[i]));
    }
}
void work(neuron * first, neuron * last, double * input, int n){
    int i;
    neuron * fl;
    neuron * current;
    fl = first.output_id;
    for(i = 0; i < n; i++){
        fl[i].output_val = input[i];
    }
    current = first.output_id[0];
    while(current!=last){
        fl = current.output_id;
        for(i = 0; i < current.output_number; i++){
            output(fl[i]);
        }
    current = current.output_id[0];
    }
}
