#include <iostream>
#include <vector>
#include "../ft_vector.hpp"
#include <set>
#include "../ft_set.hpp"
#include "tests.hpp"

# define STRESS_PUSH    5
# define STRESS_POP     5

void    compare_sets(std::set<int>& lhs, ft::set<int>& rhs);

void    stress_test(std::set<int>& lhs, ft::set<int>& rhs)
{
    for (int i = -100; i < -100 + STRESS_PUSH; i++)
        { lhs.insert(i); rhs.insert(i); }
    for (int i = -100 - STRESS_PUSH; i < -100; i++)
        { lhs.insert(i); rhs.insert(i); }


    size_t tmp1, tmp2;
    for (int i = -100; i < -100 + STRESS_POP; i++)
        {
            tmp1 = lhs.erase(i);
            tmp2 = rhs.erase(i);
            if (tmp1 != tmp2)
            {
                std::cout << RED "Stress test: KO" DEFAULT << '\n' << std::endl;
                return;
            }
        }
    for (int i = -100 - STRESS_POP; i < -100; i++)
        {
            tmp1 = lhs.erase(i);
            tmp2 = rhs.erase(i);
            if (tmp1 != tmp2)
            {
                std::cout << RED "Stress test: KO" DEFAULT << '\n' << std::endl;
                return;
            }
        }
}

template< class T>
void    print_set(T& set)
{
    std::cout << "[ ";
    for (typename T::const_iterator i = set.begin();
         i != set.end(); ++i)
        std::cout << *i << " ";
    std::cout << "]" << std::endl;
}

void    value_generator(int count, std::vector<int>& sv,
                       ft::vector<int>& fv)
{
    sv.clear();
    fv.clear();
    for (int i = 0; i < count / 2; i++)
    {
        sv.push_back(i * 2);
        fv.push_back(i * 2);
    }
    for (int i = 0; i < count / 2; i++)
    {
        sv.insert(sv.begin() + count / 4, i * 13);
        fv.insert(fv.begin() + count / 4, i * 13);
    }
}

