#ifndef BOOST_UBLAS_DAVIDON_FLETCHER_POWELL_HPP
#define BOOST_UBLAS_DAVIDON_FLETCHER_POWELL_HPP

#include <cfloat> // DBL_EPSILON
#include <boost/assert.hpp>
#include "function.hpp"

namespace boost {
    namespace numeric {
        namespace ublas {
            namespace details {

                template <class T>
                T find_min(const Function<T> & f, const vector<T> & x, vector<T> const & d, T a, T b, const double eps = 1E-8) {
                    T e = 0;
                    T x_1 = T(0);
                    T x_2 = T(0);

                    while (std::abs(b - a) >= eps) {
                        e = (b - a) * 1E-2 * 1E-3;
                        x_1 = (b + a) / 2 - e;
                        x_2 = (b + a) / 2 + e;

                        if (f(x + x_1 * d) > f(x + x_2 * d)) {
                            a = x_1;
                        }
                        else {
                            b = x_2;
                        }
                    }
                    return (a + b) / 2;
                }
            } /* namespace details */

            template <class T>
            vector<T> DavidonFletcherPowell(const Function<T> & f, vector<T> x, const double epsilon, std::size_t & number_iteration) {
                BOOST_ASSERT(f.function);
                BOOST_ASSERT(f.gradient);

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

                for (; ublas::norm_2(grad) >= epsilon && number_iteration < 1E6; old_x = x, old_grad = grad, ++number_iteration) {
                    d = -prod(eta, grad);

                    // Looking for the minimum of F(x - alpha * d) using the method of one-dimensional optimization.
                    alpha = details::find_min(f, x, d, T(0.0), T(1E3));
                    BOOST_ASSERT(alpha >= DBL_EPSILON);

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
        } /* namespace ublas */
    } /* namespace numeric */
} /* namespace boost */
#endif