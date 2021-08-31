#ifndef __FT_REVERSE_ITERATOR_HPP
# define __FT_REVERSE_ITERATOR_HPP

# include "ft_iterator.hpp"

namespace ft
{

    template<class Iterator>
    class reverse_iterator
    {
    public:
        typedef
            Iterator
            iterator_type;
        typedef
            typename ft::iterator_traits<Iterator>::iterator_category
            iterator_category;
        typedef
            typename ft::iterator_traits<Iterator>::value_type
            value_type;
        typedef
            typename ft::iterator_traits<Iterator>::difference_type
            difference_type;
        typedef
            typename ft::iterator_traits<Iterator>::pointer
            pointer;
        typedef
            typename ft::iterator_traits<Iterator>::reference
            reference;

        /* Constructors and destructor */
        reverse_iterator( void )
            : _iter()
        {}

        reverse_iterator( iterator_type x)
            : _iter(x)
        {}

        template<class U>
        reverse_iterator( const reverse_iterator<U>& other)
            : _iter(other.base())
        {}

        ~reverse_iterator( void )
        {}

        /* Assignment overload */
        template<class U>
        reverse_iterator&   operator=( const reverse_iterator<U>& other)
        {
            this->_iter = other.iter;
        }

        /* Base */
        iterator_type   base() const    { return this->_iter; }

        /* Data access */
        reference       operator*(void)         { return *(this->_iter); }
        const reference operator*(void) const   { return *(this->_iter); }
        
        pointer         operator->(void)        { return &(*this->_iter); }
        const pointer   operator->(void) const  { return &(*this->_iter); }
        
        reference       operator[](const difference_type& m)
        { return this->_iter[-m - 1]; }
        const reference operator[](const difference_type& m) const
        { return this->_iter[-m - 1]; }

        /* Arifmetics operators */
        reverse_iterator& operator++(void)
        {
            --this->_iter;
            return (*this);
        }

        reverse_iterator& operator--(void)
        {
            ++this->_iter;
            return (*this);
        }
        
        reverse_iterator operator++(int)
        {
            reverse_iterator  tmp(*this);
            --this->_iter;
            return (tmp);
        }
        
        reverse_iterator operator--(int)
        {
            reverse_iterator  tmp(*this);
            ++this->_iter;
            return (tmp);
        }

        reverse_iterator& operator+=(const difference_type& m)
        {
            this->_iter -= m;
            return (*this);
        }

        reverse_iterator& operator-=(const difference_type& m)
        {
            this->_iter += m;
            return (*this);
        }

        reverse_iterator operator+(const difference_type& m) const
        {
            return (this->_iter - m);
        }

        reverse_iterator operator-(const difference_type& m) const
        {
            return (this->_iter + m);
        }

    private:
        iterator_type    _iter;

    };

    /* compares overloads
        
        each compare has two overloads for <T> and <T, U>
        for compare <T, const T>.
    */
    // ==
    template<typename T>
    bool    operator==(const reverse_iterator<T>& first,
                        const reverse_iterator<T>& second)
    {
        return (first.base() == second.base());
    }

    template<typename T, typename U>
    bool    operator==(const reverse_iterator<T>& first,
                        const reverse_iterator<U>& second)
    {
        return (first.base() == second.base());
    }

    // !=
    template<typename T>
    bool    operator!=(const reverse_iterator<T>& first,
                        const reverse_iterator<T>& second)
    {
        return (first.base() != second.base());
    }

    template<typename T, typename U>
    bool    operator!=(const reverse_iterator<T>& first,
                        const reverse_iterator<U>& second)
    {
        return (first.base() != second.base());
    }

    // >=
    template<typename T>
    bool    operator>=(const reverse_iterator<T>& first,
                        const reverse_iterator<T>& second)
    {
        return (first.base() <= second.base());
    }

    template<typename T, typename U>
    bool    operator>=(const reverse_iterator<T>& first,
                        const reverse_iterator<U>& second)
    {
        return (first.base() <= second.base());
    }

    // <=
    template<typename T>
    bool    operator<=(const reverse_iterator<T>& first,
                        const reverse_iterator<T>& second)
    {
        return (first.base() >= second.base());
    }

    template<typename T, typename U>
    bool    operator<=(const reverse_iterator<T>& first,
                        const reverse_iterator<U>& second)
    {
        return (first.base() >= second.base());
    }

    // >
    template<typename T>
    bool    operator>(const reverse_iterator<T>& first,
                        const reverse_iterator<T>& second)
    {
        return (first.base() < second.base());
    }

    template<typename T, typename U>
    bool    operator>(const reverse_iterator<T>& first,
                        const reverse_iterator<U>& second)
    {
        return (first.base() < second.base());
    }

    // <
    template<typename T>
    bool    operator<(const reverse_iterator<T>& first,
                        const reverse_iterator<T>& second)
    {
        return (first.base() > second.base());
    }

    template<typename T, typename U>
    bool    operator<(const reverse_iterator<T>& first,
                        const reverse_iterator<U>& second)
    {
        return (first.base() > second.base());
    }

    /* non-member afirmetic functions */
    template<typename T>
    reverse_iterator<T> operator+(
        const typename reverse_iterator<T>::difference_type& m,
        const reverse_iterator<T>& iter)
    {
        return (iter.base() - m);
    }
    
    template<typename T>
    typename reverse_iterator<T>::difference_type
    operator-(const reverse_iterator<T>& first,
              const reverse_iterator<T>& second)
    {
        return (second.base() - first.base());
    }

    template<typename T, typename U>
    typename reverse_iterator<T>::difference_type
    operator-(const reverse_iterator<T>& first,
              const reverse_iterator<U>& second)
    {
        return (second.base() - first.base());
    }
}

#endif /* __FT_REVERSE_ITERATOR_HPP */