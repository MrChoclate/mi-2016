#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include "types.h"

/**
 * Generate a N(0, 1) sample
**/
double gaussrand();

/**
 * Pick a particle based on the weight
 **/
Particle pick_particle(int Np, Particle* particles);

#endif
