#ifndef BOOST_UBLAS_FUNCTION_HPP
#define BOOST_UBLAS_FUNCTION_HPP

#include <boost/function.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace boost {
    namespace numeric {
        namespace ublas {
            template <class T = double> struct Function {
                const std::size_t size;
                const boost::function<T(const boost::numeric::ublas::vector<T> &)> function;
                const boost::function<boost::numeric::ublas::vector<T>(const boost::numeric::ublas::vector<T> &)> gradient;
                const boost::function<boost::numeric::ublas::matrix<T>(const boost::numeric::ublas::vector<T> &)> hessian;

                Function(std::size_t size,
                    boost::function<T(const boost::numeric::ublas::vector<T> &)> f,
                    boost::function<boost::numeric::ublas::vector<T>(const boost::numeric::ublas::vector<T> &)> grad)
                    : size(size)
                    , function(f)
                    , gradient(grad) {
                }

                Function(std::size_t size,
                    boost::function<T(const boost::numeric::ublas::vector<T> &)> f,
                    boost::function<boost::numeric::ublas::vector<T>(const boost::numeric::ublas::vector<T> &)> grad,
                    boost::function<boost::numeric::ublas::matrix<T>(const boost::numeric::ublas::vector<T> &)> hess)
                    : size(size)
                    , function(f)
                    , gradient(grad)
                    , hessian(hess) {
                }

                Function & operator = (const Function & other) {
                    if (this != &other) {
                        size = other.size;
                        function = other.function;
                        gradient = other.gradient;
                        hessian = other.hessian;
                    }

                    return *this;
                }

                ~Function() = default;

                T operator()(const boost::numeric::ublas::vector<T> & x) const {
                    return function(x);
                }
            };
        } /* namespace ublas */
    } /* namespace numeric */
} /* namespace boost */

#endif