#ifndef __FT_RB_TREE_HPP__
# define __FT_RB_TREE_HPP__

#include "../utils/ft_utils.hpp"
#include "../utils/ft_reverse_iterator.hpp"
#include <memory>
#include <iostream>
#include <string.h>

# define _FT_RB_TREE_DEBUG 0

namespace   ft
{
    // forward declaration
    template<
        class U,
        class Compare,
        class Allocator
    > class _RB_tree;

    /*****************************************/
    /*                                       */
    /*           FT::_RB_TREE_NODE           */
    /*                                       */
    /*****************************************/
    /*! @brief enum for _RB_node colors
    */
    enum _RB_node_color
    {
        _RB_color_black = false,
        _RB_color_red
    };

    /*! @brief enum for _RB_node branch inside tree
    */
    enum _RB_node_branch
    {
        _RB_branch_left = false,
        _RB_branch_right,
        _RB_branch_undef
    };

    /*! @brief Template implemention of Red-Black tree's node
        Contains _value, _color, _parent and _left,_right children.

        @tparam U    type to store
    */
    template<class U>
    struct _RB_node
    {
        typedef U       value_type; //< type of stored value

        value_type      _value;     //< stored value
        _RB_node_color  _color;     //< color of node
        _RB_node<U>*    _parent;    //< parent of node
        _RB_node<U>*    _left;      //< left child
        _RB_node<U>*    _right;     //< right child

        /******************************/
        /* Constructor and destructor */
        /******************************/
        /*! @brief Value constructor.
            Creates RED colored node with specified _value and empty _parent/_left/_right.

            @param value    the value to store
        */
        _RB_node( const U& value)
            : _value(value), _color(_RB_color_red),
            _parent(NULL), _left(NULL), _right(NULL)
        {}

        /*! @brief Destructor
        */
        ~_RB_node( void )
        {}

        /********************/
        /*    Non-static    */
        /********************/
        /*! @brief Non_static swap children.
        */
        void    swap_children(void)
        {
            _RB_node<U> *tmp;

            tmp = this->_left;
            this->_left = this->_right;
            this->_right = tmp;
        }

        /*! @brief Non_static swap values with another node.

            @param node     node with which the swap is required
        */
        void    swap_values(_RB_node<U>* node)
        {
            // it looks really strange, but required if
            // agrument is constant or doesn't have overloaded
            // assignment operator
            char    buffer[sizeof(value_type)];
            void*   this_ptr = reinterpret_cast<void *>(&this->_value);
            void*   node_ptr = reinterpret_cast<void *>(&node->_value);

            memcpy(buffer, this_ptr, sizeof(value_type));
            memcpy(this_ptr, node_ptr, sizeof(value_type));
            memcpy(node_ptr, buffer, sizeof(value_type));
        }

        /*! @brief Non_static swap colors with another node.

            @param node     node with which the swap is required
        */
        void    swap_colors(_RB_node<U>* node)
        {
            _RB_node_color   tmp;

            tmp = this->_color;
            this->_color = node->_color;
            node->_color = tmp;
        }

        /********************/
        /*      Static      */
        /********************/
        /*! @brief Static get_color function.
            Return color of node, or 'black' if node if leaf (NULL).

            @return _RB_node_color enum -- red or black
        */
        static _RB_node_color   get_color(const _RB_node<U>* node)
        {
            if (node == NULL || node->_color == _RB_color_black)
                return (_RB_color_black);
            return (_RB_color_red);
        }

        /*! @brief Static get_branch function.
            Return branch of specified node.
            Undefined behaviour if parent is not exist.

            @return _RB_node_branch enum -- left or right
        */
        static _RB_node_branch  get_branch(const _RB_node<U>* node)
        {
            if (node->_parent->_left == node)
                return _RB_branch_left;
            else if (node->_parent->_right == node)
                return _RB_branch_right;
            return _RB_branch_undef;
        }

        /*! @brief Static get_uncle function.
            Return uncle of specified node.
            Undefined behaviour if parent or grandparent are not exist.

            @return _RB_node* -- pointer to uncle's node
        */
        static _RB_node<U>*     get_uncle(_RB_node<U>* node)
        {
            if (get_branch(node->_parent) == _RB_branch_left)
                return (node->_parent->_parent->_right);
            return (node->_parent->_parent->_left);
        }

        /*! @brief Static get_minimal function.
            Finds the leftest descendant of specified node.

            @return _RB_node* to leftest (minimal) descendant.
        */
        static _RB_node<U>*     get_minimal(_RB_node<U>* node)
        {
            if (!node)
                return node;
            while (node->_left)
                node = node->_left;
            return node;
        }

        /*! @brief Static get_maximal function.
            Finds the rightest descendant of specified node.

            @return _RB_node* to rightest (maximal) descendant.
        */
        static _RB_node<U>*     get_maximal(_RB_node<U>* node)
        {
            if (!node)
                return node;
            while (node->_right)
                node = node->_right;
            return node;
        }

    };  /* _RB_node */



    /*****************************************/
    /*                                       */
    /*         FT::_RB_TREE_ITERATOR         */
    /*                                       */
    /*****************************************/
    template<class T>
    struct _RB_tree_const_iterator;

    /*! @brief Template implementation of bidirectional _RB_tree_iterator.
        Allows to iterate the tree.

        @tparam T   node class to iterate
    */
    template<class T>
    struct _RB_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        friend struct _RB_tree_const_iterator<T>;

    public:
        template<
            class U,
            class Compare,
            class Allocator>
        friend class _RB_tree;

        typedef typename T::value_type  value_type;
        typedef value_type*             pointer;
        typedef value_type&             reference;

        typedef
            typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category
            iterator_category;
        typedef
            typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type
            difference_type;

    private:
        T*      _node;  //< pointer to current node in tree

