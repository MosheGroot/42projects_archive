#ifndef __FT_RANDOM_ACCESS_ITERATOR_HPP__
# define __FT_RANDOM_ACCESS_ITERATOR_HPP__

# include "ft_iterator.hpp"

namespace ft
{

    template<typename T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
    {    
    public:
        typedef
            typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category
            iterator_category;
        typedef
            typename ft::iterator<ft::random_access_iterator_tag, T>::value_type
            value_type;
        typedef
            typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type
            difference_type;
        typedef
            typename ft::iterator<ft::random_access_iterator_tag, T>::pointer
            pointer;
        typedef
            typename ft::iterator<ft::random_access_iterator_tag, T>::reference
            reference;

        /* Constructors and destructor */
        random_access_iterator( pointer ptr = NULL)
            : _ptr(ptr)
        {}

        random_access_iterator( const random_access_iterator& iter)
            : _ptr(iter._ptr)
        {}

        ~random_access_iterator( void )
        {}


        /* Data access */
        pointer         base() const
        { return this->_ptr; }
        
        reference       operator*(void) const
        { return *(this->_ptr); }
        
        pointer         operator->(void) const
        { return this->_ptr; }
        
        reference       operator[](const difference_type& m) const
        { return this->_ptr[m]; }


        /* Arifmetics operators */
        random_access_iterator& operator++(void)
        {
            this->_ptr += 1;
            return (*this);
        }

        random_access_iterator& operator--(void)
        {
            this->_ptr -= 1;
            return (*this);
        }

        random_access_iterator operator++(int)
        {
            random_access_iterator  tmp(*this);
            this->_ptr += 1;
            return (tmp);
        }

        random_access_iterator operator--(int)
        {
            random_access_iterator  tmp(*this);
            this->_ptr -= 1;
            return (tmp);
        }

        random_access_iterator& operator+=(const difference_type& m)
        {
            this->_ptr += m;
            return (*this);
        }

        random_access_iterator& operator-=(const difference_type& m)
        {
            this->_ptr -= m;
            return (*this);
        }
    
        random_access_iterator operator+(const difference_type& m) const
        {
            return (this->_ptr + m);
        }

        random_access_iterator operator-(const difference_type& m) const
        {
            return (this->_ptr - m);
        }

        /* enable convertion from iterator to const_iterator */
        operator random_access_iterator<const T> () const
        { return (random_access_iterator<const T>(this->_ptr)); }

    private:
        pointer _ptr;
    };

    /* compares overloads
        
        each compare has two overloads for <T> and <T, U>
        for compare <T, const T>.
    */
    // ==
    template<typename T>
    bool    operator==(const random_access_iterator<T>& first,
                        const random_access_iterator<T>& second)
    {
        return (first.base() == second.base());
    }

    template<typename T, typename U>
    bool    operator==(const random_access_iterator<T>& first,
                        const random_access_iterator<U>& second)
    {
        return (first.base() == second.base());
    }

    // !=
    template<typename T>
    bool    operator!=(const random_access_iterator<T>& first,
                        const random_access_iterator<T>& second)
    {
        return (first.base() != second.base());
    }

    template<typename T, typename U>
    bool    operator!=(const random_access_iterator<T>& first,
                        const random_access_iterator<U>& second)
    {
        return (first.base() != second.base());
    }

    // >=
    template<typename T>
    bool    operator>=(const random_access_iterator<T>& first,
                        const random_access_iterator<T>& second)
    {
        return (first.base() >= second.base());
    }

    template<typename T, typename U>
    bool    operator>=(const random_access_iterator<T>& first,
                        const random_access_iterator<U>& second)
    {
        return (first.base() >= second.base());
    }

    // <=
    template<typename T>
    bool    operator<=(const random_access_iterator<T>& first,
                        const random_access_iterator<T>& second)
    {
        return (first.base() <= second.base());
    }

    template<typename T, typename U>
    bool    operator<=(const random_access_iterator<T>& first,
                        const random_access_iterator<U>& second)
    {
        return (first.base() <= second.base());
    }

    // >
    template<typename T>
    bool    operator>(const random_access_iterator<T>& first,
                        const random_access_iterator<T>& second)
    {
        return (first.base() > second.base());
    }

    template<typename T, typename U>
    bool    operator>(const random_access_iterator<T>& first,
                        const random_access_iterator<U>& second)
    {
        return (first.base() > second.base());
    }

    // <
    template<typename T>
    bool    operator<(const random_access_iterator<T>& first,
                        const random_access_iterator<T>& second)
    {
        return (first.base() < second.base());
    }

    template<typename T, typename U>
    bool    operator<(const random_access_iterator<T>& first,
                        const random_access_iterator<U>& second)
    {
        return (first.base() < second.base());
    }

    /* non-member afirmetic functions */
    template<typename T>
    random_access_iterator<T> operator+(
        const typename random_access_iterator<T>::difference_type& m,
        const random_access_iterator<T>& iter)
    {
        return (iter.base() + m);
    }
    
    template<typename T>
    typename random_access_iterator<T>::difference_type
    operator-(const random_access_iterator<T>& first,
              const random_access_iterator<T>& second)
    {
        return (first.base() - second.base());
    }

    template<typename T, typename U>
    typename random_access_iterator<T>::difference_type
    operator-(const random_access_iterator<T>& first,
              const random_access_iterator<U>& second)
    {
        return (first.base() - second.base());
    }
}

#endif /* __FT_RANDOM_ACCESS_ITERATOR_HPP__ */
