#ifndef BOOST_UBLAS_NEWTON_HPP
#define BOOST_UBLAS_NEWTON_HPP

#include "function.hpp"
#include "invert_matrix.hpp"

namespace boost {
    namespace numeric {
        namespace ublas {
            template <class T>
            vector<T> Newton(const Function<T> & f, vector<T> x, const double epsilon, size_t & number_iteration) {
                BOOST_ASSERT(f.hessian);

                vector<T> grad(f.gradient(x));
                matrix<T> H(f.hessian(x));
                matrix<T> invert_H(f.size, f.size);

                for (; norm_2(grad) >= epsilon && number_iteration < 1E6; grad = f.gradient(x), H = f.hessian(x), ++number_iteration) {
                    InvertMatrix(H, invert_H);
                    x = x - prod(invert_H, grad);
                }

                return x;
            }
        } /* namespace ublas */
    } /* namespace numeric */
} /* namespace boost */

#endif