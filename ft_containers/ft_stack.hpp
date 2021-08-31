#ifndef __FT_STACK_HPP__
# define __FT_STACK_HPP__

# include <memory>
# include <stdexcept>

# include "ft_vector.hpp"

/*! @brief  ft::stack template class.
            Provides C++98 standart stacks's methods.
            Based on ft::vector by default

    @tparam T           type to store
    @tparam Allocator   custom memory allocator (std::alocator as default)
*/
namespace   ft {

    template<
        class T,
        class Container = ft::vector<T>
    > class stack
    {
    public:
        typedef Container                           container_type;
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;

    protected:
        Container c;

        /*****************/
        /* Private utils */
        /*****************/

    public:
        /****************/
        /* Constructors */
        /****************/

        /*! @brief  Default constructor. Creates an empty stack.
                    Allow to specify underlaying container as parametr.

            @param  cont    container to use (or default)
        */
        explicit stack( const Container& cont = Container() )
            : c(cont)
        {}

        /*! @brief Copy constructor. Creates stack as copy of 'other'.

            @param other    stack to copy
        */
        stack( const stack& other)
            : c(other.c)
        {}

        /****************/
        /*  Destructor  */
        /****************/
        /*! @brief Destructor. Destroys stack's content.
        */
        ~stack( void )
        {}


        /*****************/
        /*  Assignments  */
        /*****************/
        /*! @brief  Assignment operator overload.
                    Assign 'other' stack to this stack.

            @param  other   stack to assign

            @return Reference to this stack.
        */
        stack&     operator=(const stack& other)
        {
            this->c = other.c;
            return (*this);
        }


        /********************/
        /*  Element access  */
        /********************/
        /*! @brief  Get access to the top element of the stack.
                    Undefined behaviour if container is empty.

            @return Reference to associated element.
        */
        reference           top()
        { return (this->c.back()); }

        /*! @brief  Get access to the top element of the stack.
                    Undefined behaviour if container is empty.

            @return Const reference to associated element.
        */
        const_reference           top() const
        { return (this->c.back()); }


        /**************/
        /*  Capacity  */
        /**************/
        /*! @brief Checks if stack is empty.
            @return bool
        */
        bool        empty() const { return this->c.empty(); }

        /*! @brief Get current size of the stack.
            @return Size of the stack.
        */
        size_type   size() const { return this->c.size(); }


        /***************/
        /*  Modifiers  */
        /***************/
        /*! @brief  Push element to the top of the stack.
                    New element becomes the 'top' element.

            @param value    value to push
        */
        void    push(const value_type& value)
        {
            this->c.push_back(value);
        }

        /*! @brief  Pop element from the top of stack.
                    Undefined behaviour if stack is empty.
        */
        void    pop()
        {
            this->c.pop_back();
        }


        /*  friend compare operators */
        template< class U >
        friend bool operator==( const ft::stack<U>& lhs,
                                const ft::stack<U>& rhs);
        template< class U >
        friend bool operator!=( const ft::stack<U>& lhs,
                                const ft::stack<U>& rhs);
        template< class U >
        friend bool operator>( const ft::stack<U>& lhs,
                                const ft::stack<U>& rhs);
        template< class U >
        friend bool operator<( const ft::stack<U>& lhs,
                                const ft::stack<U>& rhs);
        template< class U >
        friend bool operator>=( const ft::stack<U>& lhs,
                                const ft::stack<U>& rhs);
        template< class U >
        friend bool operator<=( const ft::stack<U>& lhs,
                                const ft::stack<U>& rhs);

        template< class U, class Y >
        friend bool operator==( const ft::stack<U, Y>& lhs,
                                const ft::stack<U, Y>& rhs);
        template< class U, class Y >
        friend bool operator!=( const ft::stack<U, Y>& lhs,
                                const ft::stack<U, Y>& rhs);
        template< class U, class Y >
        friend bool operator>( const ft::stack<U, Y>& lhs,
                                const ft::stack<U, Y>& rhs);
        template< class U, class Y >
        friend bool operator<( const ft::stack<U, Y>& lhs,
                                const ft::stack<U, Y>& rhs);
        template< class U, class Y >
        friend bool operator>=( const ft::stack<U, Y>& lhs,
                                const ft::stack<U, Y>& rhs);
        template< class U, class Y >
        friend bool operator<=( const ft::stack<U, Y>& lhs,
                                const ft::stack<U, Y>& rhs);

    };

