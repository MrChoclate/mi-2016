#ifndef TYPES_H
#define TYPES_H

#define N_RSSI 6

enum Orientation {
  E, NE, N, NW, W, SW, S, SE
};
typedef enum Orientation Orientation;

enum RSSI {
  _56WR, Ml1B, tBfJ, z6SH, IKAo, T0Fy
};
typedef enum RSSI RSSI;

struct Particle {
  double x, y, weight;
};
typedef struct Particle Particle;


struct FingerPrint {
  double x, y;
  double* rssi;
  Orientation orientation;
};
typedef struct FingerPrint FingerPrint;


struct Position {
  double x, y;
};
typedef struct Position Position;

Orientation get_orientation_code(char* name);
RSSI get_rssi_code(char* name);

#endif