void    compare_sets(std::set<int>& lhs, ft::set<int>& rhs)
{
    print_set(lhs);
    print_set(rhs);

    std::set<int>::const_iterator i = lhs.begin();
    ft::set<int>::const_iterator j = rhs.begin();
    for ( ; i != lhs.end() && j != rhs.end(); ++i, ++j)
        if (*i != *j)
        {
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
            return;
        }
    if (i != lhs.end() || j != rhs.end())
    {
        std::cout << RED "KO" DEFAULT << std::endl;
        return;
    }
    std::cout << GREEN "OK" DEFAULT << " | ";

    // size
    if (lhs.size() != rhs.size())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    // begin iterators
    if (lhs.size() && *lhs.begin() != *rhs.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    // last element
    if (lhs.size() && *(--lhs.end()) != *(--rhs.end()))
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    std::cout << '\n' << std::endl;
}

void    test_set_constructor_1_1(void)
{
    std::cout << YELLOW "1.1) Default constructor:" DEFAULT << std::endl;
    std::set<int>    sset;
    ft::set<int>     fset;

    compare_sets(sset, fset);
}

void    test_set_constructor_1_2(void)
{
    std::cout << YELLOW "1.2) Default constructor [+ add + erase]:" DEFAULT << std::endl;
    std::set<int>    sset;
    ft::set<int>     fset;

    stress_test(sset, fset);

    compare_sets(sset, fset);
}

void    test_set_constructor_2_1(void)
{
    std::cout << YELLOW "2.1) Default constructor with compare + allocator :" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::set<int>    sset(std::less<int>(), alloc);
    ft::set<int>     fset(std::less<int>(), alloc);

    compare_sets(sset, fset);
}

void    test_set_constructor_2_2(void)
{
    std::cout << YELLOW "2.2) Default constructor with allocator [+ add + erase]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::set<int>    sset(std::less<int>(), alloc);
    ft::set<int>     fset(std::less<int>(), alloc);

    stress_test(sset, fset);

    compare_sets(sset, fset);
}

void    test_set_constructor_3_1(void)
{
    std::cout << YELLOW "3.1) Range based constructor:" DEFAULT << std::endl;

    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>   fvec;
        value_generator(1, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        compare_sets(sset, fset);
    }
}

void    test_set_constructor_3_2(void)
{
    std::cout << YELLOW "3.2) Range based constructor [+ push + pop]:" DEFAULT << std::endl;

    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(0, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
}

void    test_set_constructor_5_1(void)
{
    std::cout << YELLOW "5.1) Copy constructor [empty]:" DEFAULT << std::endl;

    {
        std::set<int>    ssample;
        ft::set<int>     fsample;

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        compare_sets(sset, fset);
    }
}

void    test_set_constructor_5_2(void)
{
    std::cout << YELLOW "5.2) Copy constructor [empty + push + pop]:" DEFAULT << std::endl;

    {
        std::set<int>    ssample;
        ft::set<int>     fsample;

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
}

void    test_set_constructor_5_3(void)
{
    std::cout << YELLOW "5.3) Copy constructor [non-empty]:" DEFAULT << std::endl;

    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(15, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        compare_sets(sset, fset);
    }
}

void    test_set_constructor_5_4(void)
{
    std::cout << YELLOW "5.4) Copy constructor [+ non-empty + push + pop]:" DEFAULT << std::endl;

    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(15, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset(ssample);
        ft::set<int>     fset(fsample);

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
}

void    test_set_assignment_1_1(void)
{
    std::cout << YELLOW "1.1) operator= [to empty]:" DEFAULT << std::endl;

    {
        std::set<int>    ssample;
        ft::set<int>     fsample;

        std::set<int>    sset;
        ft::set<int>     fset;

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset;
        ft::set<int>     fset;

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset;
        ft::set<int>     fset;

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(15, svec, fvec);

        std::set<int>    ssample(svec.begin(), svec.end());
        ft::set<int>     fsample(fvec.begin(), fvec.end());

        std::set<int>    sset;
        ft::set<int>     fset;

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
}

void    test_set_assignment_1_2(void)
{
    std::cout << YELLOW "1.2) operator= [to non-empty]:" DEFAULT << std::endl;

    {
        std::vector<int>  svec1;
        ft::vector<int>    fvec1;
        value_generator(0, svec1, fvec1);
        std::vector<int>  svec2;
        ft::vector<int>    fvec2;
        value_generator(15, svec2, fvec2);

        std::set<int>    ssample(svec1.begin(), svec1.end());
        ft::set<int>     fsample(fvec1.begin(), fvec1.end());

        std::set<int>    sset(svec2.begin(), svec2.end());
        ft::set<int>     fset(fvec2.begin(), fvec2.end());

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec1;
        ft::vector<int>    fvec1;
        value_generator(1, svec1, fvec1);
        std::vector<int>  svec2;
        ft::vector<int>    fvec2;
        value_generator(15, svec2, fvec2);

        std::set<int>    ssample(svec1.begin(), svec1.end());
        ft::set<int>     fsample(fvec1.begin(), fvec1.end());

        std::set<int>    sset(svec2.begin(), svec2.end());
        ft::set<int>     fset(fvec2.begin(), fvec2.end());

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec1;
        ft::vector<int>    fvec1;
        value_generator(5, svec1, fvec1);
        std::vector<int>  svec2;
        ft::vector<int>    fvec2;
        value_generator(15, svec2, fvec2);

        std::set<int>    ssample(svec1.begin(), svec1.end());
        ft::set<int>     fsample(fvec1.begin(), fvec1.end());

        std::set<int>    sset(svec2.begin(), svec2.end());
        ft::set<int>     fset(fvec2.begin(), fvec2.end());

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec1;
        ft::vector<int>    fvec1;
        value_generator(15, svec1, fvec1);
        std::vector<int>  svec2;
        ft::vector<int>    fvec2;
        value_generator(5, svec2, fvec2);

        std::set<int>    ssample(svec1.begin(), svec1.end());
        ft::set<int>     fsample(fvec1.begin(), fvec1.end());

        std::set<int>    sset(svec2.begin(), svec2.end());
        ft::set<int>     fset(fvec2.begin(), fvec2.end());

        sset = ssample;
        fset = fsample;

        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
}

void    test_set_get_allocator(void)
{
    std::cout << YELLOW "get_allocator: " DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    if (sset.get_allocator() != fset.get_allocator())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    std::cout << '\n' << std::endl;
}

void    test_set_iterators_1_1(void)
{
    std::cout << YELLOW "1.1) iterators [empty]:" DEFAULT << std::endl;

    std::set<int>    sset;
    ft::set<int>     fset;

    for (std::set<int>::iterator i = sset.begin(); i != sset.end(); ++i)
        *i;

    for (ft::set<int>::iterator i = fset.begin(); i != fset.end(); ++i)
        *i;

    std::set<int>::iterator  s_it = sset.begin();
    // s_it++; ++s_it; s_it--; --s_it;  // infinite
    std::cout << "std: ";
    if (s_it != sset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::iterator  f_it = fset.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;


    compare_sets(sset, fset);
}

void    test_set_iterators_1_2(void)
{
    std::cout << YELLOW "1.2) iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    for (std::set<int>::iterator i = sset.begin(); i != sset.end(); ++i)
        *i;

    for (ft::set<int>::iterator i = fset.begin(); i != fset.end(); ++i)
        *i;

    std::set<int>::iterator  s_it = sset.begin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != sset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::iterator  f_it = fset.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_sets(sset, fset);
}

void    test_set_iterators_2_1(void)
{
    std::cout << YELLOW "2.1) const_iterators [empty]:" DEFAULT << std::endl;

    std::set<int>    sset;
    ft::set<int>     fset;

    for (std::set<int>::const_iterator i = sset.begin(); i != sset.end(); ++i)
        *i;

    for (ft::set<int>::const_iterator i = fset.begin(); i != fset.end(); ++i)
        *i;

    std::set<int>::const_iterator  s_it = sset.begin();
    // s_it++; ++s_it; s_it--; --s_it; // infinite
    std::cout << "std: ";
    if (s_it != sset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::const_iterator  f_it = fset.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_sets(sset, fset);
}

void    test_set_iterators_2_2(void)
{
    std::cout << YELLOW "2.2) const_iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    for (std::set<int>::const_iterator i = sset.begin(); i != sset.end(); ++i)
        *i;

    for (ft::set<int>::const_iterator i = fset.begin(); i != fset.end(); ++i)
        *i;

    std::set<int>::const_iterator  s_it = sset.begin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != sset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::const_iterator  f_it = fset.begin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_sets(sset, fset);
}


void    test_set_iterators_3(void)
{
    std::cout << YELLOW "3) iterators order:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    for (std::set<int>::iterator i = sset.begin(); i != sset.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    for (ft::set<int>::iterator i = fset.begin(); i != fset.end(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    compare_sets(sset, fset);
}

void    test_set_rev_iterators_1_1(void)
{
    std::cout << YELLOW "1.1) reverse iterators [empty]:" DEFAULT << std::endl;

    std::set<int>    sset;
    ft::set<int>     fset;

    for (std::set<int>::reverse_iterator i = sset.rbegin(); i != sset.rend(); ++i)
        *i;

    for (ft::set<int>::reverse_iterator i = fset.rbegin(); i != fset.rend(); ++i)
        *i;

    std::set<int>::reverse_iterator  s_it = sset.rbegin();
    // s_it++; ++s_it; s_it--; --s_it; // SEGV
    std::cout << "std: ";
    if (s_it != sset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::reverse_iterator  f_it = fset.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_sets(sset, fset);
}

void    test_set_rev_iterators_1_2(void)
{
    std::cout << YELLOW "1.2) reverse iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    for (std::set<int>::reverse_iterator i = sset.rbegin(); i != sset.rend(); ++i)
        *i;

    for (ft::set<int>::reverse_iterator i = fset.rbegin(); i != fset.rend(); ++i)
        *i;

    std::set<int>::reverse_iterator  s_it = sset.rbegin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != sset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::reverse_iterator  f_it = fset.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;


    compare_sets(sset, fset);
}

void    test_set_rev_iterators_2_1(void)
{
    std::cout << YELLOW "2.1) const_reverse_iterators [empty]:" DEFAULT << std::endl;

    std::set<int>    sset;
    ft::set<int>     fset;

    for (std::set<int>::const_reverse_iterator i = sset.rbegin(); i != sset.rend(); ++i)
        *i;

    for (ft::set<int>::const_reverse_iterator i = fset.rbegin(); i != fset.rend(); ++i)
        *i;

    std::set<int>::const_reverse_iterator  s_it = sset.rbegin();
    // s_it++; ++s_it; s_it--; --s_it; // SEGV
    std::cout << "std: ";
    if (s_it != sset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::const_reverse_iterator  f_it = fset.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_sets(sset, fset);
}

void    test_set_rev_iterators_2_2(void)
{
    std::cout << YELLOW "2.2) const_reverse_iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    for (std::set<int>::const_reverse_iterator i = sset.rbegin(); i != sset.rend(); ++i)
        *i;

    for (ft::set<int>::const_reverse_iterator i = fset.rbegin(); i != fset.rend(); ++i)
        *i;

    std::set<int>::const_reverse_iterator  s_it = sset.rbegin();
    s_it++; ++s_it; s_it--; --s_it;
    std::cout << "std: ";
    if (s_it != sset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::set<int>::const_reverse_iterator  f_it = fset.rbegin();
    f_it++; ++f_it; f_it--; --f_it;
    std::cout << "ft:  ";
    if (f_it != fset.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;


    compare_sets(sset, fset);
}

void    test_set_rev_iterators_3(void)
{
    std::cout << YELLOW "3) reverse_iterators order:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    for (std::set<int>::reverse_iterator i = sset.rbegin(); i != sset.rend(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    for (ft::set<int>::reverse_iterator i = fset.rbegin(); i != fset.rend(); ++i)
        std::cout << *i << ' ';
    std::cout << std::endl;

    compare_sets(sset, fset);
}

void    test_set_capacity_1(void)
{
    std::cout << YELLOW "1) Empty:" DEFAULT << std::endl;

    {
        std::set<int>    sset;
        ft::set<int>     fset;

        if (sset.empty() == fset.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        if (sset.empty() == fset.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        if (sset.empty() == fset.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(15, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        if (sset.empty() == fset.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_set_capacity_2(void)
{
    std::cout << YELLOW "2) Size:" DEFAULT << std::endl;

    {
        std::set<int>    sset;
        ft::set<int>     fset;

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(15, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_set_capacity_3(void)
{
    std::cout << YELLOW "3) max_size:" DEFAULT << std::endl;

    {
        std::allocator<int> alloc;
        std::set<int>    sset(std::less<int>(), alloc);
        ft::set<int>     fset(std::less<int>(), alloc);

        std::cout << sset.max_size() << '\n' << fset.max_size() << std::endl;
        if (sset.max_size() == fset.max_size())
            std::cout << GREEN "SAME" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "DIFF" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_set_clear(void)
{
    std::cout << YELLOW "1) clear:" DEFAULT << std::endl;

    {
        std::set<int>    sset;
        ft::set<int>     fset;

        sset.clear();
        fset.clear();

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(1, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.clear();
        fset.clear();

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(5, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.clear();
        fset.clear();

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
    {
        std::vector<int>  svec;
        ft::vector<int>    fvec;
        value_generator(15, svec, fvec);

        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.clear();
        fset.clear();

        if (sset.size() == fset.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(sset, fset);
        compare_sets(sset, fset);
    }
}

void    test_set_insert_1(void)
{
    std::cout << YELLOW "2.1) insert [pair]:" DEFAULT << std::endl;

    std::set<int>    sset;
    ft::set<int>     fset;

    compare_sets(sset, fset);

    if (sset.insert(15).second !=
        fset.insert(15).second)
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    compare_sets(sset, fset);

    if (sset.insert(3).second !=
    fset.insert(3).second)
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    compare_sets(sset, fset);

    if (sset.insert(-100).second !=
    fset.insert(-100).second)
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    compare_sets(sset, fset);

    if (sset.insert(-1000).second !=
    fset.insert(-1000).second)
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    stress_test(sset, fset);
    compare_sets(sset, fset);
}

void    test_set_insert_2(void)
{
    std::cout << YELLOW "2.2) insert [pair with hint]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    compare_sets(sset, fset);

    sset.insert(sset.begin(), 15);
    fset.insert(fset.begin(), 15);

    compare_sets(sset, fset);

    sset.insert(sset.end(), 10);
    fset.insert(fset.end(), 10);

    stress_test(sset, fset);
    compare_sets(sset, fset);
}

void    test_set_insert_3(void)
{
    std::cout << YELLOW "2.3) insert [values by range]:" DEFAULT << std::endl;

    std::vector<int>  svec1;
    ft::vector<int>    fvec1;
    value_generator(5, svec1, fvec1);

    std::vector<int>  svec2;
    ft::vector<int>    fvec2;
    value_generator(10, svec2, fvec2);

    std::set<int>    sset;
    ft::set<int>     fset;

    compare_sets(sset, fset);

    sset.insert(svec1.begin(), svec1.end());
    fset.insert(fvec1.begin(), fvec1.end());

    compare_sets(sset, fset);

    sset.insert(svec2.begin(), svec2.end());
    fset.insert(fvec2.begin(), fvec2.end());

    stress_test(sset, fset);
    compare_sets(sset, fset);
}

void    test_set_erase_1(void)
{
    std::cout << YELLOW "3.1) erase [by iterator]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(10, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    compare_sets(sset, fset);

    sset.erase(sset.begin());
    fset.erase(fset.begin());

    compare_sets(sset, fset);

    sset.erase(++sset.begin());
    fset.erase(++fset.begin());

    compare_sets(sset, fset);

    sset.erase(++sset.end());
    fset.erase(++fset.end());

    compare_sets(sset, fset);

    sset.erase(++(++(++sset.begin())));
    fset.erase(++(++(++fset.begin())));

    stress_test(sset, fset);
    compare_sets(sset, fset);
}

void    test_set_erase_2(void)
{
    std::cout << YELLOW "3.2) erase [by range]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(10, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    compare_sets(sset, fset);

    sset.erase(++(++(++sset.begin())), (--(--(--sset.end()))));
    fset.erase(++(++(++fset.begin())), (--(--(--fset.end()))));

    compare_sets(sset, fset);

    sset.erase(++sset.begin(), sset.end());
    fset.erase(++fset.begin(), fset.end());

    compare_sets(sset, fset);

    sset.erase(sset.begin(), sset.end());
    fset.erase(fset.begin(), fset.end());

    stress_test(sset, fset);
    compare_sets(sset, fset);
}

void    test_set_erase_3(void)
{
    std::cout << YELLOW "3.3) erase [by key]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(10, svec, fvec);

    std::set<int>    sset(svec.begin(), svec.end());
    ft::set<int>     fset(fvec.begin(), fvec.end());

    compare_sets(sset, fset);

    sset.erase(6);
    fset.erase(6);
    compare_sets(sset, fset);

    sset.erase(0);
    fset.erase(0);
    compare_sets(sset, fset);

    sset.erase(4);
    fset.erase(4);
    compare_sets(sset, fset);

    sset.erase(8);
    fset.erase(8);

    stress_test(sset, fset);
    compare_sets(sset, fset);
}

void    test_set_swap_1(void)
{
    std::cout << YELLOW "4.1) swap [empties]:" DEFAULT << std::endl;

    std::set<int>    sset1, sset2;
    ft::set<int>     fset1, fset2;

    compare_sets(sset1, fset1);

    sset1.swap(sset2);
    fset1.swap(fset2);

    stress_test(sset1, fset1);
    compare_sets(sset1, fset1);
}

void    test_set_swap_2(void)
{
    std::cout << YELLOW "4.2) swap [one empty, one not]:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1, sset2(svec.begin(), svec.end());
    ft::set<int>     fset1, fset2(fvec.begin(), fvec.end());

    compare_sets(sset1, fset1);

    sset1.swap(sset2);
    fset1.swap(fset2);

    stress_test(sset1, fset1);
    compare_sets(sset1, fset1);
}

void    test_set_swap_3(void)
{
    std::cout << YELLOW "4.3) swap [non-empty]:" DEFAULT << std::endl;

    std::vector<int>  svec1, svec2;
    ft::vector<int>    fvec1, fvec2;
    value_generator(5, svec1, fvec1);
    value_generator(10, svec2, fvec2);

    std::set<int>    sset1(svec1.begin(), svec1.end()),
                            sset2(svec2.begin(), svec2.end());
    ft::set<int>     fset1(fvec1.begin(), fvec1.end()),
                            fset2(fvec2.begin(), fvec2.end());

    compare_sets(sset1, fset1);

    sset1.swap(sset2);
    fset1.swap(fset2);

    stress_test(sset1, fset1);
    compare_sets(sset1, fset1);
}

void    test_set_count(void)
{
    std::cout << YELLOW "1) Count:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        bool error = false;
        for (int i = -100; i < 100; i++)
            if (sset.count(i) != fset.count(i))
            {
                error = true; break;
            }
        if (!error)
            std::cout << GREEN "OK" DEFAULT << " | " << std::flush;
        else
            std::cout << RED "KO" DEFAULT << " | " << std::flush;
    }
    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.insert(5);
        fset.insert(5);

        sset.insert(35);
        fset.insert(35);

        sset.insert(-19);
        fset.insert(-19);

        sset.insert(-18);
        fset.insert(-18);

        bool error = false;
        for (int i = -100; i < 100; i++)
            if (sset.count(i) != fset.count(i))
            {
                error = true; break;
            }
        if (!error)
            std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
        else
            std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    }
}

void    test_set_equal_range()
{
    std::cout << YELLOW "2) Equal range:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::pair<
        std::set<int>::iterator,
        std::set<int>::iterator > stmp_pair;
    ft::pair<
        ft::set<int>::iterator,
        ft::set<int>::iterator > ftmp_pair;

    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        bool error = false;
        for (int i = -100; i < 100; i++)
        {
            stmp_pair = sset.equal_range(i);
            ftmp_pair = fset.equal_range(i);

            if (stmp_pair.first == stmp_pair.second &&
                ftmp_pair.first != ftmp_pair.second)
            {
                std::cout << RED 1;
                error = true; break;
            }
            else if (stmp_pair.first == sset.end() &&
                     ftmp_pair.first != fset.end())
            {
                std::cout << RED 2;
                error = true; break;
            }
            else if (stmp_pair.second == sset.end() &&
                     ftmp_pair.second != fset.end())
            {
                std::cout << RED 3;
                error = true; break;
            }
            else
            {
                std::set<int>::iterator sit;
                ft::set<int>::iterator fit;
                for (sit = stmp_pair.first, fit = ftmp_pair.first;
                     sit != stmp_pair.second && fit != ftmp_pair.second;
                     ++sit, ++fit)
                    if (*sit != *fit)
                    {
                        std::cout << RED 4;
                        error = true; break;
                    }
                if (!error &&
                    (sit != stmp_pair.second || fit != ftmp_pair.second))
                {
                    std::cout << RED 5;
                    error = true;
                }
                if (error)
                    break;
            }
        }

        if (!error)
            std::cout << GREEN "OK" DEFAULT << " | " << std::flush;
        else
            std::cout << RED "KO" DEFAULT << " | " << std::flush;
    }
    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.insert(5);
        fset.insert(5);

        sset.insert(35);
        fset.insert(35);

        sset.insert(-19);
        fset.insert(-19);

        sset.insert(-18);
        fset.insert(-18);

        bool error = false;
        for (int i = -100; i < 100; i++)
        {
            stmp_pair = sset.equal_range(i);
            ftmp_pair = fset.equal_range(i);

            if (stmp_pair.first == stmp_pair.second &&
                ftmp_pair.first != ftmp_pair.second)
            {
                std::cout << RED 1;
                error = true; break;
            }
            else if (stmp_pair.first == sset.end() &&
                     ftmp_pair.first != fset.end())
            {
                std::cout << RED 2;
                error = true; break;
            }
            else if (stmp_pair.second == sset.end() &&
                     ftmp_pair.second != fset.end())
            {
                std::cout << RED 3;
                error = true; break;
            }
            else
            {
                std::set<int>::iterator sit;
                ft::set<int>::iterator fit;
                for (sit = stmp_pair.first, fit = ftmp_pair.first;
                     sit != stmp_pair.second && fit != ftmp_pair.second;
                     ++sit, ++fit)
                    if (*sit != *fit)
                    {
                        std::cout << RED 4;
                        error = true; break;
                    }
                if (!error &&
                    (sit != stmp_pair.second || fit != ftmp_pair.second))
                {
                    std::cout << RED 5;
                    error = true;
                }
                if (error)
                    break;
            }
        }

        if (!error)
            std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
        else
            std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    }
}

void    test_set_lower_bound()
{
    std::cout << YELLOW "3) Lower bound:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>::iterator stmp_it;
    ft::set<int>::iterator ftmp_it;

    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        bool error = false;
        for (int i = -100; i < 100; i++)
        {
            stmp_it = sset.lower_bound(i);
            ftmp_it = fset.lower_bound(i);

            if (stmp_it == sset.end() && ftmp_it != fset.end())
            {
                std::cout << RED 1;
                error = true; break;
            }
            else if (stmp_it == sset.end() && ftmp_it == fset.end())
                continue;

            // std::cout << i
            // << " { " << stmp_it->first << " ; " << stmp_it->second
            // << " } " << "{ " << ftmp_it->first << " ; " << ftmp_it->second
            // << " } " << std::endl;
            if (*stmp_it != *ftmp_it)
            {
                std::cout << RED 2;
                error = true; break;
            }
        }

        if (!error)
            std::cout << GREEN "OK" DEFAULT << " | " << std::flush;
        else
            std::cout << RED "KO" DEFAULT << " | " << std::flush;
    }
    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.insert(5);
        fset.insert(5);

        sset.insert(35);
        fset.insert(35);

        sset.insert(-19);
        fset.insert(-19);

        sset.insert(-18);
        fset.insert(-18);

        bool error = false;
        for (int i = -100; i < 100; i++)
        {
            stmp_it = sset.lower_bound(i);
            ftmp_it = fset.lower_bound(i);

            if (stmp_it == sset.end() && ftmp_it != fset.end())
            {
                std::cout << RED 1;
                error = true; break;
            }
            else if (stmp_it == sset.end() && ftmp_it == fset.end())
                continue;

            // std::cout << i
            // << " { " << stmp_it->first << " ; " << stmp_it->second
            // << " } " << "{ " << ftmp_it->first << " ; " << ftmp_it->second
            // << " } " << std::endl;
            if (*stmp_it != *ftmp_it)
            {
                std::cout << RED 2;
                error = true; break;
            }
        }

        if (!error)
            std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
        else
            std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    }
}

void    test_set_upper_bound()
{
    std::cout << YELLOW "3) Upper bound:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>::iterator stmp_it;
    ft::set<int>::iterator ftmp_it;

    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        bool error = false;
        for (int i = -100; i < 100; i++)
        {
            stmp_it = sset.upper_bound(i);
            ftmp_it = fset.upper_bound(i);

            if (stmp_it == sset.end() && ftmp_it != fset.end())
            {
                std::cout << RED 1;
                error = true; break;
            }
            else if (stmp_it == sset.end() && ftmp_it == fset.end())
                continue;

            if (*stmp_it != *ftmp_it)
            {
                std::cout << RED 2;
                error = true; break;
            }
        }

        if (!error)
            std::cout << GREEN "OK" DEFAULT << " | " << std::flush;
        else
            std::cout << RED "KO" DEFAULT << " | " << std::flush;
    }
    {
        std::set<int>    sset(svec.begin(), svec.end());
        ft::set<int>     fset(fvec.begin(), fvec.end());

        sset.insert(5);
        fset.insert(5);

        sset.insert(35);
        fset.insert(35);

        sset.insert(-19);
        fset.insert(-19);

        sset.insert(-18);
        fset.insert(-18);

        bool error = false;
        for (int i = -100; i < 100; i++)
        {
            stmp_it = sset.upper_bound(i);
            ftmp_it = fset.upper_bound(i);

            if (stmp_it == sset.end() && ftmp_it != fset.end())
            {
                std::cout << RED 1;
                error = true; break;
            }
            else if (stmp_it == sset.end() && ftmp_it == fset.end())
                continue;

            if (*stmp_it != *ftmp_it)
            {
                std::cout << RED 2;
                error = true; break;
            }
        }

        if (!error)
            std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
        else
            std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    }
}

void    test_set_key_comp(void)
{
    std::cout << YELLOW "1) Get key compare function:" DEFAULT << std::endl;
    std::set<int>    sset;
    ft::set<int>     fset;

    stress_test(sset, fset);

    if (sset.key_comp()(5, 2) != fset.key_comp()(5, 2))
        std::cout << RED "KO" DEFAULT << " " << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << " " << std::flush;

    if (sset.key_comp()(1, 2) != fset.key_comp()(1, 2))
        std::cout << RED "KO" DEFAULT << " " << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << " " << std::flush;

    if (sset.key_comp()(5, 5) != fset.key_comp()(5, 5))
        std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
}

void    test_set_value_comp(void)
{
    std::cout << YELLOW "1) Get value compare function:" DEFAULT << std::endl;
    std::set<int>    sset;
    ft::set<int>     fset;

    stress_test(sset, fset);

    if (sset.key_comp()(5, 2) != fset.key_comp()(5, 2))
        std::cout << RED "KO" DEFAULT << " " << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << " " << std::flush;

    if (sset.key_comp()(1, 2) != fset.key_comp()(1, 2))
        std::cout << RED "KO" DEFAULT << " " << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << " " << std::flush;

    if (sset.key_comp()(5, 5) != fset.key_comp()(5, 5))
        std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
}

void    test_set_compare_1(void)
{
    std::cout << YELLOW "1) == :" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    print_set(fset1);
    print_set(fset2);
    std::cout << std::boolalpha << (fset1 == fset2) << " : ";
    if ((fset1 == fset2) == (sset1 == sset2))
        std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
    else
        std::cout << RED "KO" DEFAULT << '\n' << std::endl;

    fset2 = fset1;
    sset2 = sset1;

    print_set(fset1);
    print_set(fset2);
    std::cout << std::boolalpha << (fset1 == fset2) << " : ";
    if ((fset1 == fset2) == (sset1 == sset2))
        std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
    else
        std::cout << RED "KO" DEFAULT << '\n' << std::endl;
}

void    test_set_compare_2(void)
{
    std::cout << YELLOW "2) != :" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    {
        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 != fset2) << " : ";
        if ((fset1 != fset2) == (sset1 != sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset2 = sset1;
        fset2 = fset1;

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 != fset2) << " : ";
        if ((fset1 != fset2) == (sset1 != sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset2.erase(0);
        fset2.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 != fset2) << " : ";
        if ((fset1 != fset2) == (sset1 != sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_set_compare_3(void)
{
    std::cout << YELLOW "3) > :" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    {
        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 > fset2) << " : ";
        if ((fset1 > fset2) == (sset1 > sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset2 = sset1;
        sset2.erase(0);
        fset2 = fset1;
        fset2.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 > fset2) << " : ";
        if ((fset1 > fset2) == (sset1 > sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.erase(0);
        fset1.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 > fset2) << " : ";
        if ((fset1 > fset2) == (sset1 > sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(2);
        sset2.insert(5);
        fset1.insert(2);
        fset2.insert(5);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 > fset2) << " : ";
        if ((fset1 > fset2) == (sset1 > sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(100);
        sset2.insert(50);
        fset1.insert(100);
        fset2.insert(50);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 > fset2) << " : ";
        if ((fset1 > fset2) == (sset1 > sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_set_compare_4(void)
{
    std::cout << YELLOW "4) < :" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    {
        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 < fset2) << " : ";
        if ((fset1 < fset2) == (sset1 < sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset2 = sset1;
        sset2.erase(0);
        fset2 = fset1;
        fset2.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 < fset2) << " : ";
        if ((fset1 < fset2) == (sset1 < sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.erase(0);
        fset1.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 < fset2) << " : ";
        if ((fset1 < fset2) == (sset1 < sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(2);
        sset2.insert(5);
        fset1.insert(2);
        fset2.insert(5);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 < fset2) << " : ";
        if ((fset1 < fset2) == (sset1 < sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(100);
        sset2.insert(50);
        fset1.insert(100);
        fset2.insert(50);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 < fset2) << " : ";
        if ((fset1 < fset2) == (sset1 < sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_set_compare_5(void)
{
    std::cout << YELLOW "5) >= :" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    {
        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 >= fset2) << " : ";
        if ((fset1 >= fset2) == (sset1 >= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset2 = sset1;
        sset2.erase(0);
        fset2 = fset1;
        fset2.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 >= fset2) << " : ";
        if ((fset1 >= fset2) == (sset1 >= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.erase(0);
        fset1.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 >= fset2) << " : ";
        if ((fset1 >= fset2) == (sset1 >= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(2);
        sset2.insert(5);
        fset1.insert(2);
        fset2.insert(5);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 >= fset2) << " : ";
        if ((fset1 >= fset2) == (sset1 >= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(100);
        sset2.insert(50);
        fset1.insert(100);
        fset2.insert(50);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 >= fset2) << " : ";
        if ((fset1 >= fset2) == (sset1 >= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_set_compare_6(void)
{
    std::cout << YELLOW "6) <= :" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    {
        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 <= fset2) << " : ";
        if ((fset1 <= fset2) == (sset1 <= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset2 = sset1;
        sset2.erase(0);
        fset2 = fset1;
        fset2.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 <= fset2) << " : ";
        if ((fset1 <= fset2) == (sset1 <= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.erase(0);
        fset1.erase(0);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 <= fset2) << " : ";
        if ((fset1 <= fset2) == (sset1 <= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(2);
        sset2.insert(5);
        fset1.insert(2);
        fset2.insert(5);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 <= fset2) << " : ";
        if ((fset1 <= fset2) == (sset1 <= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sset1.insert(100);
        sset2.insert(50);
        fset1.insert(100);
        fset2.insert(50);

        print_set(fset1);
        print_set(fset2);
        std::cout << std::boolalpha << (fset1 <= fset2) << " : ";
        if ((fset1 <= fset2) == (sset1 <= sset2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_set_swap_nn(void)
{
    std::cout << YELLOW "1) swap:" DEFAULT << std::endl;

    std::vector<int>  svec;
    ft::vector<int>    fvec;
    value_generator(5, svec, fvec);

    std::set<int>    sset1(svec.begin(), svec.end()), sset2;
    ft::set<int>     fset1(fvec.begin(), fvec.end()), fset2;

    compare_sets(sset1, fset1);
    compare_sets(sset2, fset2);

    std::cout << "----------" << std::endl;

    std::swap(sset1, sset2);
    ft::swap(fset1, fset2);

    compare_sets(sset1, fset1);
    compare_sets(sset2, fset2);

    std::cout << "----------" << std::endl;

    std::swap(sset1, sset2);
    ft::swap(fset1, fset2);

    stress_test(sset1, fset1);
    stress_test(sset2, fset2);

    compare_sets(sset1, fset1);
    compare_sets(sset2, fset2);
}

void    ft_set_tests()
{
    std::cout << B_RED "[   FT_set   ]" DEFAULT << '\n' << std::endl;
    std::cout << B_CYAN "   Constructors   " DEFAULT << std::endl;
    test_set_constructor_1_1();
    test_set_constructor_1_2();

    test_set_constructor_2_1();
    test_set_constructor_2_2();

    test_set_constructor_3_1();
    test_set_constructor_3_2();

    test_set_constructor_5_1();
    test_set_constructor_5_2();
    test_set_constructor_5_3();
    test_set_constructor_5_4();

    std::cout << B_CYAN "   Assignments   " DEFAULT << std::endl;
    test_set_assignment_1_1();
    test_set_assignment_1_2();

    std::cout << B_CYAN "   Get allocator   " DEFAULT << std::endl;
    test_set_get_allocator();

    std::cout << B_CYAN "   Iterators   " DEFAULT << std::endl;
    test_set_iterators_1_1();
    test_set_iterators_1_2();
    test_set_iterators_2_1();
    test_set_iterators_2_2();
    test_set_iterators_3();

    std::cout << B_CYAN "   Reverse iterators   " DEFAULT << std::endl;
    test_set_rev_iterators_1_1();
    test_set_rev_iterators_1_2();
    test_set_rev_iterators_2_1();
    test_set_rev_iterators_2_2();
    test_set_rev_iterators_3();

    std::cout << B_CYAN "   Capacity   " DEFAULT << std::endl;
    test_set_capacity_1();
    test_set_capacity_2();
    test_set_capacity_3();

    std::cout << B_CYAN "   Modifiers   " DEFAULT << std::endl;
    test_set_clear();
    test_set_insert_1();
    test_set_insert_2();
    test_set_insert_3();
    test_set_erase_1();
    test_set_erase_2();
    test_set_erase_3();
    test_set_swap_1();
    test_set_swap_2();
    test_set_swap_3();

    std::cout << B_CYAN "   Lookup   " DEFAULT << std::endl;
    test_set_count();
    test_set_equal_range();
    test_set_lower_bound();
    test_set_upper_bound();

    std::cout << B_CYAN "   Observers   " DEFAULT << std::endl;
    test_set_key_comp();
    test_set_value_comp();

    std::cout << B_CYAN "   Non-member/compares   " DEFAULT << std::endl;
    test_set_compare_1();
    test_set_compare_2();
    test_set_compare_3();
    test_set_compare_4();
    test_set_compare_5();
    test_set_compare_6();

    std::cout << B_CYAN "   Non-member/swap   " DEFAULT << std::endl;
    test_set_swap_nn();
}
