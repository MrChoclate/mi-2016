#include <stdlib.h>
#include <string.h>
#include "types.h"

Orientation get_orientation_code(char* name) {
  if(strcmp(name, "E") == 0)
    return E;
  if(strcmp(name, "NE") == 0)
    return NE;
  if(strcmp(name, "N") == 0)
    return N;
  if(strcmp(name, "NW") == 0)
    return NW;
  if(strcmp(name, "W") == 0)
    return W;
  if(strcmp(name, "SW") == 0)
    return SW;
  if(strcmp(name, "S") == 0)
    return S;
  if(strcmp(name, "SE") == 0)
    return SE;

  return -1;
}

RSSI get_rssi_code(char* name) {
  if(strcmp(name, "56WR") == 0) {
    return _56WR;
  }
  if(strcmp(name, "Ml1B") == 0) {
    return Ml1B;
  }
  if(strcmp(name, "tBfJ") == 0) {
    return tBfJ;
  }
  if(strcmp(name, "z6SH") == 0) {
    return z6SH;
  }
  if(strcmp(name, "IKAo") == 0) {
    return IKAo;
  }
  if(strcmp(name, "T0Fy") == 0) {
    return T0Fy;
  }

  return -1;
}
