#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NeuralNetwork.h"

int main(){
return 0;
}

int learn(neuron * first, neuron * last, double rate, double alpha, int epoch, double ** data, double ** response){
int i, n, j, num_neurons, k, resp_length, s, l, num_pairs, z;
double sum;
double* out;
double * delta;
double * delta_w;
neuron * current;
n = first->output_number;
current = first;
num_neurons = 0;
num_pairs = 0;
while(current->output_id[0]!=last){
    num_neurons+=current->output_number;
    num_pairs+=(current->output_number)*(current->output_id[0]->input_number);
    current = current->output_id[0];
}
num_pairs-=first->output_number;
num_pairs-=last->input_number;
out = (double*)malloc(num_neurons*sizeof(double));
delta = (double *)malloc(num_neurons*sizeof(double));
delta_w = (double *)malloc(num_pairs*sizeof(double));
for(i = 0; i < num_pairs; i++){
    delta_w[i] = 0;
}
resp_length = last->input_number;
for(i = 0; i < epoch; i++){
    current = first;
    k = 0;
    work(first, last, data[i], n);//Apply network to data
    while(current->output_id[0]!=last){//Create array of neurons outputs
        for(j = 0; j < current->output_number; j++){
                out[k] = current->output_id[j]->output_val;//I am not sure this is to be written this way @added ->output_val@
                k++;
        }
        current = current->output_id[0];
    }
    for(j = num_neurons-1; j > num_neurons - resp_length-1; j--){//The errors of the last layer
        delta[j] = (-1)*out[j]*(1-out[j])*(response[i][resp_length-j-num_neurons+resp_length+1]-out[j]);
    }
    current = last->input_id[0];
    while(current->input_id[0]!=first){
        n = current->input_number;
        for(k = 0; k < n; k++){
                sum = 0;
                current = current->input_id[k];
                l = current->output_number;
                for(s = 0; s < l; s++){
                    sum+=delta[j + k + s]*current->output_id[s]->weight[k];
                }
                delta[j] = out[j]*(1-out[j])*sum;
                current = current->output_id[0];
                j = j-1;
        }
        current = current->input_id[0];
    }
    k = 0;
    s = 0;
    z = 0;
    current = first;
    while(current->output_id[0]!=last){
        l = current->output_number;
        n = current->output_id[0]->output_number;
        z += l;
        for(s = 0; s < l; s++){
            for(j = 0; j < n; j++){
                delta_w[k] = alpha*delta_w[k] + (1-alpha)*rate*delta[z]*current->output_id[s]->output_val;
                current->output_id[0]->output_id[j]->weight[s]+=delta_w[k];
                k++;
                z++;
            }
            z-=n;
        }
    }
}
free(out);
free(delta);
free(delta_w);
}

void output(neuron * n){
double o;
int i;
o = 0;
for(i = 0; i < n->input_number; i++){
    o+=n->input_id[i]->output_val*n->weight[i];
}

n->output_val = 1/(1+exp(-2*n->alpha*o));
}

int initialize(neuron * first, neuron * last, int num_layers){
    int i, j, k, in, on;
    double * w;
    neuron * current, * next;
    current = first;
    for(i = 0; i < num_layers; i++){
        on = current->output_number;
        for(j = 0; j < on; j++){
            next = current->output_id[j];
            in = next->input_number;
            w = next->weight;
            for(k = 0; k < in; k++){
                w[k] = eps;
            }
            next->threshold = 2*eps;
        }
        current = current->output_id[0];
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
    neuron ** fl;
    neuron * current;
    fl = first->output_id;
    for(i = 0; i < n; i++){
        fl[i]->output_val = input[i];
    }
    current = first->output_id[0];
    while(current!=last){
        fl = current->output_id;
        for(i = 0; i < current->output_number; i++){
            output(fl[i]);
        }
    current = current->output_id[0];
    }
}
