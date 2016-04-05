#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include "types.h"
#include "random.h"


Particle* create_particles(int Np, double width, double height) {
  Particle* particles = malloc(sizeof(Particle) *  Np);

  double Nwidth = sqrt(Np * width / height);
  double Nheight = sqrt(Np * height / width);
  double delta_width = width / Nwidth;
  double delta_height = height  / Nheight;

  int i = 0;
  for (int w = 0; (w < Nwidth) && (i < Np); w++) {
    for (int h = 0; (h < Nheight) && (i < Np); h++) {
      particles[i] = (Particle) {
        .x=w * delta_width,
        .y=h * delta_height,
        .weight=1. / Np
      };
      i++;
    }
  }

  assert(i == Np);
  return particles;
}

void update_particle(int Np, Particle* particles, double angle, double distance, double variance) {
  for (int i = 0; i < Np; i++) {
    particles[i].x += distance * cos(angle) + gaussrand() * sqrt(variance);
    particles[i].y += distance * sin(angle) + gaussrand() * sqrt(variance);
  }
}

int find_closest_beacon(Particle p, int n_beacons, Beacon* beacons) {
  int j = 0;
  double dist_min = (p.x - beacons[0].x) * (p.x - beacons[0].x) + (p.y - beacons[0].y) * (p.y - beacons[0].y);
  double dist;
  for (int i = 1; i < n_beacons; i++) {
    dist = (p.x - beacons[i].x) * (p.x - beacons[i].x) + (p.y - beacons[i].y) * (p.y - beacons[i].y);
    if (dist < dist_min) {
      dist_min = dist;
      j = i;
    }
  }
  return j;
}

double euclidian_distance(int n_obs, double* rssi, Beacon beacon) {
  double dist = DBL_MIN;  // distance > 0 since we will divide by it
  assert(beacon.n_rssi ==  n_obs);

  for (int i = 0; i < n_obs; i++) {
    dist += (rssi[i] - beacon.rssi[i]) * (rssi[i] - beacon.rssi[i]);
  }
  return sqrt(dist);
}

void normalize_weight(int Np, Particle* particles) {
  double weight_sum = 0;
  for (int i = 0; i < Np; i++) {
    weight_sum += particles[i].weight;
  }
  for (int i = 0; i < Np; i++) {
    particles[i].weight /= weight_sum;
  }
}

void update_weight(int Np, Particle* particles, int n_obs, double* rssi, int n_beacons, Beacon* beacons) {
  int beacon_indice;
  double dist;
  for (int i = 0; i < Np; i++) {
    beacon_indice = find_closest_beacon(particles[i], n_beacons, beacons);

    // Compute euclidian distance
    dist = euclidian_distance(n_obs, rssi, beacons[beacon_indice]);

    // Update weight
    particles[i].weight *= 1 / dist;
  }

  normalize_weight(Np, particles);
}

double effective_sample_size(int Np, Particle* particles) {
  double square_weight_sum = 0;
  for (int i = 0; i < Np; i++) {
    square_weight_sum += particles[i].weight * particles[i].weight;
  }
  return 1. / square_weight_sum;
}

Particle* resample(int Np, Particle* particles) {
  Particle *new_particles = malloc(Np * sizeof(Particle));
  for (int i = 0; i < Np; i++) {
    new_particles[i] = pick_particle(Np, particles);
    new_particles[i].weight = 1. / Np;
  }
  free(particles);
  return new_particles;
}

Position estimate(int Np, Particle* particles) {
  Position pos = {.x=0, .y=0};

  for (int i = 0; i < Np; i++) {
    pos.x = particles[i].x * particles[i].weight;
    pos.y = particles[i].y * particles[i].weight;
  }

  return pos;
}
