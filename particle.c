#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include "types.h"
#include "random.h"


Particle* create_particles(const int Np, const double width, const double height) {
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

void update_particle(const int Np, Particle* particles, const double angle, const double distance, const double variance) {
  for (int i = 0; i < Np; i++) {
    particles[i].x += distance * cos(angle) + gaussrand() * sqrt(variance);
    particles[i].y += distance * sin(angle) + gaussrand() * sqrt(variance);
  }
}

int find_closest_finger_print(Particle p, int n_finger_prints, FingerPrint* finger_prints) {
  int j = 0;
  double dist_min = (p.x - finger_prints[0].x) * (p.x - finger_prints[0].x) + (p.y - finger_prints[0].y) * (p.y - finger_prints[0].y);
  double dist;
  for (int i = 1; i < n_finger_prints; i++) {
    dist = (p.x - finger_prints[i].x) * (p.x - finger_prints[i].x) + (p.y - finger_prints[i].y) * (p.y - finger_prints[i].y);
    if (dist < dist_min) {
      dist_min = dist;
      j = i;
    }
  }
  return j;
}

double euclidian_distance(int n_obs, double* rssi, FingerPrint finger_print) {
  double dist = DBL_MIN;  // distance > 0 since we will divide by it

  for (int i = 0; i < n_obs; i++) {
    if(finger_print.rssi[i] != 0)  // We recorded this rssi
      dist += (rssi[i] - finger_print.rssi[i]) * (rssi[i] - finger_print.rssi[i]);
  }
  return sqrt(dist);
}

void normalize_weight(const int Np, Particle* particles) {
  double weight_sum = 0;
  for (int i = 0; i < Np; i++) {
    weight_sum += particles[i].weight;
  }
  for (int i = 0; i < Np; i++) {
    particles[i].weight /= weight_sum;
  }
}

void update_weight(const int Np, Particle* particles, int n_obs, double* rssi, int n_finger_prints, FingerPrint* finger_prints) {
  int finger_print_indice;
  double dist;
  for (int i = 0; i < Np; i++) {
    finger_print_indice = find_closest_finger_print(particles[i], n_finger_prints, finger_prints);

    // Compute euclidian distance
    dist = euclidian_distance(n_obs, rssi, finger_prints[finger_print_indice]);

    // Update weight
    particles[i].weight *= 1 / dist;
  }

  normalize_weight(Np, particles);
}

double effective_sample_size(const int Np, Particle* particles) {
  double square_weight_sum = 0;
  for (int i = 0; i < Np; i++) {
    square_weight_sum += particles[i].weight * particles[i].weight;
  }
  return 1. / square_weight_sum;
}

Particle* resample(const int Np, Particle* particles) {
  Particle *new_particles = malloc(Np * sizeof(Particle));
  for (int i = 0; i < Np; i++) {
    new_particles[i] = pick_particle(Np, particles);
    new_particles[i].weight = 1. / Np;
  }
  free(particles);
  return new_particles;
}

Position estimate(const int Np, Particle* particles) {
  Position pos = {.x=0, .y=0};

  for (int i = 0; i < Np; i++) {
    pos.x = particles[i].x * particles[i].weight;
    pos.y = particles[i].y * particles[i].weight;
  }

  return pos;
}

Position* particle_filter(const int Np, double width, double height, int n_finger_prints, FingerPrint* finger_prints, int k_iteration, double* angle, double* distance, int n_obs, double** rssi, double variance) {
  Position* estimations = malloc(sizeof(Position) * k_iteration);
  Particle* particles = create_particles(Np, width, height);

  for (int k = 0; k < k_iteration; k++) {
    update_particle(Np, particles, angle[k], distance[k], variance);
    update_weight(Np, particles, n_obs, rssi[k], n_finger_prints, finger_prints);
    estimations[k] = estimate(Np, particles);

    if(effective_sample_size(Np, particles) <= Np/2) {
      particles = resample(Np, particles);
    }
  }

  free(particles);
  return estimations;
}
