#include <stdlib.h>

#include "linear_algebra.h"

struct matrix *matrix_create(const unsigned int rows, const unsigned int columns) {
    struct matrix *temp = (struct matrix *)calloc(1, sizeof(struct matrix));
    temp->rows = rows;
    temp->columns = columns;
    temp->fields = (struct complex **)calloc(rows, sizeof(struct complex *));
    for(unsigned int i = 0; i < rows; i++) {
        temp->fields[i] = (struct complex *)calloc(columns, sizeof(struct complex));
        temp->fields[i][i % columns] = complex_create(1, 0);
    }
    return temp;
}