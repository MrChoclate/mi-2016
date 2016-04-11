#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "particle.h"
#include "input.h"

int main(int argc, char const *argv[]) {
  int n_finger_prints;

  read_finger_prints("map.csv", &n_finger_prints);

  return 0;
}
