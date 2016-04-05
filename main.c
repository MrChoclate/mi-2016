#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "particle.h"

int main(int argc, char const *argv[]) {
  printf("Hello world !\n");

  Particle* particles = create_particles(10000, 90., 15.);
  for (int i = 0; i < 10000; i++) {
    printf("Particle{x=%f, y=%f, weight=%f}\n", particles[i].x, particles[i].y, particles[i].weight);
  }
  free(particles);

  return 0;
}
