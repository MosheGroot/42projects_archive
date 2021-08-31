#ifndef __FT_SET_HPP__
# define __FT_SET_HPP__

#include <memory>
#include "data_structs/ft_pair.hpp"
#include "data_structs/ft_rb_tree.hpp"

namespace ft
{
    /*************************************/
    /*                                   */
    /*             FT::STACK             */
    /*                                   */
    /*************************************/
    /*! @brief Implementation of set based on RB_tree

        @tparam Key         key type to store
        @tparam T           value type to store
        @tparam Compare     function or callable compare object
        @tparam Allocator   memory allocator
    */
    template<
        class Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
    > class set
    {
    public:
        /**************************/
        /*    general typedefs    */
        /**************************/
        typedef Key     key_type;
        typedef Key     value_type;

        typedef Compare key_compare;
        typedef Compare value_compare;

        typedef Allocator   allocator_type;
        typedef typename allocator_type::size_type          size_type;          //  ( size_t )
        typedef typename allocator_type::difference_type    difference_type;    //  ( ptrdiff_t )
        typedef typename allocator_type::reference          reference;          //  ( value_type& )
        typedef typename allocator_type::const_reference    const_reference;    //  ( const value_type& )
        typedef typename allocator_type::pointer            pointer;            //  ( value_type* )
        typedef typename allocator_type::const_pointer      const_pointer;      //  ( const value_type* )

        typedef
            typename ft::_RB_tree<value_type, value_compare, allocator_type>::const_iterator
            iterator;
        typedef
            typename ft::_RB_tree<value_type, value_compare, allocator_type>::const_iterator
            const_iterator;

        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    private:
        typedef
            typename ft::_RB_tree<value_type, value_compare, allocator_type>::_node_type
            _node_type;

        /************************/
        /*    general fields    */
        /************************/

        //< tree container
        ft::_RB_tree<value_type, value_compare, allocator_type>     _tree;

    public:
        /*************************************/
        /*    Constructors and destructor    */
        /*************************************/
        /*! @brief Default costructor. Creates an empty set

            @param comp compare to assign
            @param alloc allocator to assign
        */
        explicit    set(const Compare& comp = key_compare(),
                        const Allocator& alloc = Allocator())
            : _tree(comp, alloc)
        {}

        /*! @brief Iterator constructor. Creates set with added pairs
                   from iterators range [first, last).

            @param first    begin of range
            @param last     end of range
            @param comp     compare to assign
            @param alloc    allocator to assign
        */
        template< class InputIt >
        set( InputIt first, InputIt last,
             const Compare& comp = Compare(),
             const Allocator& alloc = Allocator(),
             typename ft::enable_if<!ft::is_integral<InputIt>::value, char>::type* = NULL)
            : _tree(comp, alloc)
        {
            while (first != last)
            {
                this->_tree.push(*first);
                ++first;
            }
        }

        /*! @brief Copy constructor. Creates new set and
                   deeply copies pairs from other set.

            @param other    another set to copy
        */
        set( const set& other )
            : _tree(other._tree)
        {}

        /*! @brief Destructor. Deletes all allocated memory.
        */
        ~set( void ) {}

        /********************/
        /*    Assignment    */
        /********************/
        /*! @brief Assignment overload.
                   Deeply copies other set to this set.
        */
        set&    operator=( const set& other )
        {
            if (this == &other)
                return (*this);
            this->_tree = other._tree;
            return (*this);
        }

        /***********************/
        /*    get_allocator    */
        /***********************/
        /*! @brief Get_allocator overload.

            @return The associated allocator
        */
        allocator_type get_allocator() const
        {
            return (Allocator());
        }

        /*******************/
        /*    Iterators    */
        /*******************/
        /*! @brief Return iterator to the beginning of tree
            @return set::iterator
        */
        iterator        begin() { return this->_tree.begin(); }

        /*! @brief Return const_iterator to the beginning of tree
            @return set::const_iterator
        */
        const_iterator  begin() const { return this->_tree.begin(); }

        /*! @brief Return iterator to the end of tree.
            @return set::iterator
        */
        iterator        end() { return this->_tree.end(); }

        /*! @brief Return const_iterator to the end of tree.
            @return set::const_iterator
        */
        const_iterator  end() const { return this->_tree.end(); }

        /***********************/
        /*  Reverse_iterators  */
        /***********************/
        /*! @brief Return reverse_iterator to the begining of tree.
            (i.e. pre-end simple iterator)

            @return set::reverse_iterator
        */
        reverse_iterator        rbegin() { return this->_tree.rbegin(); }

        /*! @brief Return const_reverse_iterator to the begining of tree.
            (i.e. pre-end simple iterator)

            @return set::const_reverse_iterator
        */
        const_reverse_iterator  rbegin() const { return this->_tree.rbegin(); }
        /*! @brief Return reverse_iterator to the end of tree.
            (i.e. .end() simple iterator)

            @return set::reverse_iterator
        */
        reverse_iterator        rend() { return (this->_tree.rend()); }

        /*! @brief Return const_reverse_iterator to the end of tree.
            (i.e. .end() simple iterator)

            @return set::const_reverse_iterator
        */
        const_reverse_iterator  rend() const { return (this->_tree.rend()); }

        /******************/
        /*    Capacity    */
        /******************/
        /*! @brief Check if set is empty.
            @return boolean result of check
        */
        bool        empty() const { return (this->_tree.size() == 0); }

        /*! @brief Return current size of set.
            @return size_type
        */
        size_type   size() const { return this->_tree.size(); }

        /*! @brief Return maximum number of elements is able to hold.
            @return size_type
        */
        size_type   max_size() const { return this->_tree.get_allocator().max_size(); }

        /*******************/
        /*    Modifiers    */
        /*******************/
        /*! @brief Clear the set: deletes all pairs.
        */
        void    clear() { this->_tree.clear(); }

        /*! @brief Insert new pair to set
                   if element already contain an element
                   with an equivalent key
            @param value    pair to insert
            @return Pair of iterator to inserted element
            and bool denoting whether the insertion took place.
        */
        ft::pair<iterator, bool>   insert(const value_type& value)
        {
            _node_type  *searched = this->_tree.search(value);
            if (searched)
                return (ft::make_pair(searched, false));
            return (ft::make_pair(this->_tree.push(value), true));
        }

        /*! @brief Insert new pair to set if container doesn't
                   already contain an element with an equivalent key.
                   Using hint iterator as a suggestion as
                   to where to start the search.

            @param hint     hint iterator
            @param value    pair to insert

            @return Iterator to inserted element.
        */
        iterator    insert(const_iterator hint, const value_type& value)
        {
            _node_type  *searched = this->_tree.search(hint, value);
            if (searched)
                return (searched);
            return (this->_tree.push(hint, value));
        }

        /*! @brief Insert new pairs by iterators range [first; last).

            @param first    iterator to beginning of range
            @param second   iterator to end of range
        */
        template< class InputIt >
        typename ft::enable_if<
            !ft::is_integral<InputIt>::value,
            void
        >::type insert(InputIt first, InputIt last)
        {
            while (first != last)
            {
                this->_tree.push(*first);
                ++first;
            }
        }

        /*! @brief Erase pair from set by iterator.

            @param pos  iterator to pair to erase
        */
        void    erase(iterator pos)
        {
            this->_tree.erase(pos);
        }

        /*! @brief Erase pairs range [first; last)
                   from set by iterators.

            @param first    iterator to beginning of range
            @param second   iterator to end of range
        */
        void    erase(iterator first, iterator last)
        {
            if (first == this->begin() && last == this->end())
                clear();
            else
                while (first != last)
                    this->_tree.erase(first++);
        }

        /*! @brief Erase pair from the set by key
                   if pair with equals key exists.

            @param key  key of pair to delete

            @return 0 if set doesn't contains pair with the same key
            or 1 if pair has been erased.
        */
        size_type    erase(const key_type& key)
        {
            return this->_tree.erase(value_type(key));
        }

        /*! @brief Swap the contects between this and other set.
            @param other    set to swap
        */
        void    swap(set& other)
        {
            this->_tree.swap(other._tree);
        }

        /****************/
        /*    Lookup    */
        /****************/
        /*! @brief Count number of elements with equivalent key

            @param key key to search
        */
        size_type   count(const key_type& key) const
        {
            if (this->_tree.search(value_type(key)))
                return (1);
            return (0);
        }

        /*! @brief Find pair with equivalent key
                   and return iterator to it.

            @param key key to search
            @return Iterator to element or .end iterator if container doesn't
                    contain that key.
        */
        iterator    find(const Key& key)
        {
            return this->_tree.search(value_type(key));
        }

        /*! @brief Find pair with equivalent key
                   and return iterator to it.

            @param key key to search
            @return Const_iterator to element or .end iterator if container doesn't
                    contain that key.
        */
        const_iterator  find(const Key& key) const
        {
            return this->_tree.search(value_type(key));
        }

        /*! @brief Lower bound.
                   Returns an iterator pointing to the first element
                   that is not less than (i.e. greater or equal to) key

            @return Iterator to lower_bound element or .end()
        */
        iterator    lower_bound(const key_type& key)
        {
            return this->_tree.lower_bound(value_type(key));
        }

        /*! @brief Lower bound.
                   Returns an iterator pointing to the first element
                   that is not less than (i.e. greater or equal to) key

            @return Const_iterator to lower_bound element or .end()
        */
        const_iterator    lower_bound(const key_type& key) const
        {
            return this->_tree.lower_bound(value_type(key));
        }

        /*! @brief Upper bound.
                   Returns an iterator pointing to the first element
                   that is greater than key

            @return Iterator to upper_bound element or .end()
        */
        iterator    upper_bound(const key_type& key)
        {
            return this->_tree.upper_bound(value_type(key));
        }

        /*! @brief Upper bound.
                   Returns an iterator pointing to the first element
                   that is greater than key

            @return Const_iterator to upper_bound element or .end()
        */
        const_iterator    upper_bound(const key_type& key) const
        {
            return this->_tree.upper_bound(value_type(key));
        }

        /*! @brief Equal range function.
                   Returns a range of iterators, that contains all elements
                   with the given key in the container.

            @return Pair of iterators of [first; second)
        */
        ft::pair<iterator,iterator> equal_range(const Key& key)
        {
            return (ft::make_pair(this->_tree.lower_bound(value_type(key)),
                                  this->_tree.upper_bound(value_type(key))));
        }

        /*******************/
        /*    Observers    */
        /*******************/
        /*! @brief Return copy of function object that compares the keys.

            @return compare object
        */
        key_compare     key_comp() const
        { return key_compare(); }

        /*! @brief Return copy of function object that compares the pairs.

            @return compare object
        */
        value_compare   value_comp() const
        { return value_compare(key_compare()); }
    };