    /**************************/
    /*  Non-member functions  */
    /**************************/
    /*  compare operators with default container */
    /*! @brief Equal compares.

        @param lhs  first stack to compare
        @param rhs  second stack to compare

        @return True if contents of stacks are the same.
    */
    template< class T >
    bool    operator==( const ft::stack<T>& lhs,
                      const ft::stack<T>& rhs)
    {
        return (lhs.c == rhs.c);
    }

    /*! @brief Non-equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(lhs == rhs)
    */
    template< class T >
    bool    operator!=( const ft::stack<T>& lhs,
                      const ft::stack<T>& rhs)
    {
        return (lhs.c != rhs.c);
    }

    /*! @brief Less compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return Result of lexicographically compares.
    */
    template< class T >
    bool    operator<( const ft::stack<T>& lhs,
                       const ft::stack<T>& rhs)
    {
        return (lhs.c < rhs.c);
    }

    /*! @brief Greater compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return (rhs < lhs).
    */
    template< class T >
    bool    operator>( const ft::stack<T>& lhs,
                       const ft::stack<T>& rhs)
    {
        return (lhs.c > rhs.c);
    }

    /*! @brief Less or equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(rhs < lhs).
    */
    template< class T >
    bool    operator<=( const ft::stack<T>& lhs,
                        const ft::stack<T>& rhs)
    {
        return (lhs.c <= rhs.c);
    }

    /*! @brief Greater or equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(lhs < rhs).
    */
    template< class T >
    bool    operator>=( const ft::stack<T>& lhs,
                        const ft::stack<T>& rhs)
    {
        return (lhs.c >= rhs.c);
    }


    /*  compare operators with custom container */
    /*! @brief Equal compares.

        @param lhs  first stack to compare
        @param rhs  second stack to compare

        @return True if contents of stacks are the same.
    */
    template< class T, class U >
    bool    operator==( const ft::stack<T, U>& lhs,
                      const ft::stack<T, U>& rhs)
    {
        return (lhs.c == rhs.c);
    }

    /*! @brief Non-equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(lhs == rhs)
    */
    template< class T, class U >
    bool    operator!=( const ft::stack<T, U>& lhs,
                      const ft::stack<T, U>& rhs)
    {
        return (lhs.c != rhs.c);
    }

    /*! @brief Less compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return Result of lexicographically compares.
    */
    template< class T, class U >
    bool    operator<( const ft::stack<T, U>& lhs,
                       const ft::stack<T, U>& rhs)
    {
        return (lhs.c < rhs.c);
    }

    /*! @brief Greater compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return (rhs < lhs).
    */
    template< class T, class U >
    bool    operator>( const ft::stack<T, U>& lhs,
                       const ft::stack<T, U>& rhs)
    {
        return (lhs.c > rhs.c);
    }

    /*! @brief Less or equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(rhs < lhs).
    */
    template< class T, class U >
    bool    operator<=( const ft::stack<T, U>& lhs,
                        const ft::stack<T, U>& rhs)
    {
        return (lhs.c <= rhs.c);
    }

    /*! @brief Greater or equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(lhs < rhs).
    */
    template< class T, class U >
    bool    operator>=( const ft::stack<T, U>& lhs,
                        const ft::stack<T, U>& rhs)
    {
        return (lhs.c >= rhs.c);
    }
}

#endif /* __FT_STACK_HPP__ */
