#include "linear_algebra.h"
#define SMART_DEALLOCATION
#include "../smart_allocation/smart_allocation.h"

struct matrix *matrix_create(const unsigned int rows, const unsigned int columns) {
    struct matrix *temp = (struct matrix *)smart_allocate(1, sizeof(struct matrix));
    temp->rows = rows;
    temp->columns = columns;
    temp->fields = (struct complex *)smart_allocate(rows*columns, sizeof(struct complex));
    B(temp, temp->fields)
    for(unsigned int i = 0; i < rows; i++) {
        INDEX(temp, i, i % columns) = complex_create(1, 0);
    }
    return temp;
}
struct matrix *matrix_create_empty(const unsigned int rows, const unsigned int columns) {
    struct matrix *temp = (struct matrix *)smart_allocate(1, sizeof(struct matrix));
    temp->rows = rows;
    temp->columns = columns;
    temp->fields = (struct complex *)smart_allocate(rows*columns, sizeof(struct complex));
    B(temp, temp->fields)
    return temp;
}

void matrix_print(const struct matrix * const m) {
    if(!m) return;

    for(unsigned int i = 0; i < m->rows; i++) {
        for(unsigned int j = 0; j < m->columns; j++) {
            complex_print(INDEX(m, i, j));
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
            INDEX(result, i, j) = complex_add(INDEX(m1, i, j), INDEX(m2, i, j));
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
            INDEX(result, i, j) = complex_sub(INDEX(m1, i, j), INDEX(m2, i, j));
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
        struct complex temp = complex_mul(INDEX(m1, i, count), INDEX(m2, count, j));
        result = complex_add(result, temp);
    }
    return result;
}
struct matrix *matrix_mul(const struct matrix * const m1, const struct matrix * const m2) {
    if(!m1 || !m2) return NULL;

    if(m1->rows == 1 && m1->columns == 1) {
        return matrix_mul_scalar(INDEX(m1, 0, 0), m2);
    }
    if(m2->rows == 1 && m2->columns == 1) {
        return matrix_mul_scalar(INDEX(m2, 0, 0), m1);
    }

    if(m1->columns != m2->rows) return NULL;

    struct matrix *result = matrix_create_empty(m1->rows, m2->columns);
    for(unsigned int i = 0; i < m1->rows; i++) {
        for(unsigned int j = 0; j < m2->columns; j++) {
            INDEX(result, i, j) = matrix_get_field_mul_value(m1, m2, i, j);
        }
    }
    return result;
}
struct matrix *matrix_mul_scalar(const struct complex s, const struct matrix * const m) {
    if(!m) return NULL;

    struct matrix *result = matrix_create_empty(m->rows, m->columns);
    for(unsigned int i = 0; i < m->rows; i++) {
        for(unsigned int j = 0; j < m->columns; j++) {
            INDEX(result, i, j) = complex_mul(s, INDEX(m, i, j));
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
            INDEX(result, i, j) = complex_mul(
                INDEX(m1, i / m2->rows, j / m2->columns),
                INDEX(m2, i % m2->rows, j % m2->columns)
            );
        }
    }
    return result;
}
struct matrix *matrix_tensor_product_n_times(const struct matrix * const m, 
                                                const unsigned int n) 
{
    if(!m || !n) return NULL;
    S
    struct matrix *result = (struct matrix *)m;
    for(unsigned int i = 1; i < n; i++) {
        result = matrix_tensor_product(result, m);
    }
    P(result)
    E
    return result;
}

struct matrix *matrix_transpose(const struct matrix * const m) {
    if(!m) return NULL;

    struct matrix *result = matrix_create_empty(m->columns, m->rows);
    for(unsigned int i = 0; i < m->columns; i++) {
        for(unsigned int j = 0; j < m->rows; j++) {
            INDEX(result, i, j) = INDEX(m, j, i);
        }
    }
    return result;
}

struct matrix *matrix_get_adjoint(const struct matrix * const m) {
    if(!m) return NULL;

    struct matrix *result = matrix_create_empty(m->columns, m->rows);
    for(unsigned int i = 0; i < m->columns; i++) {
        for(unsigned int j = 0; j < m->rows; j++) {
            struct complex num =INDEX(m, j, i);
            num = complex_get_conjugate(num);
            INDEX(result, i, j) = num;
        }
    }
    return result;
}

struct complex matrix_get_trace(const struct matrix * const m) {
    if(!m) return complex_create(0, 0);
    if(m->rows != m->columns) complex_create(0, 0);

    struct complex result = complex_create(0, 0);
    for(unsigned int i = 0; i < m->rows; i++) {
        result = complex_add(INDEX(m, i, i), result);
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
            INDEX(result, i, j) = complex_add(
                INDEX(m, i * (space_index + 1), j * (space_index + 1)), 
                INDEX(m, i * (space_index + 1) + (spaces - space_index), 
                         j * (space_index + 1) + (spaces - space_index))
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
    INDEX(temp, 0, 0) = num1;
    INDEX(temp, 1, 0) = num2;
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
    struct complex result = INDEX(temp, 0, 0);
    return result;
}