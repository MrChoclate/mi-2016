#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "types.h"


#define PI acos(-1)


long M = INT_MAX;
int A = 1103515245;
int C = 12345;

int* init_seed(int n) {
		int* seed = malloc(sizeof(int) *n);
		for (int i = 0; i < n; i++) {
			seed[i] = time(0) * i;
		}
		return seed;
}

double randu(int* seed, int index)
{
	int num = A*seed[index] + C;
	seed[index] = num % M;
	return fabs(seed[index]/((double) M));
}

double gaussrand(int * seed, int index){
	double u = randu(seed, index);
	double v = randu(seed, index);
	double cosine = cos(2*PI*v);
	double rt = -2*log(u);
	return sqrt(rt)*cosine;
}


Particle pick_particle(const int Np, Particle* particles) {
	double random = (double) rand() / RAND_MAX;
	double weight_sum = 0;
	int i = 0;

	while(weight_sum < random) {
		weight_sum += particles[i].weight;
		i += 1;
	}

	return particles[i-1];
}
