#pragma once

#include <boost/assert.hpp>
#include <boost/function.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace std_utils {
    namespace ublas = boost::numeric::ublas;

    template <typename T>
    ublas::unbounded_array<T> make_unbounded_array(std::initializer_list<T> list) {
        std::size_t size = list.size();
        ublas::unbounded_array<T> result(size);
        for (size_t i = 0; i < size; ++i)
            result[i] = *(list.begin() + i);
        return result;
    }

    template <class T> struct Function {
        const std::size_t size;
        const boost::function<T(const ublas::vector<T> &)> function;
        const boost::function<ublas::vector<T>(const ublas::vector<T> &)> gradient;

        Function(std::size_t size,
            boost::function<T(const ublas::vector<T> &)> f,
            boost::function<ublas::vector<T>(const ublas::vector<T> &)> grad)
            : size(size)
            , function(f)
            , gradient(grad) {
        }

        Function & operator = (const Function & other) {
            if (this != &other) {
                size = other.size;
                function = other.function;
                gradient = other.gradient;
            }

            return *this;
        }

        T operator()(const ublas::vector<T> & x) const {
            return function(x);
        }
    };

    namespace details {
        template <class T>
        T find_min(const std_utils::Function<T> & f, const ublas::vector<T> & x, ublas::vector<T> const & d, T a, T b, const double eps = 1E-8) {
            T e = 0;
            T x_1 = T(0);
            T x_2 = T(0);

            while (std::abs(b - a) >= eps) {
                e = (b - a) * 1E-2 * 1E-3;
                x_1 = (b + a) / 2 - e;
                x_2 = (b + a) / 2 + e;

                if (f(x + x_1 * d) > f(x + x_2 * d)) {
                    a = x_1;
                } else {
                    b = x_2;
                }
            }

            BOOST_ASSERT((a + b) / 2 >= 0.0);
            return (a + b) / 2;
        }
    }

    template <class T>
    ublas::vector<T> DavidonFletcherPowell(const Function<T> & f, ublas::vector<T> x, const double epsilon) {
        using namespace ublas;

        vector<T> grad(f.gradient(x));
        matrix<T> eta(identity_matrix<T>(f.size));
        vector<T> old_x = x;
        vector<T> old_grad = grad;

        vector<T> d;
        T alpha = T(0);

        vector<T> delta_x;
        vector<T> delta_g;
        matrix<T> A;
        matrix<T> B;

        for (; ublas::norm_2(grad) >= epsilon; old_x = x, old_grad = grad) {
            d = -prod(eta, grad);

            // Looking for the minimum of F(x - alpha * d) using the method of one-dimensional optimization.
            alpha = details::find_min(f, x, d, T(0), T(1E5));
            x = x + alpha * d;
            grad = f.gradient(x);

            delta_x = x - old_x;
            delta_g = grad - old_grad;

            A = (outer_prod(delta_x, delta_x) / inner_prod(delta_x, delta_g));

            B = prod(outer_prod(static_cast<vector<T>>(prod(eta, delta_g)), delta_g), trans(eta))
                / inner_prod(static_cast<vector<T>>(prod(static_cast<vector<T>>(prod(identity_matrix<T>(f.size), delta_g)), eta)), delta_g);

            eta = eta + A - B;
        }

        return x;
    }
}
