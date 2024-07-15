#include "linear_algebra.h"
#include "../smart_allocation/smart_allocation.h"

struct matrix *matrix_create(const unsigned int rows, const unsigned int columns) {
    struct matrix *temp = (struct matrix *)smart_allocate(1, sizeof(struct matrix));
    temp->rows = rows;
    temp->columns = columns;
    temp->fields = (struct complex **)smart_allocate(rows, sizeof(struct complex *));
    for(unsigned int i = 0; i < rows; i++) {
        temp->fields[i] = (struct complex *)smart_allocate(columns, sizeof(struct complex));
        temp->fields[i][i % columns] = complex_create(1, 0);
    }
    return temp;
}