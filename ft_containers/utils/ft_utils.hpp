#ifndef __FT_UTILS_HPP__
# define __FT_UTILS_HPP__

# include "ft_meta.hpp"
# include "ft_iterator.hpp"

namespace ft
{

    /*
        ft::distance    function

        Signature:
            distance (InputIt begin, InputIt end)

        Behaviour:
            Takes two `Input Iterators' and returns numbers of hops
            from `begin' to `end'.
            If `end' is not reachable from `begin' -- UB

        Works with linear complexity.
    */
    template< class InputIt >
    typename iterator_traits<InputIt>::difference_type
        distance (InputIt begin, InputIt end)
        {
            typename ft::iterator_traits<InputIt>::difference_type  out = 0;

            while (begin++ != end)
                ++out;
            return (out);
        }


    /*
        ft comparisons objects

        T1 and T2 must implicitly convert among themselves
    */
    // template
    template<class T1, class T2 = T1>
    struct _compares
    {
        typedef bool    result_type;
        typedef T1      first_argument_type;
        typedef T2      second_argument_type;
    };

    // ==
    template<class T1, class T2 = T1>
    struct equal_to : _compares<T1, T2>
    {
        equal_to() {}
        ~equal_to() {}

        bool operator()( const T1& lhs, const T2& rhs ) const
        {
            return (lhs == rhs);
        }
    };

    // !=
    template<class T1, class T2 = T1>
    struct not_equal_to : _compares<T1, T2>
    {
        not_equal_to() {}
        ~not_equal_to() {}

        bool operator()( const T1& lhs, const T2& rhs ) const
        {
            return (lhs != rhs);
        }
    };

    // >
    template<class T1, class T2 = T1>
    struct greater : _compares<T1, T2>
    {
        greater() {}
        ~greater() {}

        bool operator()( const T1& lhs, const T2& rhs ) const
        {
            return (lhs > rhs);
        }
    };

    // <
    template<class T1, class T2 = T1>
    struct less : _compares<T1, T2>
    {
        less() {}
        ~less() {}

        bool operator()( const T1& lhs, const T2& rhs ) const
        {
            return (lhs < rhs);
        }
    };

    // >=
    template<class T1, class T2 = T1>
    struct greater_equal : _compares<T1, T2>
    {
        greater_equal() {}
        ~greater_equal() {}

        bool operator()( const T1& lhs, const T2& rhs ) const
        {
            return (lhs >= rhs);
        }
    };

    // <=
    template<class T1, class T2 = T1>
    struct less_equal : _compares<T1, T2>
    {
        less_equal() {}
        ~less_equal() {}

        bool operator()( const T1& lhs, const T2& rhs ) const
        {
            return (lhs <= rhs);
        }
    };


    /*
        ft::equal

        Signatures:
        bool    equal ( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2);

        bool    equal ( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, BinaryPredicate p );

        Behaviour:
            Compare ranges `[first1, last1)` and
            `[first2, first2 + (last1 - first1)]`.
            If they are equals, return `true` and `false` otherwise.

            Can use binaryPredicate with next signature:
                `bool pred(const Type1 &a, const Type2 &b);`
            It must return true if the elements should be treated as equal.
    */

    template<class InputIt1, class InputIt2>
    typename ft::enable_if<
        !ft::is_integral<InputIt1>::value &&
        !ft::is_integral<InputIt2>::value,
        bool
    >::type     equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        return equal(first1, last1, first2,
                    equal_to<typename InputIt1::value_type,
                            typename InputIt2::value_type
                            >()
                    );
    }

    template<class InputIt1, class InputIt2, class BinaryPredicate>
    typename ft::enable_if<
        !ft::is_integral<InputIt1>::value &&
        !ft::is_integral<InputIt2>::value &&
        !ft::is_integral<BinaryPredicate>::value,
        bool
    >::type     equal(InputIt1 first1, InputIt1 last1,
                      InputIt2 first2,BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            if (!pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }


    /* ft::lexicographical_compare

        Signatures:
            template< class InputIt1, class InputIt2 >
            bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                        InputIt2 first2, InputIt2 last2 );

            template< class InputIt1, class InputIt2, class Compare >
            bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                          InputIt2 first2, InputIt2 last2,
                                          Compare comp );
    */
    template<class InputIt1, class InputIt2>
    typename ft::enable_if<
        !ft::is_integral<InputIt1>::value &&
        !ft::is_integral<InputIt2>::value,
        bool
    >::type lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2)
    {
        return lexicographical_compare(first1, last1, first2, last2,
                                        ft::less<
                                            typename InputIt1::value_type,
                                            typename InputIt2::value_type
                                        >()
                                    );
    }

    template<class InputIt1, class InputIt2, class Compare>
    typename ft::enable_if<
        !ft::is_integral<InputIt1>::value &&
        !ft::is_integral<InputIt2>::value &&
        !ft::is_integral<Compare>::value,
        bool
    >::type lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    Compare cmp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (cmp(*first1, *first2))
                return true;
            if (cmp(*first2, *first1))
                return false;
            ++first1;
            ++first2;
        }
        return ((first1 == last1) && (first2 != last2));
    }
}

#endif /* __FT_UTILS_HPP__ */
