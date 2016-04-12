#ifndef INPUT_H
#define INPUT_H

#include "types.h"

FingerPrint* read_finger_prints(const char* filename, int* n_finger_prints);
Data* read_data(const char *filename, int* n_data);

#endif
