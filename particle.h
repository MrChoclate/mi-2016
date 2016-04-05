#ifndef PARTICLE_H
#define PARTICLE_H


#include <stdlib.h>
#include "types.h"


/**
 * Create Np particles uniformly in a width * height room.
 * Returns a dynamicly array of particles (must be freed)
**/
Particle* create_particles(int Np, double width, double height);
void update_particle(int Np, Particle* particles, double angle, double distance, double variance);
void normalize_weight(int Np, Particle* particles);
void update_weight(int Np, Particle* particles, int n_obs, double* rssi, int n_beacons, Beacon* beacons);
int find_closest_beacon(Particle p, int n_beacons, Beacon* beacons);
double euclidian_distance(int n_obs, double* rssi, Beacon beacon);
double effective_sample_size(int Np, Particle* particles);
Particle* resample(int Np, Particle* particles);
Position estimate(int Np, Particle* particles);


#endif
