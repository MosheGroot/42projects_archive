#ifndef __FT_PAIR__
# define __FT_PAIR__

namespace ft
{

    template<class T1, class T2>
    struct pair
    {
        /* fields */
        typedef T1  first_type;
        typedef T2  second_type;

        T1  first;
        T2  second;

        /* Constructors and destructor */
        pair( void )
            : first(), second()
        {}

        pair(const T1& x, const T2& y)
            : first(x), second(y)
        {}

        template<class U1, class U2>
        pair(const pair<U1, U2>& p)
            : first(p.first), second(p.second)
        {}

        ~pair( void )
        {}

        /* assignment operator */
        pair&   operator=(const pair& p)
        {
            if (this == &p)
                return (*this);
            this->first = p.first;
            this->second = p.second;
            return (*this);
        }
    };

    /* non-member functions */
    // make_pair
    template<class T1, class T2>
    ft::pair<T1, T2>    make_pair( T1 t, T2 u)
    {
        ft::pair<T1, T2>    out(t, u);
        return (out);
    }

    // compare operators
    template<class T1, class T2>
    bool    operator==(const ft::pair<T1, T2>& lhs,
                       const ft::pair<T1, T2>& rhs)
    {
        return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
    }

    template<class T1, class T2>
    bool    operator!=(const ft::pair<T1, T2>& lhs,
                       const ft::pair<T1, T2>& rhs)
    {
        return (!(lhs == rhs));
    }

    template<class T1, class T2>
    bool    operator<(const ft::pair<T1, T2>& lhs,
                      const ft::pair<T1, T2>& rhs)
    {
        if (lhs.first == rhs.first)
            return (lhs.second < rhs.second);
        return (lhs.first < rhs.first);
    }

    template<class T1, class T2>
    bool    operator>=(const ft::pair<T1, T2>& lhs,
                       const ft::pair<T1, T2>& rhs)
    {
        return (!(lhs < rhs));
    }

    template<class T1, class T2>
    bool    operator>(const ft::pair<T1, T2>& lhs,
                      const ft::pair<T1, T2>& rhs)
    {
        if (lhs.first == rhs.first)
            return (lhs.second > rhs.second);
        return (lhs.first > rhs.first);
    }

    template<class T1, class T2>
    bool    operator<=(const ft::pair<T1, T2>& lhs,
                       const ft::pair<T1, T2>& rhs)
    {
        return (!(lhs > rhs));
    }
}

#endif /* __FT_PAIR__ */
