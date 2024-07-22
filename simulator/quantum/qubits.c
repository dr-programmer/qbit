#include "qubits.h"

qubit *qubit_create() {
    qubit *temp = vector_create();
    return temp;
}
qubit *qubit_create_init(const struct complex a0, const struct complex a1) {
    qubit *temp = vector_create_init(a0, a1);
    return temp;
}