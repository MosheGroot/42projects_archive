#ifndef __FT_VECTOR_HPP__
# define __FT_VECTOR_HPP__

# include <memory>
# include <stdexcept>

# include "utils/ft_meta.hpp"
# include "utils/ft_utils.hpp"
# include "utils/ft_iterator.hpp"
# include "utils/ft_random_access_iterator.hpp"
# include "utils/ft_reverse_iterator.hpp"

/* ft::vector info:
 *
 *   Capacity managment:
 *       * On every resize (resize, assignment) or copy/iterator constructor
 *           (i.e. multiple elements modifiers)
 *           _capacity sets as (new_size + 1), not (new_size * 2);
 *           In most cases after those modifiers there won't be single modify.
 *
 *       * On every single push, pop or insert
 *           _capacity sets as (new_size * 2) if:
 *               - _size     == _capacity;
 *               - _size * 4 >= _capacity;
 *           In most cases those modifiers will be followed by another
 *           signle modify,
 *           so it's more optimized.
*/
/*! @brief  ft::vector template class.
          Provides C++98 standart vector's methods.

    @tparam T           type to store
    @tparam Allocator   custom memory allocator (std::alocator as default)
*/
namespace   ft {

    template<
        class T,
        class Allocator = std::allocator<T>
    > class vector
    {
    public:
        typedef T   value_type;

// defaults:
        typedef Allocator                                   allocator_type;     //  std::alocator<T>
        typedef typename allocator_type::size_type          size_type;          //  ( size_t )
        typedef typename allocator_type::difference_type    difference_type;    //  ( size_t )
        typedef typename allocator_type::reference          reference;          //  ( T& )
        typedef typename allocator_type::const_reference    const_reference;    //  ( const T& )
        typedef typename allocator_type::pointer            pointer;            //  ( T* )
        typedef typename allocator_type::const_pointer      const_pointer;      //  ( const T* )

        typedef typename ft::random_access_iterator<value_type>         iterator;
        typedef typename ft::random_access_iterator<const value_type>   const_iterator;

        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    private:
        Allocator   _alloc;
        size_type   _size;
        size_type   _capacity;
        pointer     _array;

        /*****************/
        /* Private utils */
        /*****************/
        /*! @brief  Force resize underlying array to new_cap size
                    without any checks. Data keeps valid.

            @param new_cap  new capacity of array
        */
        void    __array_resize( size_type new_cap )
        {
            pointer new_data = this->_alloc.allocate(new_cap);
            for (size_type i = 0; i < this->_size; ++i)
                this->_alloc.construct(new_data + i, this->_array[i]);

            this->~vector();
            this->_capacity = new_cap;
            this->_array = new_data;
        }

        /*! @brief Force move elements of array starting from `pos'
                   for `shift' positions to the right side.
                   Doesn't check _capacity.

            @param pos      index where to start movement
            @param shift    distance to move elements
                            (and also the number of shifted elements)
        */
        void     __array_move_right( size_type pos, size_type shift )
        {
            for (size_type i = this->_size - 1; i > pos; --i)
            {
                this->_alloc.construct(this->_array + (i + shift), this->_array[i]);
                this->_alloc.destroy(this->_array + (i + shift));
            }
            this->_alloc.construct(this->_array + (pos + shift), this->_array[pos]);
            this->_alloc.destroy(this->_array + pos);
        }

        /*! @brief  Force move elements of array starting from `pos'
                    for `shift' positions to the left side.
                    Doesn't check _capacity.

            @param pos      index where to start movement
            @param shift    distance to move elements
                            (and also the number of shifted elements)
        */
        void     __array_move_left( size_type pos, size_type shift )
        {
            for (size_type i = pos; i < this->_size; ++i)
            {
                this->_alloc.construct(this->_array + (i - shift), this->_array[i]);
                this->_alloc.destroy(this->_array + i);
            }
        }

        /*! @brief  Checks capacity and decides to resizing
                    in various cases.
        */
        void     __check_capacity(void)
        {
            if (!this->_size && this->_capacity > 1)
                this->__array_resize(1);
            else if (this->_size * 2 < this->_capacity
                    && this->_size * 4 >= this->_capacity)
                this->__array_resize(this->_size * 2);
            else if (this->_size == this->_capacity)
                this->__array_resize(this->_capacity * 2);
        }

    public:
        /****************/
        /* Constructors */
        /****************/

        /*! @brief  Default constructor.
                    Creates an empty vector.
        */
        vector( void )
            : _alloc(), _size(0), _capacity(1), _array(_alloc.allocate(_capacity))
        {}

        /*! @brief  Default constructor with custom allocator.
                    Creates an empty vector.
        */
        explicit vector( const Allocator& alloc )
            : _alloc(alloc), _size(0), _capacity(1), _array(_alloc.allocate(_capacity))
        {}

        /*! @brief  Size based constructor.
                    Creates vector with capacity (n + 1) and
                    construct elements as copies of 'value'
                    (or by default if no value is specified)

            @param n        size of array
            @param value    value to assign
            @param alloc    custom allocator to use
        */
        explicit vector( size_type n,
                         const value_type& value = T(),
                         const Allocator& alloc = Allocator())
            : _alloc(alloc), _size(n),
            _capacity(n + 1), _array(_alloc.allocate(_capacity))
        {
            for (size_type i = 0; i < this->_size; ++i)
                _alloc.construct(_array + i, value);
        }

        /*! @brief  Range based constructor.
                    Creates vector from [begin, end) iterators range
                    (i.e. copies elements from range to new vector).

            @param begin    iterator to the beginning of range
            @param end      iterator to the end of range
            @param alloc    custom allocator to use

            Info:
                Last empty argument is a SFINAE protection.
        */
        template< class InputIt>
        vector( InputIt begin, InputIt end, const Allocator& alloc = Allocator(),
            typename ft::enable_if<!ft::is_integral<InputIt>::value, char>::type* = NULL
        )
            : _alloc(alloc), _size(ft::distance(begin, end)),
            _capacity(_size + 1), _array(_alloc.allocate(_capacity))
        {
            for (size_type i = 0; i < this->_size; ++i)
            {
                this->_alloc.construct(this->_array + i, *begin);
                ++begin;
            }
        }

        /*! @brief Copy constructor. Creates vector as copy of 'other'.

            @param other    vector to copy
        */
        vector( const vector& other)
            : _alloc(other._alloc), _size(other._size),
            _capacity(other._capacity), _array(_alloc.allocate(_capacity))
        {
            for (size_type i = 0; i < this->_size; ++i)
                this->_alloc.construct(this->_array + i, other._array[i]);
        }

        /****************/
        /*  Destructor  */
        /****************/
        /*! @brief Destructor. Destroys vector's content.
        */
        ~vector( void )
        {
            for (size_type i = 0; i < this->_size; i++)
                this->_alloc.destroy(this->_array + i);
            this->_alloc.deallocate(this->_array, this->_capacity);
        }


        /*****************/
        /*  Assignments  */
        /*****************/
        /*! @brief  Assignment operator overload.
                    Assign 'other' vector to this vector.

            @param  other   vector to assign

            @return Reference to this vector.
        */
        vector&     operator=(const vector& other)
        {
            if (&other == this)
                return (*this);

            this->~vector();

            this->_alloc = other._alloc;
            this->_size = other._size;
            this->_capacity = other._capacity;

            this->_array = this->_alloc.allocate(this->_capacity);
            for (size_type i = 0; i < this->_size; ++i)
                this->_alloc.construct(this->_array + i, other._array[i]);
            return (*this);
        }

        /*! @brief  Size based assignment.
                    Assign 'n' number of 'values' to vector with
                    destroying old elements.

            @param n        new number of elements
            @param value    value to assign
        */
        void        assign(size_type n, const value_type& value)
        {
            if (this->_size == n)
            {
                for (size_type i = 0; i < this->_size; i++)
                    this->_alloc.destroy(this->_array + i);
            }
            else
            {
                this->~vector();
                this->_size = n;
                this->_capacity = n + 1;
                this->_array = this->_alloc.allocate(this->_capacity);
            }

            for (size_type i = 0; i < this->_size; ++i)
                this->_alloc.construct(this->_array + i, value);
        }

        /*! @brief  Range based assignment.
                    Assign vector from [begin, end) iterators range
                    (i.e. copies elements from range to new vector).

            @param begin    iterator to the beginning of range
            @param end      iterator to the end of range

            Info:
                Return value is a SFINAE protection.
        */
        template<class InputIt>
        typename ft::enable_if<
            !ft::is_integral<InputIt>::value,
            void
        >::type assign(InputIt begin, InputIt end)
        {
            this->~vector();
            this->_size = ft::distance(begin, end);
            this->_capacity = this->_size + 1;

            this->_array = this->_alloc.allocate(this->_capacity);
            for (size_type i = 0; i < this->_size; ++i, ++begin)
                this->_alloc.construct(this->_array + i, *begin);
        }


        /*******************/
        /*  get_allocator  */
        /*******************/
        /*! @brief Returns the associated allocator.

            @return Allocator type.
        */
        Allocator   get_allocator() const { return this->_alloc; }


        /********************/
        /*  Element access  */
        /********************/
        /*! @brief  Get access to element of the vector by index.
                    Throwing exception if index is out of range.

            @return Reference to associated element.
        */
        reference       at(size_type pos)
        {
            if (pos >= this->_size)
                throw std::out_of_range("invalid pos");
            return (this->_array[pos]);
        }

        /*! @brief  Get access to element of the vector by index.
                    Throwing exception if index is out of range.

            @return Const reference to associated element.
        */
        const_reference at(size_type pos) const
        {
            if (pos >= this->_size)
                throw std::out_of_range("invalid pos");
            return (this->_array[pos]);
        }

        /*! @brief  Get access to element of the vector by index.
                    Doesn't check 'out of range' error.

            @return Reference to associated element.
        */
        reference           operator[](size_type pos)
        { return this->_array[pos]; }

        /*! @brief  Get access to element of the vector by index.
                    Doesn't check 'out of range' error.

            @return Const reference to associated element.
        */
        const_reference     operator[](size_type pos) const
        { return this->_array[pos]; }

        /*! @brief  Get access to first element of the vector.
                    Undefined behaviour if container is empty.

            @return Reference to associated element.
        */
        reference           front()
        { return (this->_array[0]); }

        /*! @brief  Get access to first element of the vector.
                    Undefined behaviour if container is empty.

            @return Const reference to associated element.
        */
        const_reference     front() const
        { return (this->_array[0]); }

        /*! @brief  Get access to last element of the vector.
                    Undefined behaviour if container is empty.

            @return Reference to associated element.
        */
        reference           back()
        { return (this->_array[this->_size - 1]); }

        /*! @brief  Get access to last element of the vector.
                    Undefined behaviour if container is empty.

            @return Const reference to associated element.
        */
        const_reference     back() const
        { return (this->_array[this->_size - 1]); }

        /*! @brief  Get direct access to the underlying array.

            @return Pointer to underlying array.
        */
        pointer         data()
        { return this->_array; }

        /*! @brief  Get direct access to the underlying array.

            @return Const pointer to underlying array.
        */
        const_pointer   data() const
        { return this->_array; }


        /***************/
        /*  Iterators  */
        /***************/
        /*! @brief  Get iterator to the beginning of the vector.
                    If vector is empty then return is the same as end() iterator.

            @return iterator
        */
        iterator begin()
        { return (this->_array); }

        /*! @brief  Get const_iterator to the beginning of the vector.
                    If vector is empty then return is the same as end() const_iterator.

            @return const_iterator
        */
        const_iterator begin() const
        { return (this->_array); }

        /*! @brief  Get iterator to the end of the vector.

            @return iterator
        */
        iterator end()
        {
            if (this->empty())
                return (this->_array);
            return (this->_array + this->_size);
        }

        /*! @brief  Get const_iterator to the end of the vector.

            @return const_iterator
        */
        const_iterator end() const
        {
            if (this->empty())
                return (this->_array);
            return (this->_array + this->_size);
        }

        // reverse_iterator and const_reverse_iterator
        /*! @brief  Get reverse_iterator to the reverse beginning
                    of the vector.
                    If vector is empty then return is the same
                    as rend() reverse_iterator.

            @return reverse_iterator
        */
        reverse_iterator rbegin()
        {
            if (this->empty())
                return (this->end());
            return (this->end() - 1);
        }

        /*! @brief  Get const_reverse_iterator to the reverse beginning
                    of the vector.
                    If vector is empty then return is the same
                    as rend() const_reverse_iterator.

            @return const_reverse_iterator
        */
        const_reverse_iterator rbegin() const
        {
            if (this->empty())
                return (this->end());
            return (this->end() - 1);
        }

        /*! @brief  Get reverse_iterator to the reverse end of the vector.

            @return reverse_iterator
        */
        reverse_iterator rend()
        {
            if (this->empty())
                return (this->begin());
            return (this->begin() - 1);
        }

        /*! @brief  Get const_reverse_iterator to the reverse end of the vector.

            @return const_reverse_iterator
        */
        const_reverse_iterator rend() const
        {
            if (this->empty())
                return (this->begin());
            return (this->end() - 1);
        }

        /**************/
        /*  Capacity  */
        /**************/
        /*! @brief Checks if vector is empty.
            @return bool
        */
        bool        empty() const { return (this->_size == 0); }

        /*! @brief Get current size of the vector.
            @return Size of the vector.
        */
        size_type   size() const { return (this->_size); }

        /*! @brief Get capacity of the vector.
            @return Capacity of the vector.
        */
        size_type   capacity() const { return this->_capacity; }

        /*! @brief Get max size that can contain the vector.
            @return Max size of the vector.
        */
        size_type   max_size() const { return this->_alloc.max_size(); }

        /*! @brief  Reserves memory for vector.
                    Throws exception if 'new_cap' > max_size().
                    All iterators and references are become invalidated.

            @param new_cap  new capacity of vector.
        */
        void    reserve(size_type new_cap)
        {
            if (new_cap > this->_alloc.max_size())
                throw std::length_error("new_cap > max_size()");

            if (new_cap <= this->_capacity)
                return;

            this->__array_resize(new_cap);
        }

        /***************/
        /*  Modifiers  */
        /***************/
        /*! @brief Clear the vector.
        */
        void    clear()
        {
            for (size_type i = 0; i < this->_size; ++i)
                this->_alloc.destroy(this->_array + i);
            this->_size = 0;
        }

        /*! @brief  Insert value to specified 'pos' position
                    with shifting all other elements.

            @param pos      position where to insert element
            @param value    value to insert

            @return Iterator to inserted element.
        */
        iterator    insert(iterator pos, const T& value)
        {
            return insert(pos, 1, value);
        }

        /*! @brief  Insert 'count' number of values to specified 'pos' position
                    with shifting all other elements.

            @param pos      position where to insert element
            @param count    number of elements to insert
            @param value    value to insert

            @return Iterator to first inserted element.
        */
        iterator    insert(iterator pos, size_type count, const T& value)
        {
            if (count == 0)
                return pos;

            size_type   dist = ft::distance(this->begin(), pos);
            if (this->_size + count >= this->_capacity)
                this->__array_resize(this->_size + count + 1);

            if (this->_size)
                __array_move_right(dist, count);
            for (size_type i = dist; i < dist + count; ++i)
                this->_array[i] = value;

            this->_size += count;
            return (this->_array + dist);
        }

        /*! @brief  Insert [begin; end) range of elements
                    to specified 'pos' position with shifting
                    all other elements.

            @param pos      position where to insert element
            @param begin    iterator to the beginning of range
            @param end      iterator to the end of range

            @return Iterator to first inserted element.
        */
        template  <class InputIt>
        typename ft::enable_if<
            !ft::is_integral<InputIt>::value,
            iterator
        >::type insert(iterator pos, InputIt begin, InputIt end)
        {
            size_type   count = ft::distance(begin, end);
            if (count == 0)
                return pos;

            size_type   dist = ft::distance(this->begin(), pos);
            if (this->_size + count > this->_capacity)
                this->__array_resize(this->_size + count + 1);

            if (this->_size)
            {
                for (size_type i = this->_size - 1; i > dist; --i)
                    this->_alloc.construct(this->_array + (i + count),
                                            this->_array[i]);
                this->_alloc.construct(this->_array + dist + count,
                                            this->_array[dist]);
            }
            for (size_type i = dist; i < dist + count; ++i, ++begin)
                this->_array[i] = *begin;

            this->_size += count;
            return (this->_array + dist);
        }

        /*! @brief  Erase element by iterator
                    with shifting all other elements.
            @param pos  position to element to erase
            @return iterator to next after erased element.
        */
        iterator    erase(iterator pos)
        {
            return erase(pos, pos + 1);
        }

        /*! @brief  Erase [first, last) range of elements
                    with shifting all other elements.

            @param first    iterator to the beginning of range
            @param last      iterator to the end of range

            @return iterator to next after last erased element
                    or if (first == last) then returns end() iterator.
        */
        iterator    erase(iterator first, iterator last)
        {
            size_type   count = ft::distance(first, last);
            size_type   dist = ft::distance(this->begin(), first);

            if (!count)
                return (this->end());

            for (size_type i = dist + count - 1; i > dist ; --i)
                this->_alloc.destroy(this->_array + i);
            this->_alloc.destroy(this->_array + dist);

            if (this->_size - count)
                this->__array_move_left(dist + count, count);
            this->_size -= count;
            this->__check_capacity();
            return (this->begin() + dist);
        }

        /*! @brief  Push element to the back of vector.
                    New element becomes the 'last' element.

            @param value    value to push
        */
        void    push_back(const value_type& value)
        {
            this->__check_capacity();
            this->_alloc.construct(this->_array + this->_size, value);
            this->_size += 1;
        }

        /*! @brief  Pop element from the back of vector.
                    Undefined behaviour if vector is empty.
        */
        void    pop_back()
        {
            this->_alloc.destroy(this->_array + this->_size - 1);
            if (this->_size)
                this->_size -= 1;
            this->__check_capacity();
        }

        /*! @brief  Resize the vector. If ('count' > size()) then expands vector
                    with new 'value' (or default) elements. Otherwise narrows the vector to new size.

            @param count    new size of vector
            @param value    value which using for expanding the vector
                            (or default value)
        */
        void    resize(size_type count, T value = T())
        {
            if (this->_size < count)
            {
                if (count > this->_capacity)
                    this->__array_resize(count + 1);
                for (size_type i = this->_size; i < count; ++i)
                    this->_alloc.construct(this->_array + i, value);
                this->_size = count;
            }
            else if (this->_size > count)
            {
                for (size_type i = this->_size - 1; i > count; --i)
                    this->_alloc.destroy(this->_array + i);
                this->_alloc.destroy(this->_array + count);
                this->_size = count;
                if (this->_size * 4 >= this->_capacity)
                    this->__array_resize(this->_size + 1);
            }
        }

        /*! @brief  Swap contects with 'other' vector.
                    Undefined behaviour if allocators are not the same.
                    All iterators and references remain valid.

            @param other    vector to swap
        */
        void    swap(vector& other)
        {
            //get_allocator() != other.get_allocator() -- UB
            pointer     tmp_array = other._array;
            size_type   tmp_cap = other._capacity;
            size_type   tmp_size = other._size;

            other._array = this->_array;
            other._capacity = this->_capacity;
            other._size = this->_size;

            this->_array = tmp_array;
            this->_capacity = tmp_cap;
            this->_size = tmp_size;
        }

    };

