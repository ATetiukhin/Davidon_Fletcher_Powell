#pragma once

typedef double type_t;
using matrix_t = boost::numeric::ublas::matrix<type_t>;
using vector_t = boost::numeric::ublas::vector<type_t>;

// 100 * (x_2 - x_1^2)^2 + (1 - x_1)^2
type_t function(const vector_t & x);
vector_t gradient(const vector_t & x);
matrix_t hessian(const vector_t & x);

// 4 + (x_1 - 5)^2 + (x_2 - 6)^2
type_t function1(const vector_t & x);
vector_t gradient1(const vector_t & x);

// (x_2 - x_1^2)^2 + (1 - x_1)^2
type_t function2(const vector_t & x);
vector_t gradient2(const vector_t & x);

type_t function3(const vector_t & x);
vector_t gradient3(const vector_t & x);
