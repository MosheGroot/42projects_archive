#ifndef __FT_MAP_HPP__
# define __FT_MAP_HPP__

#include <memory>
#include "data_structs/ft_pair.hpp"
#include "data_structs/ft_rb_tree.hpp"

namespace ft
{
    /*************************************/
    /*                                   */
    /*              FT::MAP              */
    /*                                   */
    /*************************************/
    /*! @brief Implementation of map based on RB_tree

        @tparam Key         key type to store
        @tparam T           value type to store
        @tparam Compare     function or callable compare object
        @tparam Allocator   memory allocator
    */
    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T> >
    > class map
    {
    public:
        /**************************/
        /*    general typedefs    */
        /**************************/
        typedef Key     key_type;
        typedef T       mapped_type;

        typedef ft::pair<const key_type, mapped_type>       value_type;
        typedef Compare     key_compare;

        /*! @brief Map's value_compare callable subclass.
        */
        class value_compare
        {
        protected:
            friend class map;

            Compare comp;

            value_compare( const Compare& c ) : comp(c) {}

        public:
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;

            /*! @brief Call the compare function to compare pairs by first argument

                @param lhs,rhs  pairs to compare
                @return boolean result
            */
            result_type operator()(const first_argument_type& lhs,
                                const second_argument_type& rhs) const
            {
                return (this->comp(lhs.first, rhs.first));
            }
        };

        typedef Allocator   allocator_type;
        typedef typename allocator_type::size_type          size_type;          //  ( size_t )
        typedef typename allocator_type::difference_type    difference_type;    //  ( ptrdiff_t )
        typedef typename allocator_type::reference          reference;          //  ( value_type& )
        typedef typename allocator_type::const_reference    const_reference;    //  ( const value_type& )
        typedef typename allocator_type::pointer            pointer;            //  ( value_type* )
        typedef typename allocator_type::const_pointer      const_pointer;      //  ( const value_type* )

        typedef
            typename ft::_RB_tree<value_type, value_compare, allocator_type>::iterator
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
        /*! @brief Default costructor. Creates an empty map

            @param comp compare to assign
            @param alloc allocator to assign
        */
        explicit    map(const Compare& comp = key_compare(),
                        const Allocator& alloc = Allocator())
            : _tree(comp, alloc)
        {}

        /*! @brief Iterator constructor. Creates map with added pairs
                   from iterators range [first, last).

            @param first    begin of range
            @param last     end of range
            @param comp compare to assign
            @param alloc allocator to assign
        */
        template< class InputIt >
        map( InputIt first, InputIt last,
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

        /*! @brief Copy constructor. Creates new map and
                   deeply copies pairs from other map.

            @param other    another map to copy
        */
        map( const map& other )
            : _tree(other._tree)
        {}

        /*! @brief Destructor. Deletes all allocated memory.
        */
        ~map( void ) {}

        /********************/
        /*    Assignment    */
        /********************/
        /*! @brief Assignment overload.
                   Deeply copies other map to this map.
        */
        map&    operator=( const map& other )
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

        /************************/
        /*    Element access    */
        /************************/
        /*! @brief at function.
            Access specified element with bounds checking.

            @param key  key to search

            @return value associated with key
        */
        mapped_type&    at(const key_type& key)
        {
            _node_type* searched = this->_tree.search(ft::make_pair(key, 0));
            if (!searched)
                throw std::out_of_range("range error");
            return (searched->_value.second);
        }

        /*! @brief at function.
            Access specified element with bounds checking.

            @param key  key to search

            @return value associated with key
        */
        const mapped_type&    at(const key_type& key) const
        {
            const _node_type* searched = this->_tree.search(ft::make_pair(key, mapped_type()));
            if (!searched)
                throw std::out_of_range("range error");
            return (searched->_value.second);
        }

        /*! @brief Element access operator.
            If key doesn't mapped, creates new default pair with this key.
            Otherwise, returns reference to old value.

            @param key  key to access

            @return Reference to mapped value
        */
        mapped_type&    operator[](const Key& key)
        {
            value_type  tmp_pair = ft::make_pair(key, mapped_type());

            _node_type*  searched = this->_tree.search(tmp_pair);
            if (!searched)
                return insert(tmp_pair).first->second;
            return searched->_value.second;
        }

        /*******************/
        /*    Iterators    */
        /*******************/
        /*! @brief Return iterator to the beginning of tree
            @return map::iterator
        */
        iterator        begin() { return this->_tree.begin(); }

        /*! @brief Return const_iterator to the beginning of tree
            @return map::const_iterator
        */
        const_iterator  begin() const { return this->_tree.begin(); }

        /*! @brief Return iterator to the end of tree.
            @return map::iterator
        */
        iterator        end() { return this->_tree.end(); }

        /*! @brief Return const_iterator to the end of tree.
            @return map::const_iterator
        */
        const_iterator  end() const { return this->_tree.end(); }

        /***********************/
        /*  Reverse_iterators  */
        /***********************/
        /*! @brief Return reverse_iterator to the begining of tree.
            (i.e. pre-end simple iterator)

            @return map::reverse_iterator
        */
        reverse_iterator        rbegin() { return this->_tree.rbegin(); }

        /*! @brief Return const_reverse_iterator to the begining of tree.
            (i.e. pre-end simple iterator)

            @return map::const_reverse_iterator
        */
        const_reverse_iterator  rbegin() const { return this->_tree.rbegin(); }
        /*! @brief Return reverse_iterator to the end of tree.
            (i.e. .end() simple iterator)

            @return map::reverse_iterator
        */
        reverse_iterator        rend() { return (this->_tree.rend()); }

        /*! @brief Return const_reverse_iterator to the end of tree.
            (i.e. .end() simple iterator)

            @return map::const_reverse_iterator
        */
        const_reverse_iterator  rend() const { return (this->_tree.rend()); }

        /******************/
        /*    Capacity    */
        /******************/
        /*! @brief Check if map is empty.
            @return boolean result of check
        */
        bool        empty() const { return (this->_tree.size() == 0); }

        /*! @brief Return current size of map.
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
        /*! @brief Clear the map: deletes all pairs.
        */
        void    clear() { this->_tree.clear(); }

        /*! @brief Insert new pair to map
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

        /*! @brief Insert new pair to map if container doesn't
                   already contain an element with an equivalent key.
                   Using hint iterator as a suggestion as
                   to where to start the search.

            @param hint     hint iterator
            @param value    pair to insert

            @return Iterator to inserted element.
        */
        iterator    insert(iterator hint, const value_type& value)
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

        /*! @brief Erase pair from map by iterator.

            @param pos  iterator to pair to erase
        */
        void    erase(iterator pos)
        {
            this->_tree.erase(pos);
        }

        /*! @brief Erase pairs range [first; last)
                   from map by iterators.

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

        /*! @brief Erase pair from the map by key
                   if pair with equals key exists.

            @param key  key of pair to delete

            @return 0 if map doesn't contains pair with the same key
            or 1 if pair has been erased.
        */
        size_type    erase(const key_type& key)
        {
            return this->_tree.erase(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Swap the contects between this and other map.
            @param other    map to swap
        */
        void    swap(map& other)
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
            if (this->_tree.search(ft::make_pair(key, mapped_type())))
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
            return this->_tree.search(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Find pair with equivalent key
                   and return iterator to it.

            @param key key to search
            @return Const_iterator to element or .end iterator if container doesn't
                    contain that key.
        */
        const_iterator  find(const Key& key) const
        {
            return this->_tree.search(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Lower bound.
                   Returns an iterator pointing to the first element
                   that is not less than (i.e. greater or equal to) key

            @return Iterator to lower_bound element or .end()
        */
        iterator    lower_bound(const key_type& key)
        {
            return this->_tree.lower_bound(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Lower bound.
                   Returns an iterator pointing to the first element
                   that is not less than (i.e. greater or equal to) key

            @return Const_iterator to lower_bound element or .end()
        */
        const_iterator    lower_bound(const key_type& key) const
        {
            return this->_tree.lower_bound(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Upper bound.
                   Returns an iterator pointing to the first element
                   that is greater than key

            @return Iterator to upper_bound element or .end()
        */
        iterator    upper_bound(const key_type& key)
        {
            return this->_tree.upper_bound(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Upper bound.
                   Returns an iterator pointing to the first element
                   that is greater than key

            @return Const_iterator to upper_bound element or .end()
        */
        const_iterator    upper_bound(const key_type& key) const
        {
            return this->_tree.upper_bound(ft::make_pair(key, mapped_type()));
        }

        /*! @brief Equal range function.
                   Returns a range of iterators, that contains all elements
                   with the given key in the container.

            @return Pair of iterators of [first; second)
        */
        ft::pair<iterator,iterator> equal_range(const Key& key)
        {
            ft::pair<key_type, mapped_type> tmp_pair(key, mapped_type());

            return (ft::make_pair(this->_tree.lower_bound(tmp_pair),
                                  this->_tree.upper_bound(tmp_pair)));
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
    template<class Key, class T>
    bool    operator==( const ft::map<Key, T>& lhs,
                        const ft::map<Key, T>& rhs)
    {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<class Key, class T>
    bool    operator!=( const ft::map<Key, T>& lhs,
                        const ft::map<Key, T>& rhs)
    {
        return !(lhs == rhs);
    }

    template<class Key, class T>
    bool    operator<( const ft::map<Key, T>& lhs,
                       const ft::map<Key, T>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                           rhs.begin(), rhs.end());
    }

    template<class Key, class T>
    bool    operator>( const ft::map<Key, T>& lhs,
                       const ft::map<Key, T>& rhs)
    {
        return (rhs < lhs);
    }

    template<class Key, class T>
    bool    operator<=( const ft::map<Key, T>& lhs,
                        const ft::map<Key, T>& rhs)
    {
        return !(rhs < lhs);
    }

    template<class Key, class T>
    bool    operator>=( const ft::map<Key, T>& lhs,
                        const ft::map<Key, T>& rhs)
    {
        return !(lhs < rhs);
    }

    /*! @brief Swap contects between two maps

        @param lhs first map
        @param rhs second map
    */
    template<class Key, class T>
    void swap( ft::map<Key, T>& lhs,
               ft::map<Key, T>& rhs )
    {
        lhs.swap(rhs);
    }
}

#endif /* __FT_MAP_HPP__ */
