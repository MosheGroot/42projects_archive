#ifndef __FT_META_HPP__
# define __FT_META_HPP__

namespace ft
{
    /* Enable_if    metafunction
        
        Signature:
            template< _condition, _Type >

        Behaviour:
            If condition is true, ::type field sets to _Type
            Otherwise, template does not match
    */
    template<bool _condition, typename _Type = void>
    struct enable_if {};

    template<typename _Type>
    struct enable_if<true, _Type>
    {
        typedef _Type   type;
    };


    /* Is_integral  metafunction

        Signature:
            template< T >

        Behaviour:
            Checks if T is integral type, i.e.:
                * bool              *
                * char
                * signed char
                * unsigned char
                * wchar_t
                * short
                * unsigned short
                * int
                * unsigned int
                * long
                * unsigned long
            But (!) not:
                * float
                * double
                * long double.
            And sets ::value to true or false.
    */
    template<typename T>
    struct is_integral { static const bool  value = false; };

    template<>  struct is_integral<bool>            { static const bool value = true; };
    template<>  struct is_integral<char>            { static const bool value = true; };
    template<>  struct is_integral<signed char>     { static const bool value = true; };
    template<>  struct is_integral<unsigned char>   { static const bool value = true; };
    template<>  struct is_integral<wchar_t>         { static const bool value = true; };
    template<>  struct is_integral<short>           { static const bool value = true; };
    template<>  struct is_integral<unsigned short>  { static const bool value = true; };
    template<>  struct is_integral<int>             { static const bool value = true; };
    template<>  struct is_integral<unsigned int>    { static const bool value = true; };
    template<>  struct is_integral<long>            { static const bool value = true; };
    template<>  struct is_integral<unsigned long>   { static const bool value = true; };

}

#endif  /* __FT_META_HPP__ */
