#ifndef QUBITS_H
#define QUBITS_H

#include "linear_algebra/linear_algebra.h"

typedef vector qubit;

qubit *qubit_create();
qubit *qubit_create_init(const struct complex a0, const struct complex a1);

#endif