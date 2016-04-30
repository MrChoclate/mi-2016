#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <omp.h>
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
  double random;
  int nthread = omp_get_num_threads();
  int* seed = init_seed(nthread);
  int rank;

  #pragma omp parallel for schedule(static) private(random, rank)
  for (int i = 0; i < Np; i++) {
    rank = omp_get_thread_num();
    random = gaussrand(seed, rank);
    particles[i].x += distance * cos(angle * 3.1415 / 180) + random * sqrt(variance);
    random = gaussrand(seed, rank);
    particles[i].y += distance * sin(angle * 3.1415 / 180) + random * sqrt(variance);
  }
  free(seed);
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
  double dist = 0;
  int count = 0;

  for (int i = 0; i < n_obs; i++) {
    if(finger_print.rssi[i] != 0) {  // We recorded this rssi
      dist += (rssi[i] - finger_print.rssi[i]) * (rssi[i] - finger_print.rssi[i]);
      count += 1;
    }
  }
  return sqrt(dist / count);
}

void normalize_weight(const int Np, Particle* particles) {
  double weight_sum = 0;
  #pragma omp parallel for schedule(static) reduction(+:weight_sum)
  for (int i = 0; i < Np; i++) {
    weight_sum += particles[i].weight;
  }
  #pragma omp parallel for schedule(static)
  for (int i = 0; i < Np; i++) {
    particles[i].weight /= weight_sum;
  }
}

void update_weight(const int Np, Particle* particles, int n_obs, double* rssi, int n_finger_prints, FingerPrint* finger_prints) {
  int finger_print_indice;
  double dist;
  #pragma omp parallel for schedule(static) private(finger_print_indice, dist)
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
  #pragma omp parallel for schedule(static) reduction(+:square_weight_sum)
  for (int i = 0; i < Np; i++) {
    square_weight_sum += particles[i].weight * particles[i].weight;
  }
  return 1. / square_weight_sum;
}

Particle* resample(const int Np, Particle* particles) {
  Particle *new_particles = malloc(Np * sizeof(Particle));
  #pragma omp parallel for schedule(static)
  for (int i = 0; i < Np; i++) {
    new_particles[i] = pick_particle(Np, particles);
    new_particles[i].weight = 1. / Np;
  }
  free(particles);
  return new_particles;
}

Position estimate(const int Np, Particle* particles) {
  double x = 0.0, y = 0.0;
  #pragma omp parallel for schedule(static) reduction(+:x,y)
  for (int i = 0; i < Np; i++) {
    x += particles[i].x * particles[i].weight;
    y += particles[i].y * particles[i].weight;
  }

  return (Position) {.x=x, .y=y};
}

Orientation get_orientation(double angle) {
  angle += 90;  // angle is now positive
  angle -= 360.0/16;  // quarter will be centered
  int quarters = angle / (360.0/8);
  assert(quarters >= 0);
  assert(quarters < 8);
  return quarters;
}

FingerPrint** sort_finger_prints(int n_finger_prints, FingerPrint* finger_prints) {
  assert(n_finger_prints % 8 == 0);
  FingerPrint** array = malloc(sizeof(FingerPrint*) * 8);
  for (int i = 0; i < 8; i++) {
    array[i] = malloc(sizeof(FingerPrint) * n_finger_prints / 8);
  }
  int indices[8] = {0};

  for (int i = 0; i < n_finger_prints; i++) {
    array[finger_prints[i].orientation][indices[finger_prints[i].orientation]] = finger_prints[i];
    indices[finger_prints[i].orientation] += 1;
  }
  return array;
}

Position* particle_filter(const int Np, double width, double height, int n_finger_prints, FingerPrint* finger_prints, int k_iteration, Data* datas, double variance) {
  Position* estimations = malloc(sizeof(Position) * k_iteration);
  Particle* particles = create_particles(Np, width, height);

  FingerPrint** sorted = sort_finger_prints(n_finger_prints, finger_prints);

  for (int k = 0; k < k_iteration; k++) {
    update_particle(Np, particles, datas[k].angle, datas[k].distance, variance);
    update_weight(Np, particles, N_RSSI, datas[k].rssi, n_finger_prints / 8, sorted[get_orientation(datas[k].angle)]);
    estimations[k] = estimate(Np, particles);

    if(effective_sample_size(Np, particles) <= Np/2) {
      particles = resample(Np, particles);
    }
  }

  free(particles);
  return estimations;
}