    public:
        /*******************************/
        /* Constructors and destructor */
        /*******************************/
        /*! @brief Default constructor.
        */
        _RB_tree_iterator( void )
            : _node(NULL)
        {}

        /*! @brief Node constructor.

            @param node pointer to node inside tree
        */
        _RB_tree_iterator( T* node )
            : _node(node)
        {}

        /*! @brief Copy constructor

            @param iter another iterator to copy
        */
        _RB_tree_iterator( const _RB_tree_iterator& iter)
            : _node(iter._node)
        {}

        /*! @brief Destructor
        */
        ~_RB_tree_iterator( void )
        {}

        /*! @brief Assignment operator

            @param iter another iterator to assign
        */
        _RB_tree_iterator&  operator=(const _RB_tree_iterator& iter)
        {
            if (this == &iter)
                return (*this);
            this->_node = iter._node;
            return (*this);
        }

        /****************/
        /*    Access    */
        /****************/
        /*! @brief Operator* overload

            @return reference to stored value
        */
        reference       operator*(void) const
        { return (this->_node->_value); }

        /*! @brief Operator-> overload

            @return pointer to stored value
        */
        pointer         operator->(void) const
        { return (&this->_node->_value); }

        /***********************/
        /*    In/decrements    */
        /***********************/
        /*! @brief Increment operator overload.
            Moves iterator to next value in the tree.
            If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            @return Reference to this iterator
        */
        _RB_tree_iterator& operator++(void)
        {
            if (this->_node->_right)       // if has right branch
                this->_node = T::get_minimal(this->_node->_right);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_right)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        /*! @brief Decrement operator overload.
            Moves iterator to previous value in the tree.

            1) If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            2) If current iterator value is .begin()
            then iterator switches to .end().

            @return Reference to this iterator
        */
        _RB_tree_iterator& operator--(void)
        {
            if (this->_node->_parent && this->_node->_color == _RB_color_red &&
                    this->_node == this->_node->_parent->_parent)
                this->_node = this->_node->_right;
            else if (this->_node->_left)                // if has left branch
                this->_node = T::get_maximal(this->_node->_left);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_left)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        /*! @brief  post-increment
            Moves iterator to next value in the tree.
            If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            @return iterator before incrementation
        */
        _RB_tree_iterator   operator++(int)
        {
            _RB_tree_iterator<T>   out(*this);
            this->operator++();
            return (out);
        }

        /*! @brief Decrement operator overload.
            Moves iterator to previous value in the tree.

            1) If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            2) If current iterator value is .begin()
            then iterator switches to .end().

            @return iterator before incrementation
        */
        _RB_tree_iterator   operator--(int)
        {
            _RB_tree_iterator<T>   out(*this);
            this->operator--();
            return (out);
        }


        /******************/
        /*    Compares    */
        /******************/
        friend bool     operator==(const _RB_tree_iterator& it1,
                                   const _RB_tree_iterator& it2)
        { return (it1._node == it2._node); }

