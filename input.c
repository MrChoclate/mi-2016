#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "types.h"

double* parse_rssi(const char *data) {
  double* rssi = malloc(sizeof(double) * N_RSSI);

  char rssi_name[100];
  int rssi_value, n;
  while(sscanf(data, "%[^{}:]:%d;%n", rssi_name, &rssi_value, &n) == 2) {
    data += n;
    rssi[get_rssi_code(rssi_name)] = rssi_value;
  }

  return rssi;
}

FingerPrint* read_finger_prints(const char* filename, int* n_finger_prints) {
  double x, y;
  char o[10], rssis[100];
  int i = 0;
  FILE *fp = fopen(filename, "r");
  assert(fp != NULL);

  // Count the number of line
  char ch;
  *n_finger_prints = 0;
  do {
    ch = fgetc(fp);
    if (ch == '\n')
      *n_finger_prints += 1;
  } while (ch != EOF);
  rewind(fp);  // reset file position indicator

  // Parse the input
  FingerPrint* finger_prints = malloc(sizeof(FingerPrint) * (*n_finger_prints));
  while(fscanf(fp, "%lf ; %lf ; %s ; %s", &x, &y, o, rssis) == 4) {

    finger_prints[i] = (FingerPrint) {
      .x=x,
      .y=y,
      .orientation=get_orientation_code(o),
      .rssi=parse_rssi(rssis)
    };
    i++;
  }
  fclose(fp);
  return finger_prints;
}
