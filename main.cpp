#include "Davidon_Fletcher_Powell.hpp"

double function(const std_utils::ublas::vector<double> & x) {
    return 4 * (x[0] - 5) * (x[0] - 5) + (x[1] - 6) * (x[1] - 6);
}

std_utils::ublas::vector<double> gradient(const std_utils::ublas::vector<double> & x) {
    std_utils::ublas::vector<double> grad(x.size());
    grad[0] = 8 * (x[0] - 5);
    grad[1] = 2 * (x[1] - 6);

    return grad;
}

int main() {
    using namespace std_utils;
    std::cout.precision(9);

    Function<double> f(2, function, gradient);
    ublas::vector<double> x(make_unbounded_array({8.0, 9.0}));
    const double epsilon = 1E-6;

    auto solution = DavidonFletcherPowell(f, x, epsilon);

    std::cout << "Computed solution:" << std::endl;
    std::cout << solution << std::endl;
    std::cout << "Function value: " << f(solution) << std::endl << std::endl;

    return 0;
}