#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "test.hpp"

// 100 * (x_2 - x_1^2)^2 + (1 - x_1)^2
type_t function(const vector_t & x) {
    return 100 * pow(x[1] - x[0] * x[0], 2) + pow(1 - x[0], 2);
}

vector_t gradient(const vector_t & x) {
    vector_t grad(x.size());

    grad[0] = 2 * (200 * pow(x[0], 3) - 200 * x[0] * x[1] + x[0] - 1);
    grad[1] = 200 * (x[1] - x[0] * x[0]);

    return grad;
}

matrix_t hessian(const vector_t & x) {
    const auto size = x.size();
    matrix_t hessian(size, size);

    hessian(0, 0) = 1200 * x[0] * x[0] + -400 * x[1] + 2;
    hessian(0, 1) = -400 * x[0];
    hessian(1, 0) = hessian(0, 1);
    hessian(1, 1) = 200;

    return hessian;
}

// 4 + (x_1 - 5)^2 + (x_2 - 6)^2
type_t function1(const vector_t & x) {
    return 4 * (x[0] - 5) * (x[0] - 5) + (x[1] - 6) * (x[1] - 6);
}

vector_t gradient1(const vector_t & x) {
    vector_t grad(x.size());
    grad[0] = 8 * (x[0] - 5);
    grad[1] = 2 * (x[1] - 6);

    return grad;
}

// (x_2 - x_1^2)^2 + (1 - x_1)^2
type_t function2(const vector_t & x) {
    return pow(x[1] - x[0] * x[0], 2) + pow(1 - x[0], 2);
}

vector_t gradient2(const vector_t & x) {
    vector_t grad(x.size());
    grad[0] = 2. * ((x[1] - x[0] * x[0]) * (-2. * x[0]) + x[0] - 1.);
    grad[1] = 2. * (x[1] - x[0] * x[0]);

    return grad;
}

type_t function3(const vector_t & x) {
    return x[0] * x[0] + x[0] * x[1] + 5 * x[1] * x[1] - x[0] + 13 * x[1] + 10;
}

vector_t gradient3(const vector_t & x) {
    vector_t grad(x.size());

    grad[0] = 2 * x[0] + x[1] - 1;
    grad[1] = x[0] + 10 * x[1] + 13;

    return grad;
}