    /**************************/
    /*  Non-member functions  */
    /**************************/
    /*  compare operators */
    /*! @brief Equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return True if contents of vectors are the same.
    */
    template< class T, class Alloc >
    bool    operator==( const ft::vector<T, Alloc>& lhs,
                      const ft::vector<T, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    /*! @brief Non-equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(lhs == rhs)
    */
    template< class T, class Alloc >
    bool    operator!=( const ft::vector<T, Alloc>& lhs,
                      const ft::vector<T, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    /*! @brief Less compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return Result of lexicographically compares.
    */
    template< class T, class Alloc >
    bool    operator<( const ft::vector<T, Alloc>& lhs,
                       const ft::vector<T, Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                            rhs.begin(), rhs.end());
    }

    /*! @brief Greater compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return (rhs < lhs).
    */
    template< class T, class Alloc >
    bool    operator>( const ft::vector<T, Alloc>& lhs,
                       const ft::vector<T, Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    /*! @brief Less or equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(rhs < lhs).
    */
    template< class T, class Alloc >
    bool    operator<=( const ft::vector<T, Alloc>& lhs,
                        const ft::vector<T, Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    /*! @brief Greater or equal compares.

        @param lhs  first vector to compare
        @param rhs  second vector to compare

        @return !(lhs < rhs).
    */
    template< class T, class Alloc >
    bool    operator>=( const ft::vector<T, Alloc>& lhs,
                        const ft::vector<T, Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    /*! @brief Swap contects between two vectors.

        @param lhs first vector
        @param rhs second vector
    */
    template< class T, class Alloc >
    void swap( ft::vector<T, Alloc>& lhs,
               ft::vector<T, Alloc>& rhs )
    {
        lhs.swap(rhs);
    }

}

#endif /* __FT_VECTOR_HPP__ */
