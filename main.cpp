#include "Davidon_Fletcher_Powell.hpp"

typedef double type_t;

// 4 + (x_1 - 5)^2 + (x_2 - 6)^2
type_t function(const std_utils::ublas::vector<type_t> & x) {
    return 4 * (x[0] - 5) * (x[0] - 5) + (x[1] - 6) * (x[1] - 6);
}

std_utils::ublas::vector<type_t> gradient(const std_utils::ublas::vector<type_t> & x) {
    std_utils::ublas::vector<type_t> grad(x.size());
    grad[0] = 8 * (x[0] - 5);
    grad[1] = 2 * (x[1] - 6);

    return grad;
}

// (x_2 - x_1^2)^2 + (1 - x_1)^2
type_t function1(const std_utils::ublas::vector<type_t> & x) {
    return pow(x[1] - x[0] * x[0], 2) + pow(1 - x[0], 2);
}

std_utils::ublas::vector<type_t> gradient1(const std_utils::ublas::vector<type_t> & x) {
    std_utils::ublas::vector<type_t> grad(x.size());
    grad[0] = 2. * ((x[1] - x[0] * x[0]) * (-2. * x[0]) + x[0] - 1.);
    grad[1] = 2. * (x[1] - x[0] * x[0]);

    return grad;
}

type_t function2(const std_utils::ublas::vector<type_t> & x)
{
    return x[0] * x[0] + x[0] * x[1] + 5 * x[1] * x[1] - x[0] + 13 * x[1] + 10;
}

std_utils::ublas::vector<type_t> gradient2(const std_utils::ublas::vector<type_t> & x)
{
    std_utils::ublas::vector<type_t> grad(x.size());
    grad[0] = 2 * x[0] + x[1] - 1;
    grad[1] = x[0] + 10 * x[1] + 13;
    return grad;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    using namespace std_utils;
    std::cout.precision(10);

    auto epsilon = 1E-9;
    std::size_t number_iteration = 0;

    //Function<type_t> f(2, function, gradient);
    //ublas::vector<type_t> x(make_unbounded_array({ 8.0, 9.0 }));

    Function<type_t> f(2, function1, gradient1);
    //ublas::vector<type_t> x(make_unbounded_array({ -1.2, 1.0 }));
    //ublas::vector<type_t> x(make_unbounded_array({ -18.0, 19.0 }));
    ublas::vector<type_t> x(make_unbounded_array({ 18.0, -19.0 }));

    //Function<type_t> f(2, function2, gradient2);
    //ublas::vector<type_t> x(make_unbounded_array({ -1.2, 1.0 }));

    auto solution = DavidonFletcherPowell(f, x, epsilon, number_iteration);

    std::cout << "Precision:            " << epsilon << std::endl;
    std::cout << "Number of iterations: " << number_iteration << std::endl;
    std::cout << "Function value:       " << f(solution) << std::endl;
    std::cout << "Computed solution:    " << solution << std::endl;

    return 0;
}