    /**************************/
    /*  Non-member functions  */
    /**************************/
    /*  compare operators */
    template<class Key>
    bool    operator==( const ft::set<Key>& lhs,
                        const ft::set<Key>& rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<class Key>
    bool    operator!=( const ft::set<Key>& lhs,
                        const ft::set<Key>& rhs)
    {
        return !(lhs == rhs);
    }

    template<class Key>
    bool    operator<( const ft::set<Key>& lhs,
                       const ft::set<Key>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                           rhs.begin(), rhs.end());
    }

    template<class Key>
    bool    operator>( const ft::set<Key>& lhs,
                       const ft::set<Key>& rhs)
    {
        return (rhs < lhs);
    }

    template<class Key>
    bool    operator<=( const ft::set<Key>& lhs,
                        const ft::set<Key>& rhs)
    {
        return !(rhs < lhs);
    }

    template<class Key>
    bool    operator>=( const ft::set<Key>& lhs,
                        const ft::set<Key>& rhs)
    {
        return !(lhs < rhs);
    }

    /*! @brief Swap contects between two sets

        @param lhs first set
        @param rhs second set
    */
    template<class Key>
    void swap( ft::set<Key>& lhs,
               ft::set<Key>& rhs )
    {
        lhs.swap(rhs);
    }
}

#endif /* __FT_SET_HPP__ */
