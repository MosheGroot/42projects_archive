#ifndef __FT_ITERATOR_HPP__
# define __FT_ITERATOR_HPP__

# include <cstddef>

namespace ft
{
    /* Iterator_traits
        Interface for access to properties of iterator
    */
    template<class _Iterator>
    struct iterator_traits
    {
        typedef typename _Iterator::iterator_category   iterator_category;
        typedef typename _Iterator::value_type          value_type;
        typedef typename _Iterator::difference_type     difference_type;
        typedef typename _Iterator::pointer             pointer;
        typedef typename _Iterator::reference           reference;
    };


    /*
        Iterator tags
    */
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };


    /*
        Iterator struct
    */
    template<
        class Category,
        class T,
        class Distance = ptrdiff_t,
        class Pointer = T*,
        class Reference = T&
    > struct iterator
    {
        public:
            typedef Category    iterator_category;
            typedef T           value_type;
            typedef Distance    difference_type;
            typedef Pointer     pointer;
            typedef Reference   reference;
    };
}

#endif /* __FT_ITERATOR_HPP__ */