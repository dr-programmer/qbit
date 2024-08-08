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
struct matrix *matrix_create_empty(const unsigned int rows, const unsigned int columns) {
    struct matrix *temp = (struct matrix *)smart_allocate(1, sizeof(struct matrix));
    temp->rows = rows;
    temp->columns = columns;
    temp->fields = (struct complex **)smart_allocate(rows, sizeof(struct complex *));
    for(unsigned int i = 0; i < rows; i++) {
        temp->fields[i] = (struct complex *)smart_allocate(columns, sizeof(struct complex));
    }
    return temp;
}

void matrix_print(const struct matrix * const m) {
    if(!m) return;

    for(unsigned int i = 0; i < m->rows; i++) {
        for(unsigned int j = 0; j < m->columns; j++) {
            complex_print(m->fields[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

struct matrix *matrix_add(const struct matrix * const m1, const struct matrix * const m2) {
    if(!m1 || !m2) return NULL;
    if(m1->rows != m2->rows || m1->columns != m2->columns) return NULL;

    struct matrix *result = matrix_create_empty(m1->rows, m2->columns);
    for(unsigned int i = 0; i < m1->rows; i++) {
        for(unsigned int j = 0; j < m1->columns; j++) {
            result->fields[i][j] = complex_add(m1->fields[i][j], m2->fields[i][j]);
        }
    }
    return result;
}
struct matrix *matrix_sub(const struct matrix * const m1, const struct matrix * const m2) {
    if(!m1 || !m2) return NULL;
    if(m1->rows != m2->rows || m1->columns != m2->columns) return NULL;

    struct matrix *result = matrix_create_empty(m1->rows, m2->columns);
    for(unsigned int i = 0; i < m1->rows; i++) {
        for(unsigned int j = 0; j < m1->columns; j++) {
            result->fields[i][j] = complex_sub(m1->fields[i][j], m2->fields[i][j]);
        }
    }
    return result;
}
static struct complex matrix_get_field_mul_value(const struct matrix * const m1, 
                                                    const struct matrix * const m2, 
                                                    const unsigned int i, 
                                                    const unsigned int j) 
{
    struct complex result = {0, 0};
    for(unsigned int count = 0; count < m1->columns; count++) {
        struct complex temp = complex_mul(m1->fields[i][count], m2->fields[count][j]);
        result = complex_add(result, temp);
    }
    return result;
}
struct matrix *matrix_mul(const struct matrix * const m1, const struct matrix * const m2) {
    if(!m1 || !m2) return NULL;

    if(m1->rows == 1 && m1->columns == 1) {
        return matrix_mul_scalar(m1->fields[0][0], m2);
    }
    if(m2->rows == 1 && m2->columns == 1) {
        return matrix_mul_scalar(m2->fields[0][0], m1);
    }

    if(m1->columns != m2->rows) return NULL;

    struct matrix *result = matrix_create_empty(m1->rows, m2->columns);
    for(unsigned int i = 0; i < m1->rows; i++) {
        for(unsigned int j = 0; j < m2->columns; j++) {
            result->fields[i][j] = matrix_get_field_mul_value(m1, m2, i, j);
        }
    }
    return result;
}
struct matrix *matrix_mul_scalar(const struct complex s, const struct matrix * const m) {
    if(!m) return NULL;

    struct matrix *result = matrix_create_empty(m->rows, m->columns);
    for(unsigned int i = 0; i < m->rows; i++) {
        for(unsigned int j = 0; j < m->columns; j++) {
            result->fields[i][j] = complex_mul(s, m->fields[i][j]);
        }
    }
    return result;
}

struct matrix *matrix_tensor_product(const struct matrix * const m1, 
                                        const struct matrix * const m2) 
{
    if(!m1 || !m2) return NULL;

    struct matrix *result = matrix_create_empty(m1->rows * m2->rows, 
                                                    m1->columns * m2->columns);
    for(unsigned int i = 0; i < result->rows; i++) {
        for(unsigned int j = 0; j < result->columns; j++) {
            result->fields[i][j] = complex_mul(
                m1->fields[i / m2->rows][j / m2->columns], 
                m2->fields[i % m2->rows][j % m2->columns]
            );
        }
    }
    return result;
}

struct matrix *matrix_transpose(const struct matrix * const m) {
    if(!m) return NULL;

    struct matrix *result = matrix_create_empty(m->columns, m->rows);
    for(unsigned int i = 0; i < m->columns; i++) {
        for(unsigned int j = 0; j < m->rows; j++) {
            result->fields[i][j] = m->fields[j][i];
        }
    }
    return result;
}

struct matrix *matrix_get_adjoint(const struct matrix * const m) {
    if(!m) return NULL;

    struct matrix *result = matrix_create_empty(m->columns, m->rows);
    for(unsigned int i = 0; i < m->columns; i++) {
        for(unsigned int j = 0; j < m->rows; j++) {
            struct complex num = m->fields[j][i];
            num = complex_get_conjugate(num);
            result->fields[i][j] = num;
        }
    }
    return result;
}

struct complex matrix_get_trace(const struct matrix * const m) {
    if(!m) return complex_create(0, 0);
    if(m->rows != m->columns) complex_create(0, 0);

    struct complex result = complex_create(0, 0);
    for(unsigned int i = 0; i < m->rows; i++) {
        result = complex_add(m->fields[i][i], result);
    }

    return result;
}
struct matrix *matrix_get_partial_trace(const struct matrix * const m, 
                                            const unsigned int space_index, 
                                            const unsigned int spaces) 
{
    if(!m) return NULL;
    if(m->rows != m->columns) return NULL;

    unsigned int space_size = m->rows / spaces;
    struct matrix *result = matrix_create_empty(space_size, space_size);
    for(unsigned int i = 0; i < space_size; i++) {
        for(unsigned int j = 0; j < space_size; j++) {
            result->fields[i][j] = complex_add(
                m->fields[i * (space_index + 1)][j * (space_index + 1)], 
                m->fields[i + (spaces - space_index)][j + (spaces - space_index)]
            );
        }
    }

    return result;
}

vector *vector_create() {
    vector *temp = matrix_create_empty(2, 1);
    return temp;
}
vector *vector_create_init(struct complex num1, struct complex num2) {
    vector *temp = vector_create();
    temp->fields[0][0] = num1;
    temp->fields[1][0] = num2;
    return temp;
}

dual_vector *vector_get_dual(const vector * const v) {
    if(!v) return NULL;

    dual_vector *result = matrix_get_adjoint(v);
    return result;
}

struct complex vector_inner_product(const vector * const v1, const vector * const v2) {
    if(!v1 || !v2) return complex_create(0, 0);
    if(v1->rows != v2->rows) return complex_create(0, 0);

    dual_vector *dual_v1 = vector_get_dual(v1);
    struct matrix *temp = matrix_mul(dual_v1, v2);
    struct complex result = temp->fields[0][0];
    return result;
}