#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "particle.h"
#include "input.h"
#include "output.h"


int main(int argc, char const *argv[]) {
  int n_finger_prints;
  int n_data;

  FingerPrint* finger_prints = read_finger_prints("map.csv", &n_finger_prints);
  Data* datas = read_data("data.csv", &n_data);

  Position* estimates = particle_filter(100000, 5.0, 5.0, n_finger_prints, finger_prints, n_data, datas,  0.05);

  precision(estimates);

  return 0;
}
