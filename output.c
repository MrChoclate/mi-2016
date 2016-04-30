#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types.h"

#define N_TRUE_POS 113


void precision(Position *estimates) {
  Position true_position[N_TRUE_POS] = {
    (Position) {.x=0.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=2.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=4.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=6.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=2.86,	.y=7.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=4.86,	.y=7.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=6.86,	.y=7.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=8.86,	.y=7.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=10.86,	.y=7.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=12.86,	.y=7.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=13.86,	.y=9.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=15.36,	.y=11.98},
    (Position) {.x=16.36,	.y=13.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=17.86,	.y=15.48},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=14.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=12.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=10.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=8.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=6.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=4.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=2.86,	.y=16.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=16.5},
    (Position) {.x=0.86,	.y=14.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=12.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=10.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=8.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=6.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=4.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=2.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=0.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=2.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=4.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=6.86,	.y=0.98},
    (Position) {.x=8.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=10.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=12.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=14.86,	.y=0.98},
    (Position) {.x=16.86,	.y=0.98},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=17.86,	.y=1.5},
    (Position) {.x=18.86,	.y=2.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=19.86,	.y=3.5},
    (Position) {.x=20.86,	.y=4.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=20.86,	.y=6.5},
    (Position) {.x=20.86,	.y=8.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=20.86,	.y=10.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=20.86,	.y=12.5},
    (Position) {.x=-1,	.y=-1},
    (Position) {.x=20.86,	.y=14.5},
  };

  double d_avg = 0, d_min = 1000, d_max = 0, d;
  int count = 0;

  for (size_t i = 0; i < N_TRUE_POS; i++) {
    if(true_position[i].x != -1) {
      d = sqrt((estimates[i].x - true_position[i].x) * (estimates[i].x - true_position[i].x) + (estimates[i].y - true_position[i].y) * (estimates[i].y - true_position[i].y));
      if (d < d_min) {
        d_min = d;
      }
      if (d > d_max) {
        d_max = d;
      }
      d_avg += d;
      count += 1;
      printf("%lf %lf %lf\n", d, (estimates[i].x - true_position[i].x), (estimates[i].y - true_position[i].y));
    }
  }
  d_avg /= count;
  printf("Max: %lf\nMin: %lf\nAvg: %lf\n", d_max, d_min, d_avg);
};
