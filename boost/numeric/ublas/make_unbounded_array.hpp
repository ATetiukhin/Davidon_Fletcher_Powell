#ifndef BOOST_UBLAS_MAKE_UNBOUNDED_ARRAY_HPP
#define BOOST_UBLAS_MAKE_UNBOUNDED_ARRAY_HPP

#include <initializer_list>
#include <boost/numeric/ublas/storage.hpp>

namespace boost {
    namespace numeric {
        namespace ublas {
            template <typename T>
            unbounded_array<T> make_unbounded_array(std::initializer_list<T> list) {
                std::size_t size = list.size();
                unbounded_array<T> result(size);

                for (size_t i = 0; i < size; ++i)
                    result[i] = *(list.begin() + i);

                return result;
            }
        } /* namespace ublas */
    } /* namespace numeric */
} /* namespace boost */

#endif