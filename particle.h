#ifndef PARTICLE_H
#define PARTICLE_H


#include <stdlib.h>
#include "types.h"


/**
 * Create Np particles uniformly in a width * height room.
 * Returns a dynamicly array of particles (must be freed)
**/
Particle* create_particles(const int Np, const double width, const double height);
void update_particle(const int Np, Particle* particles, const double angle, const double distance, const double variance);
void normalize_weight(const int Np, Particle* particles);
void update_weight(const int Np, Particle* particles, int n_obs, double* rssi, int n_finger_prints, FingerPrint* finger_prints);
int find_closest_finger_print(Particle p, int n_finger_prints, FingerPrint* finger_prints);
double euclidian_distance(int n_obs, double* rssi, FingerPrint finger_print);
double effective_sample_size(const int Np, Particle* particles);
Particle* resample(const int Np, Particle* particles);
Position estimate(const int Np, Particle* particles);
Position* particle_filter(const int Np, double width, double height, int n_finger_prints, FingerPrint* finger_prints, int k_iteration, double* angle, double* distance, int n_obs, double** rssi, double variance);

#endif
