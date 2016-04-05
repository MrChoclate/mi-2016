#ifndef TYPES_H
#define TYPES_H


struct Particle {
  double x, y, weight;
};
typedef struct Particle Particle;


struct Beacon {
  double x, y;
  int n_rssi;
  double* rssi;
};
typedef struct Beacon Beacon;


struct Position {
  double x, y;
};
typedef struct Position Position;

#endif
