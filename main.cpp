#include "boost/numeric/ublas/make_unbounded_array.hpp"

#include "boost/numeric/ublas/Newton.hpp"
#include "boost/numeric/ublas/Davidon_Fletcher_Powell.hpp"
#include <boost/numeric/ublas/io.hpp>

#include "test.hpp"

void print(const boost::numeric::ublas::Function<> & f, const vector_t & solution, double epsilon, std::size_t number_iteration) {
    std::cout << "Precision:            " << epsilon << std::endl;
    std::cout << "Number of iterations: " << number_iteration << std::endl;
    std::cout << "Function value:       " << f(solution) << std::endl;
    std::cout << "Computed solution:    " << solution << std::endl << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.precision(10);
    using namespace boost::numeric::ublas;

    auto epsilon = 1E-9;
    std::size_t number_iteration = 0;
    vector_t solution;

    Function<> f(2, function, gradient, hessian);
    //vector_t x(make_unbounded_array({ -1.2, 1.0 }));
    vector_t x(make_unbounded_array({ -0.5, 0.5 }));
    //vector_t x(make_unbounded_array({ -8.0, 9.0 }));

    solution = DavidonFletcherPowell(f, x, epsilon, number_iteration = 0);
    std::cout << "Davidon-Fletcher-Powell:" << std::endl;
    print(f, solution, epsilon, number_iteration);

    solution = Newton(f, x, epsilon, number_iteration = 0);
    std::cout << "Newton:" << std::endl;
    print(f, solution, epsilon, number_iteration);

    return 0;
}