        friend bool     operator!=(const _RB_tree_iterator& it1,
                                   const _RB_tree_iterator& it2)
        { return (it1._node != it2._node); }

    };  /* _RB_tree_iterator */



    /*****************************************/
    /*                                       */
    /*      FT::_RB_TREE_CONST_ITERATOR      */
    /*                                       */
    /*****************************************/
    /*! @brief Template implementation of bidirectional _RB_tree_const_iterator.
        Allows to iterate the tree.

        @tparam T   node class to iterate
    */
    template<class T>
    struct _RB_tree_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        template<
            class U,
            class Compare,
            class Allocator>
        friend class _RB_tree;

        typedef typename T::value_type  value_type;
        typedef const value_type*       pointer;
        typedef const value_type&       reference;

        typedef
            typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category
            iterator_category;
        typedef
            typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type
            difference_type;


    private:
        T*      _node;  //< pointer to current node in tree

    public:
        /*******************************/
        /* Constructors and destructor */
        /*******************************/
        /*! @brief Default constructor.
        */
        _RB_tree_const_iterator( void )
            : _node(NULL)
        {}

        /*! @brief Node constructor.

            @param node pointer to node inside tree
        */
        _RB_tree_const_iterator( T* node )
            : _node(node)
        {}

        /*! @brief Copy constructor from const_iterator

            @param iter another const_iterator to copy
        */
        _RB_tree_const_iterator( const _RB_tree_const_iterator& iter)
            : _node(iter._node)
        {}

        /*! @brief Copy constructor from iterator

            @param iter another iterator to copy
        */
       _RB_tree_const_iterator( const _RB_tree_iterator<T>& iter)
            : _node(iter._node)
        {}

        /*! @brief Destructor
        */
        ~_RB_tree_const_iterator( void )
        {}

        /*! @brief Assignment operator

            @param iter another iterator to assign
        */
        _RB_tree_const_iterator&  operator=(const _RB_tree_const_iterator& iter)
        {
            if (this == &iter)
                return (*this);
            this->_node = iter._node;
            return (*this);
        }


        /****************/
        /*    Access    */
        /****************/
        /*! @brief Operator* overload

            @return reference to stored value
        */
        reference       operator*(void) const
        { return (this->_node->_value); }

        /*! @brief Operator-> overload

            @return pointer to stored value
        */
        pointer         operator->(void) const
        { return (&this->_node->_value); }

        /***********************/
        /*    In/decrements    */
        /***********************/
        /*! @brief Increment operator overload.
            Moves iterator to next value in the tree.
            If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            @return Reference to this iterator
        */
        _RB_tree_const_iterator& operator++(void)
        {
            if (this->_node->_right)       // if has right branch
                this->_node = T::get_minimal(this->_node->_right);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_right)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        /*! @brief Decrement operator overload.
            Moves iterator to previous value in the tree.

            1) If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            2) If current iterator value is .begin()
            then iterator switches to .end().

            @return Reference to this iterator
        */
        _RB_tree_const_iterator& operator--(void)
        {
            if (this->_node->_parent && this->_node->_color == _RB_color_red &&
                    this->_node == this->_node->_parent->_parent)
                this->_node = this->_node->_right;
            else if (this->_node->_left)                // if has left branch
                this->_node = T::get_maximal(this->_node->_left);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_left)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        /*! @brief  post-increment
            Moves iterator to next value in the tree.
            If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            @return iterator before incrementation
        */
        _RB_tree_const_iterator   operator++(int)
        {
            _RB_tree_const_iterator<T>   out(*this);
            this->operator++();
            return (out);
        }

        /*! @brief Decrement operator overload.
            Moves iterator to previous value in the tree.

            1) If current iterator value is .end()
            then iterator switches to the rightest element of tree.

            2) If current iterator value is .begin()
            then iterator switches to .end().

            @return iterator before incrementation
        */
        _RB_tree_const_iterator   operator--(int)
        {
            _RB_tree_const_iterator<T>   out(*this);
            this->operator--();
            return (out);
        }


        /******************/
        /*    Compares    */
        /******************/
        friend bool     operator==(const _RB_tree_const_iterator& it1,
                                   const _RB_tree_const_iterator& it2)
        { return (it1._node == it2._node); }

        friend bool     operator!=(const _RB_tree_const_iterator& it1,
                                   const _RB_tree_const_iterator& it2)
        { return (it1._node != it2._node); }

    };  /* _RB_tree_const_iterator */



    /******************************************/
    /*                                        */
    /*              FT::_RB_TREE              */
    /*                                        */
    /******************************************/
    /*! @brief Template implimentation of Red-Black tree

        @tparam U            type to store
        @tparam Compare      callable object or function for compares
        @tparam Allocator    memory allocator
    */
    template<
        class U,
        class Compare,
        class Allocator = std::allocator<U>
    > class _RB_tree
    {
    public:
        typedef _RB_node<U>     _node_type;
        typedef U               value_type;

        typedef
            typename Allocator::template rebind<_node_type>::other
            _node_allocator;


        typedef typename _node_allocator::size_type          size_type;          //  ( size_t )
        typedef typename _node_allocator::difference_type    difference_type;    //  ( ptrdiff_t )
        typedef typename _node_allocator::reference          reference;          //  ( T& )
        typedef typename _node_allocator::const_reference    const_reference;    //  ( const T& )
        typedef typename _node_allocator::pointer            pointer;            //  ( T* )
        typedef typename _node_allocator::const_pointer      const_pointer;      //  ( const T* )

        typedef typename ft::_RB_tree_iterator<_node_type>          iterator;
        typedef typename ft::_RB_tree_const_iterator<_node_type>    const_iterator;

        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    private:
        _node_allocator _node_alloc;    //< allocator of _RB_nodes
        Compare         _cmp;           //< compare function
        size_type       _size;          //< current tree size

        _node_type*     __header;       //< header of tree: (`_parent` == root), (`_left` == minimal), (`_right` == maximal).
        // genious idea. Stolen from the original:
        //  __header->_color   == RED ( => not root)
        //  __header->_parent  == root
        //  __header->_left    == .begin()
        //  __header->_right   == .end() - 1
        //  __header           == .end()

    public:
        /****************/
        /*    PUBLIC    */
        /****************/

        /*******************************/
        /* Constructors and destructor */
        /*******************************/

        /*! @brief Default constructor.
            Creates an empty tree.
        */
        _RB_tree( const Compare& comp = Compare(),
                  const Allocator& alloc = Allocator())
            : _node_alloc(alloc), _cmp(comp), _size(0)
        {
            this->__header = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(this->__header, value_type());
        }

        /*! @brief Copy constructor.
            Deeply copies the tree.

            @param tree tree to be copied
        */
        _RB_tree( const _RB_tree& tree )
            : _node_alloc(tree._node_alloc),
              _cmp(tree._cmp), _size(0)
        {
            this->__header = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(this->__header, value_type());

            this->_dfs_copy(&this->__header->_parent, this->__header, tree.__header->_parent);
            this->__header->_left = _node_type::get_minimal(this->__header->_parent);
            this->__header->_right = _node_type::get_maximal(this->__header->_parent);
        }

        /*! @brief Destructor.
            Delete all allocated memory.
        */
        ~_RB_tree( void )
        {
            this->_dfs_delete(this->__header->_parent);
            this->_node_alloc.destroy(this->__header);
            this->_node_alloc.deallocate(this->__header, 1);
        }

        /*! @brief Assignment operator
            Deeply copies the tree.

            @param tree tree to be assigned
        */
        _RB_tree&   operator=(const _RB_tree& tree)
        {
            if (this == &tree)
                return (*this);
            this->_dfs_delete(this->__header->_parent);
            this->_dfs_copy(&this->__header->_parent, this->__header, tree.__header->_parent);
            this->__header->_left = _node_type::get_minimal(this->__header->_parent);
            this->__header->_right = _node_type::get_maximal(this->__header->_parent);
            return (*this);
        }

        /*! @brief Get_allocator overload.

            @return The associated allocator
        */
        _node_allocator get_allocator() const
        {
            return (this->_node_alloc);
        }

        /*********************/
        /*  General methods  */
        /*********************/

        /*! @brief Push new value to the tree.

            @param value new value to add

            @return Pointer to pushed node.
        */
        _node_type*    push(const U& value)
        {
            // add new root
            if (!this->__header->_parent)
                return this->_add_node(&this->__header->_parent, value, this->__header);

            // search for new node's position
            _node_type* iter = this->__header->_parent;
            _node_type* prev;
            while (iter)
            {
                prev = iter;
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    return iter;
            }

            // add new node
            if (this->_cmp(value, prev->_value))
                return this->_add_node(&prev->_left, value, prev);
            return this->_add_node(&prev->_right, value, prev);
        }

        /*! @brief Push new value to the tree after hint iterator.

            @param hint  iterator as a suggestion as to where to start the search
            @param value new value to add

            @return Pointer to pushed node.
        */
        _node_type*    push(const_iterator hint, const U& value)
        {
            // search for new node's position
            _node_type* iter = hint._node;
            _node_type* prev;

            // if hint is wrong reset iter to root
            if (iter != this->__header->_parent &&
                !this->_cmp(value, iter->_parent->_value))
                iter = this->__header->_parent;

            while (iter)
            {
                prev = iter;
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    return iter;
            }

            // add new node
            if (this->_cmp(value, prev->_value))
                return this->_add_node(&prev->_left, value, prev);
            return this->_add_node(&prev->_right, value, prev);
        }

        /*! @brief Search value in the tree.

            @param value    value to search

            @return _RB_node* -- pointer to first occurance of value or NULL
        */
        _node_type*     search(const U& value)
        {
            _node_type*     iter = this->__header->_parent;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        /*! @brief Search value in the tree.

            @param value    value to search

            @return _RB_node* -- pointer to first occurance of value or NULL
        */
        const _node_type*     search(const U& value) const
        {
            _node_type*     iter = this->__header->_parent;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        /*! @brief Search value in the tree starting from hint node.

            @param hint     iterator as a suggestion as to where to start the search
            @param value    value to search

            @return _RB_node* -- pointer to first occurance of value or NULL
        */
        _node_type*     search(const_iterator hint, const U& value)
        {
            _node_type*     iter = hint._node;

            // if hint is wrong reset iter to root
            if (iter != this->__header->_parent &&
                !this->_cmp(value, iter->_parent->_value))
                iter = this->__header->_parent;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        /*! @brief Search value in the tree.

            @param hint     iterator as a suggestion as to where to start the search
            @param value    value to search

            @return _RB_node* -- pointer to first occurance of value or NULL
        */
        const _node_type*     search(const_iterator hint, const U& value) const
        {
            _node_type*     iter = hint._node;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        /*! @brief Erase value all occurrences of value from the tree

            @param value    value to erase
        */
        size_type       erase(const U& value)
        {
            _node_type*     node_ptr = this->search(value);
            size_type       deleted = 0;

            while (node_ptr)
            {
                this->_erase(node_ptr);
                deleted += 1;
                node_ptr = this->search(value);
            }
            this->_size -= deleted;
            return deleted;
        }

        /*! @brief Erase node from tree by iterator.

            @param pos  iterator to node to delete
        */
        void            erase(iterator pos)
        {
            this->_erase(pos._node);
            this->_size -= 1;
        }

        /*! @brief Erase node from tree by iterator.

            @param pos  iterator to node to delete
        */
        void            erase(const_iterator pos)
        {
            this->_erase(pos._node);
            this->_size -= 1;
        }

        /*! @brief Delete all values from the tree.
        */
        void    clear()
        {
            this->_dfs_delete(this->__header->_parent);
            this->__header->_parent = NULL;
            this->__header->_left = NULL;
            this->__header->_right = NULL;
        }

        /*! @brief Swap trees with their sizes and compares.
        */
        void    swap(_RB_tree& other)
        {
            _node_type  *tmp_node = this->__header;
            this->__header = other.__header;
            other.__header = tmp_node;

            size_type   tmp_size = this->_size;
            this->_size = other._size;
            other._size = tmp_size;

            Compare     tmp_cmp = this->_cmp;
            this->_cmp = other._cmp;
            other._cmp = tmp_cmp;
        }

        /*! @brief Size method.

            @return number of elements in tree
        */
        size_type       size(void) const
        { return this->_size; }

        /*! @brief Lower_bound function

            @param value value to compare

            @return An iterator pointing to first element
                    that is not less than key.
        */
        iterator    lower_bound(const value_type& value)
        {
            _node_type*   tmp;
            tmp = this->_lower_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        /*! @brief Const lower_bound function

            @param value value to compare

            @return A const_iterator pointing to first element
                    that is not less than key.
        */
        const_iterator    lower_bound(const value_type& value) const
        {
            const _node_type*   tmp;
            tmp = this->_lower_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        /*! @brief Upper_bound function

            @param value value to compare

            @return An iterator pointing to first element
                    that is greater than key.
        */
        iterator    upper_bound(const value_type& value)
        {
            _node_type*   tmp;
            tmp = this->_upper_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        /*! @brief Upper_bound function

            @param value value to compare

            @return A const_iterator pointing to first element
                    that is greater than key.
        */
        const_iterator    upper_bound(const value_type& value) const
        {
            const _node_type*   tmp;
            tmp = this->_upper_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        /***************/
        /*  Iterators  */
        /***************/

        /*! @brief Return iterator to the begining of tree.
            @return _RB_tree::iterator
        */
        iterator        begin()
        {
            if (!this->_size)
                return (this->__header);
            return (this->__header->_left);
        }

        /*! @brief Return const_iterator to the begining of tree.
            @return _RB_tree::const_iterator
        */
        const_iterator  begin() const
        {
            if (!this->_size)
                return (this->__header);
            return (this->__header->_left);
        }

        /*! @brief Return iterator to the end of tree.
            @return _RB_tree::iterator
        */
        iterator        end()
        { return (this->__header); }

        /*! @brief Return const_iterator to the end of tree.
            @return _RB_tree::const_iterator
        */
        const_iterator  end() const
        { return (this->__header); }

        /***********************/
        /*  Reverse_iterators  */
        /***********************/
        /*! @brief Return reverse_iterator to the begining of tree.
            (i.e. pre-end simple iterator)

            @return _RB_tree::reverse_iterator
        */
        reverse_iterator rbegin()
        {
            if (!this->_size)
                return (this->end());
            return (--this->end());
        }

        /*! @brief Return const_reverse_iterator to the begining of tree.
            (i.e. pre-end simple iterator)

            @return _RB_tree::const_reverse_iterator
        */
        const_reverse_iterator rbegin() const
        {
            if (!this->_size)
                return (this->end());
            return (--this->end());
        }

        /*! @brief Return reverse_iterator to the end of tree.
            (i.e. .end() simple iterator)

            @return _RB_tree::reverse_iterator
        */
        reverse_iterator rend()
        { return (this->end()); }

        /*! @brief Return const_reverse_iterator to the end of tree.
            (i.e. .end() simple iterator)

            @return _RB_tree::const_reverse_iterator
        */
        const_reverse_iterator rend() const
        { return (this->end()); }


    private:
        /*****************/
        /*    PRIVATE    */
        /*****************/
        /*! @brief Recursively deletes all nodes in dfs order
            @param node root node of the delition area
        */
        void    _dfs_delete(_node_type *node)
        {
            if (!node)
                return;
            _dfs_delete(node->_left);
            _dfs_delete(node->_right);
            this->_node_alloc.destroy(node);
            this->_node_alloc.deallocate(node, 1);
            this->_size -= 1;
        }

        /*! @brief Recursively copies all nodes from another node.
            Undefined behaviour if nodes are in same tree.

            @param **dest   address to store new root node
            @param *prev    parent node of the node (NULL or __header)
            @param *to_copy node from another tree to copy
        */
        void    _dfs_copy(_node_type **dest, _node_type *prev,
                          const _node_type *to_copy)
        {
            if (!to_copy)
            {
                *dest = NULL;
                return;
            }
            *dest = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(*dest, to_copy->_value);
            (*dest)->_parent = prev;
            (*dest)->_color = to_copy->_color;
            this->_size += 1;
            this->_dfs_copy(&(*dest)->_left, *dest, to_copy->_left);
            this->_dfs_copy(&(*dest)->_right, *dest, to_copy->_right);
        }

        /***********************/
        /*      Add value      */
        /***********************/
        /*! @brief Add new value to tree with tree balancing calling.

            @param **dest   address to store new node
            @param value    value of new node
            @param *parent  parent of new node

            @return Pointer to added node
        */
        _node_type *    _add_node(_node_type **dest, const value_type& value,
                                  _node_type *parent)
        {
            *dest = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(*dest, value);
            (*dest)->_parent = parent;
            this->_size += 1;

            _node_type* out_ptr = *dest;
            if (parent != this->__header) // target is not root
            {
                this->_check_balance(*dest);

                // update minimal and maximal nodes
                if (this->__header->_left->_left)
                    this->__header->_left = this->__header->_left->_left;
                if (this->__header->_right->_right)
                    this->__header->_right = this->__header->_right->_right;
            }
            else
            {
                this->__header->_left = (*dest);
                this->__header->_right = (*dest);
            }

            this->__header->_parent->_color = _RB_color_black;

#if _FT_RB_TREE_DEBUG
            // debug print if invalid tree
            size_type   tmp;
            if (_check_tree(this->__header->_parent, tmp) == false)
            {
                // std::cout << "ADD error [ " << value << " ]\n";
                this->_print_tree(this->__header->_parent, 0);
                std::cout << "\n" << std::endl;
            }
#endif
            return out_ptr;
        }

        /*! @brief Checks balance of tree in the 'target' node's area.
            Rebalance the tree if it is violated.

            @param target   last added node to check
        */
        void    _check_balance(_node_type *target)
        {
            // some protections for recursive calls
            if (!target || target == this->__header->_parent || target == this->__header)
                return;

            // if parent is RED too, grandparent's existance is guaranteed
            if (target->_parent->_color != _RB_color_red)   // => no color conflicts
                return;

            if (_node_type::get_color(_node_type::get_uncle(target)) == _RB_color_red)
                _balance_case1(target);
            else
            {
                if (_node_type::get_branch(target) != _node_type::get_branch(target->_parent))
                    _balance_case2(target);
                else
                    _balance_case3(target);
            }
        }

        /*! @brief Balance case 1: uncle is red
        */
        inline void    _balance_case1(_node_type *target)
        {
            // change colors
            target->_parent->_color = _RB_color_black;
            _node_type::get_uncle(target)->_color = _RB_color_black;
            target->_parent->_parent->_color = _RB_color_red;
            this->_check_balance(target->_parent->_parent);
        }

        /*! @brief Balance case 2: uncle is black, parent and grandparent in different branches
        */
        inline void    _balance_case2(_node_type *target)
        {
            if (_node_type::get_branch(target) == _RB_branch_right)
            {
                this->_rotate_left(target);
                _balance_case3(target->_left);
            }
            else
            {
                this->_rotate_right(target);
                _balance_case3(target->_right);
            }
        }

        /*! @brief Balance case 3: uncle is black, parent and grandparent in same branches
        */
        inline void    _balance_case3(_node_type *target)
        {
            // rotate tree
            target->_parent->_color = _RB_color_black;
            target->_parent->_parent->_color = _RB_color_red;
            if (_node_type::get_branch(target) == _RB_branch_right)
                this->_rotate_left(target->_parent);
            else
                this->_rotate_right(target->_parent);
        }

        /* Rotates

            (!) For 'balance after push' calls -- 'Target' is parent of pushed node:

                        Grandparent                  [parent]
                        /          \                 /     \
                    [Parent]      Uncle      =>  (added)   Grandparent
                      /  \         /  \                    /     \
                (Added)  .A.     .B.   .C.               .A.     Uncle
                                                                /   \
                                                                .B.   .C.
                                (rotate right example)
            Behaviour:
                Rotate tree like in AVL-tree.
                Doesn't change colors!
                Doesn't check if parent or grandparent are exist.
        */
        /*! @brief Right rotate of tree.

            @param target           node that becomes the new local root
                                    (usually parent of last added node).
        */
        void     _rotate_right(_node_type *target)
        {
            _node_type* const   grandparent = target->_parent->_parent; // grandparent is fixed

            // right child
            if (target->_right)
                target->_right->_parent = target->_parent;
            target->_parent->_left = target->_right;

            // parent
            target->_parent->_parent = target;
            target->_right = target->_parent;

            // root change
            if (grandparent != this->__header) // parent is not global root
            {
                if (grandparent->_left == target->_parent)
                    grandparent->_left = target;
                else
                    grandparent->_right = target;
            }
            else
                this->__header->_parent = target;

            // target's parent change
            target->_parent = grandparent;
        }

        /*! @brief Left rotate of tree.

            @param target           node that becomes the new local root
                                    (usually parent of last added node).
        */
        void     _rotate_left(_node_type *target)
        {
            _node_type* const   grandparent = target->_parent->_parent; // grandparent is fixed

            // left child
            if (target->_left)
                target->_left->_parent = target->_parent;
            target->_parent->_right = target->_left;

            // parent
            target->_parent->_parent = target;
            target->_left = target->_parent;

            // root change
            if (grandparent != this->__header) // parent is not global root
            {
                if (grandparent->_left == target->_parent)
                    grandparent->_left = target;
                else
                    grandparent->_right = target;
            }
            else
                this->__header->_parent = target;

            // target's parent change
            target->_parent = grandparent;
        }

        /***********************/
        /*     Erase value     */
        /***********************/
        /*
            Erase node

            Erase of some node considers 5 cases
            (node color + number of children -- not 6 because of add rules),
            one of which is considered separetely: deleting black node with 0 children.
            This case entails a change in black height => we need to rebalance tree.

            For illustrations go to:
            https://habr.com/ru/company/otus/blog/521034/
        */
        /*! @brief Erase specified non-null node

            @param target   node to erase
        */
        void    _erase(_node_type *target)
        {
#if _FT_RB_TREE_DEBUG
            // value_type  val = target->_value;
#endif
            // get count of children
            size_type   count_of_children = 0;
            if (target->_right)
                count_of_children += 1;
            if (target->_left)
                count_of_children += 1;

            // choose deletion case
            if (count_of_children == 2)
                this->_erase_case_rb_2(target);
            else if (count_of_children == 1) // black color is guaranteed!
                this->_erase_case_black_1(target);
            else // count_of_children == 0
            {
                if (target->_color == _RB_color_red)
                    this->_erase_case_red_0(target);
                else
                    this->_erase_case_black_0(target);
            }

#if _FT_RB_TREE_DEBUG
            // debug print
            size_type   tmp;
            if (_check_tree(this->__header->_parent, tmp) == false)
            {
                // std::cout << "ERASE error [ " << val << " ]\n";
                this->_print_tree(this->__header->_parent, 0);
                std::cout << "\n" << std::endl;
            }
#endif
        }

        /*! @brief Erase case "X with 2 children".

            Case comes down to "erase X with 0/1 children"
        */
        inline void    _erase_case_rb_2(_node_type *target)
        {
            // find min or max value in children subtrees
            _node_type  *min = target->_right;
            _node_type  *max = target->_left;

            while (min && max)
            {
                min = min->_left;
                if (min)
                    max = max->_right;
            }
            while (min && min->_left)
                min = min->_left;
            while (max && max->_right)
                max = max->_right;

            // choose farest of them
            _node_type  *to_swap = max;
            if (min)
                to_swap = min;
            else
                to_swap = max;

            // swap nodes with keeping colors
            this->_erase_swap_nodes(target, to_swap);

            // erase node with 0 or 1 child
            this->_erase(target);
        }

        /*! @brief Erase case "black with 1 children".

            In this case guaranteed that one child is RED
            (second is NULL node with black color so child
            will be RED for same black-height)

            Case comes down to swap and delete RED child.
        */
        inline void    _erase_case_black_1(_node_type *target)
        {
            // choose children
            _node_type  *to_swap;
            if (target->_left)
                to_swap = target->_left;
            else
                to_swap = target->_right;

            // swap nodes with keeping colors
            this->_erase_swap_nodes(target, to_swap);

            // erase node without children
            this->_erase_case_red_0(target);
        }

        /*! @brief Erase case "red without children".

            Simplest case. We can erase this node without
            changing black-height.
        */
        inline void    _erase_case_red_0(_node_type *target)
        {
            if (_node_type::get_branch(target) == _RB_branch_left)
                target->_parent->_left = NULL;
            else
                target->_parent->_right = NULL;

            if (this->__header->_right == target)
                this->__header->_right = target->_parent;
            else if (this->__header->_left == target)
                this->__header->_left = target->_parent;

            this->_node_alloc.destroy(target);
            this->_node_alloc.deallocate(target, 1);
        }

        /*! @brief Erase case "black without children".

            Hardest case. Simple deletion but this entails
            a change in black-height, so we need to rebalance tree.
        */
        inline void    _erase_case_black_0(_node_type *target)
        {
            _node_type  *parent = target->_parent;

            if (parent == this->__header)  //  if target is root
                parent->_parent = NULL;
            if (parent->_left == target)
                parent->_left = NULL;
            if (parent->_right == target)
                parent->_right = NULL;

            if (this->__header->_right == target)
                this->__header->_right = parent;
            else if (this->__header->_left == target)
                this->__header->_left = parent;

            this->_node_alloc.destroy(target);
            this->_node_alloc.deallocate(target, 1);
            this->_erase_rebalance(NULL, parent);
        }

        /*! @brief  Private swap_nodes function for erase process.
                    Swap nodes' pointers for keeping iterators valid.
                    Colors at positions are staying the same!

            @param parent       First node to swap.
            @param descendent   Second node to swap which must be descendent
                                of first one.
        */
        void    _erase_swap_nodes(_node_type *parent, _node_type *descendent)
        {
            // Change pointer to parent from parent
            if (parent == this->__header->_parent) // parent is root
                this->__header->_parent = descendent;
            else
            {
                if (_node_type::get_branch(parent) == _RB_branch_left)
                    parent->_parent->_left = descendent;
                else
                    parent->_parent->_right = descendent;
            }

            // Change pointer to descendent from parent
            // Important: descendent can't be root!
            if (descendent->_parent != parent)
            {
                if (_node_type::get_branch(descendent) == _RB_branch_left)
                    descendent->_parent->_left = parent;
                else
                    descendent->_parent->_right = parent;
            }

            // check left bound
            if (parent == this->__header->_left)
                this->__header->_left = descendent;
            else if (descendent == this->__header->_left)
                this->__header->_left = parent;

            // check right bound
            if (parent == this->__header->_right)
                this->__header->_right = descendent;
            else if (descendent == this->__header->_right)
                this->__header->_right = parent;

            // Change to parent from children
            if (parent->_left && parent->_left != descendent)
                parent->_left->_parent = descendent;
            if (parent->_right && parent->_right != descendent)
                parent->_right->_parent = descendent;

            // Change to descendent from children
            if (descendent->_left)
                descendent->_left->_parent = parent;
            if (descendent->_right)
                descendent->_right->_parent = parent;

            // swap all fields
            char    buffer[sizeof(_node_type)];
            memcpy(buffer, parent, sizeof(_node_type));
            memcpy(parent, descendent, sizeof(_node_type));
            memcpy(descendent, buffer, sizeof(_node_type));

            // if cycled (descendent was a child of parent)
            if (parent->_parent == parent)
                parent->_parent = descendent;
            if (descendent->_left == descendent)
                descendent->_left = parent;
            else if (descendent->_right == descendent)
                descendent->_right = parent;

            // and swap values
            parent->swap_values(descendent);
        }

        /*! @brief Rebalance the tree after deletion some black node.
            Can be called recursively. So 'child' param is not always NULL.

            @param child    pointer to "deleted" or actually deleted node
            @param parent   pointer to parent of "deleted" node
        */
        void    _erase_rebalance(_node_type *child, _node_type *parent)
        {
            // if root was erased
            if (parent == this->__header || !parent)
                return;

            // choose sibling
            _node_type  *sibling;
            if (parent->_left == child)
                sibling = parent->_right;
            else
                sibling = parent->_left;
            // btw, NULL sibling is imposible case.

            // check sibling's color
            if (sibling->_color == _RB_color_black)
            {
                _node_type  *same_branch_child;     // same branch as brother's
                _node_type  *another_branch_child;

                if (_node_type::get_branch(sibling) == _RB_branch_right)
                {
                    same_branch_child = sibling->_right;
                    another_branch_child = sibling->_left;
                }
                else
                {
                    same_branch_child = sibling->_left;
                    another_branch_child = sibling->_right;
                }

                if (_node_type::get_color(same_branch_child) == _RB_color_red)
                    this->_erase_rebalance_case__black_red_sameb(sibling);
                else if (_node_type::get_color(another_branch_child) == _RB_color_red)
                    this->_erase_rebalance_case__black_red_anotherb(sibling);
                else
                    this->_erase_rebalance_case__black_black(sibling);
            }
            else // sibling->_color == RED
                this->_erase_rebalance_case__red(child, parent, sibling);
        }

        /*! @brief Erase rebalance case "BLACK sibling with RED same-branch child"

            Solution is in recolor sibling, child and parent, and rotate.
            ahother-branch child's color has no fffect this case.

            @param sibling  pointer to sibling of "deleted" node
        */
        inline void     _erase_rebalance_case__black_red_sameb(_node_type *sibling)
        {
            sibling->_color = sibling->_parent->_color;
            sibling->_parent->_color = _RB_color_black;
            if (_node_type::get_branch(sibling) == _RB_branch_right)
            {
                sibling->_right->_color = _RB_color_black; // child's color change
                this->_rotate_left(sibling);
            }
            else
            {
                sibling->_left->_color = _RB_color_black; // child's color change
                this->_rotate_right(sibling);
            }
        }

        /*! @brief Erase rebalance case "BLACK sibling with RED another-branch child"

            Solution is in rotate aroung sibling and some recolors
            for jump to "RED same-branch child" case.

            @param sibling  pointer to sibling of "deleted" node
        */
        inline void     _erase_rebalance_case__black_red_anotherb(_node_type *sibling)
        {
            sibling->_color = _RB_color_red;
            if (_node_type::get_branch(sibling) == _RB_branch_right)
            {
                sibling->_left->_color = _RB_color_black;
                this->_rotate_right(sibling->_left);
            }
            else
            {
                sibling->_right->_color = _RB_color_black;
                this->_rotate_left(sibling->_right);
            }
            // another-branch child became sibling's parent, so do next jump:
            this->_erase_rebalance_case__black_red_sameb(sibling->_parent);
        }

        /*! @brief Erase rebalance case "BLACK sibling with BLACK children"

            Solution is in recolor sibling's node and parent.
            Then recursive call rebalance of parent, if parent was black,
            otherwise algorithm stops.

            @param sibling  pointer to sibling of "deleted" node
        */
        inline void     _erase_rebalance_case__black_black(_node_type *sibling)
        {
            sibling->_color = _RB_color_red;
            if (sibling->_parent->_color != _RB_color_red)
                this->_erase_rebalance(sibling->_parent, sibling->_parent->_parent);   // recursive call
            else
                sibling->_parent->_color = _RB_color_black; // end of algorithm
        }

         /*! @brief Erase rebalance case "RED sibling"

            Solution is in recolor nodes and rotate
            for jump to case "BLACK sibling"

            @param child    pointer to "deleted" node
            @param parent   pointer to parent of "deleted" node
            @param sibling  pointer to sibling of "deleted" node
        */
        inline void     _erase_rebalance_case__red(_node_type *child, _node_type *parent, _node_type *sibling)
        {
            sibling->_parent->_color = _RB_color_red;
            sibling->_color = _RB_color_black;
            if (_node_type::get_branch(sibling) == _RB_branch_right)
                this->_rotate_left(sibling);
            else
                this->_rotate_right(sibling);
            // recursive call for case choose
            this->_erase_rebalance(child, parent);
        }


        /**********************************/
        /*     Upper and lower bounds     */
        /**********************************/
        /*! @brief Recursive private lower_bound function

            @param root pointer to node where to search bound.
            @param value value to compare

            @return A pointer to first element
                    that is not less than key or NULL.
        */
        _node_type* _lower_bound(_node_type* root, const value_type& value)
        {
            _node_type* tmp;

            while (root)
            {
                if (this->_cmp(root->_value, value)) // value < key
                    root = root->_right;
                else // value >= key
                {
                    if (root->_left)
                    {
                        tmp = this->_lower_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

        /*! @brief Recursive private const lower_bound function

            @param root pointer to node where to search bound.
            @param value value to compare

            @return A const pointer to first element
                    that is not less than key or NULL.
        */
        const _node_type* _lower_bound(const _node_type* root,
                                 const value_type& value) const
        {
            const _node_type*   tmp;

            while (root)
            {
                if (this->_cmp(root->_value, value)) // value < key
                    root = root->_right;
                else // value >= key
                {
                    if (root->_left)
                    {
                        tmp = this->_lower_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

        /*! @brief Recursive private upper_bound function

            @param root pointer to node where to search bound.
            @param value value to compare

            @return A pointer to first element
                    that is greater than key or NULL.
        */
        _node_type* _upper_bound(_node_type* root, const value_type& value)
        {
            _node_type* tmp;

            while (root)
            {
                if (!this->_cmp(value, root->_value)) // value <= key
                    root = root->_right;
                else // value > key
                {
                    if (root->_left)
                    {
                        tmp = this->_upper_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

        /*! @brief Recursive private const upper_bound function

            @param root pointer to node where to search bound.
            @param value value to compare

            @return A const pointer to first element
                    that is greater than key or NULL.
        */
        const _node_type* _upper_bound(_node_type* root,
                                       const value_type& value) const
        {
            const _node_type* tmp;

            while (root)
            {
                if (!this->_cmp(value, root->_value)) // value <= key
                    root = root->_right;
                else // value > key
                {
                    if (root->_left)
                    {
                        tmp = this->_upper_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

#if _FT_RB_TREE_DEBUG
        /*****************/
        /*     Debug     */
        /*****************/
        /*! @brief Recursive colorized printing of the tree.
                   Order is: parent, left, right.

            @param node     the root of tree
            @param depth    alignment param (ussualy 0)
        */
        void    _print_tree(const _node_type *node, size_type depth, std::ostream& os = std::cout) const
        {
            for (size_type i = 0; i < depth; i++)
                os << "  ";

            if (_node_type::get_color(node) == _RB_color_black)
                os << "\x1b[40;1m[ ";
            else
                os << "\x1b[41;1m[ ";

            if (node)
                // os << node->_value;
                os << "val"; // for pairs
            else
                os << "(null)";
            os << " ]\x1b[m " << std::endl;
            if (node)
            {
                _print_tree(node->_left, depth + 1, os);
                _print_tree(node->_right, depth + 1, os);
            }
        }

        /*! @brief Recursive tree validation check.
            Return black-height of tree.

            @param node     current node of tree
            @param bheight  reference to store
                            current black-height of tree

            @return true or false -- valid or not
        */
        bool   _check_tree(const _node_type *node, size_type &bheight) const
        {
            // leaf node
            if (!node)
            {
                bheight = 0;
                return (true);
            }

            // color conflicts check
            if (node->_color == _RB_color_red && node->_parent->_color == _RB_color_red)
                return (false);

            // values check
            if (node != this->__header->_parent && node->_value != node->_parent->_value)
            {
                _RB_node_branch tmp_branch = _node_type::get_branch(node);
                if (tmp_branch == _RB_branch_left && !this->_cmp(node->_value, node->_parent->_value))
                    return (false);
                if (tmp_branch == _RB_branch_right && this->_cmp(node->_value, node->_parent->_value))
                    return (false);
            }

            // height check
            size_type   bheight_left, bheight_right;
            if (_check_tree(node->_left, bheight_left) == false)
                return (false);
            if (_check_tree(node->_right, bheight_right) == false)
                return (false);
            if (bheight_left != bheight_right)
                return (false);

            // substrees are ok, this tree is ok
            bheight = bheight_left;
            if (node->_color == _RB_color_black)
                bheight += 1;
            return (true);
        }

        friend std::ostream&    operator<<(std::ostream& os, const _RB_tree& rb_tree)
        {
            size_t  bheight;

            os << "Valid tree: " << (rb_tree._check_tree(rb_tree.__header->_parent, bheight) ? "true" : "false") << "\n";
            os << "With black height: " << bheight << std::endl;
            rb_tree._print_tree(rb_tree.__header->_parent, 1, os);
            return os;
        }
#endif
    };  /* _RB_tree */

}

#endif /* __FT_RB_TREE_HPP__ */
