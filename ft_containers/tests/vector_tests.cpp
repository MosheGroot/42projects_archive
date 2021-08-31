#include <iostream>
#include <vector>
#include "../ft_vector.hpp"
#include "tests.hpp"

# define STRESS_PUSH    5
# define STRESS_POP     5

void    stress_test(std::vector<int>& lhs, ft::vector<int>& rhs)
{
    for (int i = 0; i < STRESS_PUSH; i++)
        { lhs.push_back(i); rhs.push_back(i); }

    for (int i = 0; i < STRESS_POP; i++)
        { lhs.pop_back(); rhs.pop_back(); }
}

template< class T>
void    print_stack(const T& vec)
{
    std::cout << "[ ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << "]" << std::endl;
}

void    compare_vectors(const std::vector<int>& lhs, const ft::vector<int>& rhs)
{
    print_stack(lhs);
    print_stack(rhs);

    for (size_t i = 0; i < lhs.size(); i++)
        if (lhs[i] != rhs[i])
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

    // front
    if (lhs.size() && lhs.front() != rhs.front())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    // back
    if (lhs.size() && lhs.back() != rhs.back())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    // begin iterators
    if ((lhs.size() && *lhs.begin() != *rhs.begin())
        || (!lhs.size() && rhs.begin() != rhs.end()))
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT  << ' ' << std::flush;

    // begin-end distance
    if (std::distance(lhs.begin(), lhs.end()) != ft::distance(rhs.begin(), rhs.end()))
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    std::cout << '\n' << std::endl;
}

void    test_vector_constructor_1_1(void)
{
    std::cout << YELLOW "1.1) Default constructor:" DEFAULT << std::endl;
    std::vector<int>    svec;
    ft::vector<int>     fvec;

    compare_vectors(svec, fvec);
}

void    test_vector_constructor_1_2(void)
{
    std::cout << YELLOW "1.2) Default constructor [+ push + pop]:" DEFAULT << std::endl;
    std::vector<int>    svec;
    ft::vector<int>     fvec;

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);
}

void    test_vector_constructor_2_1(void)
{
    std::cout << YELLOW "2.1) Default constructor with allocator:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::vector<int>    svec(alloc);
    ft::vector<int>     fvec(alloc);

    compare_vectors(svec, fvec);
}

void    test_vector_constructor_2_2(void)
{
    std::cout << YELLOW "2.2) Default constructor with allocator [+ push + pop]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::vector<int>    svec(alloc);
    ft::vector<int>     fvec(alloc);

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);
}

void    test_vector_constructor_3_1(void)
{
    std::cout << YELLOW "3.1) Size based constructor:" DEFAULT << std::endl;

    std::vector<int>    svec(5, 123);
    ft::vector<int>     fvec(5, 123);

    compare_vectors(svec, fvec);
}

void    test_vector_constructor_3_2(void)
{
    std::cout << YELLOW "3.2) Size based constructor [+ allocator]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::vector<int>    svec(5, 123, alloc);
    ft::vector<int>     fvec(5, 123, alloc);

    compare_vectors(svec, fvec);
}

void    test_vector_constructor_3_3(void)
{
    std::cout << YELLOW "3.3) Size based constructor [+ push + pop]:" DEFAULT << std::endl;

    std::vector<int>    svec(5, 123);
    ft::vector<int>     fvec(5, 123);

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);
}

void    test_vector_constructor_3_4(void)
{
    std::cout << YELLOW "3.4) Size based constructor [+ alloc + push + pop]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    std::vector<int>    svec(5, 123, alloc);
    ft::vector<int>     fvec(5, 123, alloc);

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);
}

void    test_vector_constructor_4_1(void)
{
    std::cout << YELLOW "4.1) Range based constructor [+ various sizes]:" DEFAULT << std::endl;

    {
        std::vector<int>    sample(0, 7);

        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(1, 7);

        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(3, 7);

        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_4_2(void)
{
    std::cout << YELLOW "4.2) Range based constructor [+ various sizes + alloc]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;

    {
        std::vector<int>    sample(0, 7);

        std::vector<int>    svec(sample.begin(), sample.end(), alloc);
        ft::vector<int>     fvec(sample.begin(), sample.end(), alloc);

        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(1, 7);

        std::vector<int>    svec(sample.begin(), sample.end(), alloc);
        ft::vector<int>     fvec(sample.begin(), sample.end(), alloc);

        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(3, 7);

        std::vector<int>    svec(sample.begin(), sample.end(), alloc);
        ft::vector<int>     fvec(sample.begin(), sample.end(), alloc);

        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_4_3(void)
{
    std::cout << YELLOW "4.3) Range based constructor [+ various sizes + push + pop]:" DEFAULT << std::endl;

    {
        std::vector<int>    sample(0, 7);

        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(1, 7);

        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(3, 7);

        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_4_4(void)
{
    std::cout << YELLOW "4.4) Range based constructor [+ various sizes + alloc + push + pop]:" DEFAULT << std::endl;

    std::allocator<int>  alloc;


    {
        std::vector<int>    sample(0, 7);

        std::vector<int>    svec(sample.begin(), sample.end(), alloc);
        ft::vector<int>     fvec(sample.begin(), sample.end(), alloc);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(1, 7);

        std::vector<int>    svec(sample.begin(), sample.end(), alloc);
        ft::vector<int>     fvec(sample.begin(), sample.end(), alloc);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(3, 7);

        std::vector<int>    svec(sample.begin(), sample.end(), alloc);
        ft::vector<int>     fvec(sample.begin(), sample.end(), alloc);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_5_1(void)
{
    std::cout << YELLOW "5.1) Copy constructor [empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample;
        ft::vector<int>     fsample;

        std::vector<int>    svec(ssample);
        ft::vector<int>     fvec(fsample);

        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_5_2(void)
{
    std::cout << YELLOW "5.2) Copy constructor [empty + push + pop]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample;
        ft::vector<int>     fsample;

        std::vector<int>    svec(ssample);
        ft::vector<int>     fvec(fsample);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_5_3(void)
{
    std::cout << YELLOW "5.3) Copy constructor [non-empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample(10, 5);
        ft::vector<int>     fsample(10, 5);

        std::vector<int>    svec(ssample);
        ft::vector<int>     fvec(fsample);

        compare_vectors(svec, fvec);
    }
}

void    test_vector_constructor_5_4(void)
{
    std::cout << YELLOW "5.4) Copy constructor [+ non-empty + push + pop]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample(10, 5);
        ft::vector<int>     fsample(10, 5);

        std::vector<int>    svec(ssample);
        ft::vector<int>     fvec(fsample);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_assignment_1_1(void)
{
    std::cout << YELLOW "1.1) operator= [to empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample;
        ft::vector<int>     fsample;

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(0, 15);
        ft::vector<int>     fsample(0, 15);

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(1, 7);
        ft::vector<int>     fsample(1, 7);

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(3, 7);
        ft::vector<int>     fsample(3, 7);

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_assignment_1_2(void)
{
    std::cout << YELLOW "1.2) operator= [to non-empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample;
        ft::vector<int>     fsample;

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(0, 15);
        ft::vector<int>     fsample(0, 15);

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(1, 7);
        ft::vector<int>     fsample(1, 7);

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(3, 7);
        ft::vector<int>     fsample(3, 7);

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec = ssample;
        fvec = fsample;

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_assignment_2_1(void)
{
    std::cout << YELLOW "2.1) Size based assigment [to empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(0, 7);
        fvec.assign(0, 7);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(1, 7);
        fvec.assign(1, 7);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(5, 7);
        fvec.assign(5, 7);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_assignment_2_2(void)
{
    std::cout << YELLOW "2.2) Size based assigment [to non-empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(0, 7);
        fvec.assign(0, 7);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(1, 7);
        fvec.assign(1, 7);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(5, 7);
        fvec.assign(5, 7);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_assignment_3_1(void)
{
    std::cout << YELLOW "3.1) Range based assigment [to empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample;

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(0, 15);

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(1, 7);

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(3, 7);

        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_assignment_3_2(void)
{
    std::cout << YELLOW "3.2) Range based assigment [to non-empty]:" DEFAULT << std::endl;

    {
        std::vector<int>    ssample;

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(0, 15);

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(1, 7);

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    ssample(3, 7);

        std::vector<int>    svec(1000, 5);
        ft::vector<int>     fvec(1000, 5);

        svec.assign(ssample.begin(), ssample.end());
        fvec.assign(ssample.begin(), ssample.end());

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_get_allocator(void)
{
    std::cout << YELLOW "get_allocator: " DEFAULT << std::endl;

    std::vector<int>    svec(1000, 5);
    ft::vector<int>     fvec(1000, 5);

    if (svec.get_allocator() != fvec.get_allocator())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    std::cout << '\n' << std::endl;
}

void    test_vector_access_1_1(void)
{
    std::cout << YELLOW "1.1) at [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 5);
    ft::vector<int>     fvec(10, 5);

    for (ft::vector<int>::size_type i = 0; i < fvec.size(); i++)
        if (svec.at(i) != fvec.at(i))
        {
            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
    std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

    for (ft::vector<int>::size_type i = 0; i < fvec.size(); i++)
    {
        svec.at(i) = 7;
        fvec.at(i) = 7;
        if (svec.at(i) != fvec.at(i))
        {
            std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
    }
    std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_access_1_2(void)
{
    std::cout << YELLOW "1.2) at [empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(0, 5);
    ft::vector<int>     fvec(0, 5);

    try
    {
        fvec.at(0);
        std::cout << "const ref:\t" << RED "KO" DEFAULT << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception : " << e.what() << '\n';
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;
    }

    try
    {
        fvec.at(0) = 5;
        std::cout << "const ref:\t" << RED "KO" DEFAULT << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << "exception : " << e.what() << '\n';
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;
    }
    compare_vectors(svec, fvec);
}

void    test_vector_access_2(void)
{
    std::cout << YELLOW "2) operator[] [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 5);
    ft::vector<int>     fvec(10, 5);

    for (ft::vector<int>::size_type i = 0; i < fvec.size(); i++)
        if (svec[i] != fvec[i])
        {
            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
    std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

    for (ft::vector<int>::size_type i = 0; i < fvec.size(); i++)
    {
        svec[i] = 7;
        fvec[i] = 7;
        if (svec[i] != fvec[i])
        {
            std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
    }
    std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_access_3(void)
{
    std::cout << YELLOW "3) front [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 5);
    ft::vector<int>     fvec(10, 5);

    if (svec.front() != fvec.front())
    {
        std::cout << "const ref:\t" << RED "KO" DEFAULT << std::flush;
        return;
    }
    std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

    svec.front() = 7;
    fvec.front() = 7;
    if (svec.front() != fvec.front())
    {
        std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::flush;
        return;
    }
    std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_access_4(void)
{
    std::cout << YELLOW "4) back [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 5);
    ft::vector<int>     fvec(10, 5);

    {
        if (svec.back() != fvec.back())
        {
            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

        svec.back() = 7;
        fvec.back() = 7;
        if (svec.back() != fvec.back())
        {
            std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
        std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

        compare_vectors(svec, fvec);
    }

    svec.pop_back();
    fvec.pop_back();

    {
        if (svec.back() != fvec.back())
        {
            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;

        svec.back() = 7;
        fvec.back() = 7;
        if (svec.back() != fvec.back())
        {
            std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
        std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;

        compare_vectors(svec, fvec);
    }
}

void    test_vector_access_5(void)
{
    std::cout << YELLOW "5) data [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 5);
    ft::vector<int>     fvec(10, 5);

    svec.data()[0] = 123;
    fvec.data()[0] = 123;

    svec.data()[5] = 123;
    fvec.data()[5] = 123;

    compare_vectors(svec, fvec);
}

void    test_vector_iterators_1_1(void)
{
    std::cout << YELLOW "1.1) iterators [empty]:" DEFAULT << std::endl;

    std::vector<int>    svec;
    ft::vector<int>     fvec;

    for (std::vector<int>::iterator i = svec.begin(); i != svec.end(); ++i)
        *i = 0;

    for (ft::vector<int>::iterator i = fvec.begin(); i != fvec.end(); ++i)
        *i = 0;

    std::vector<int>::iterator  s_it = svec.begin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5; s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != svec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::vector<int>::iterator  f_it = fvec.begin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5; f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != fvec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_iterators_1_2(void)
{
    std::cout << YELLOW "1.2) iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 8);
    ft::vector<int>     fvec(10, 8);

    for (std::vector<int>::iterator i = svec.begin(); i != svec.end(); ++i)
        *i = 0;

    for (ft::vector<int>::iterator i = fvec.begin(); i != fvec.end(); ++i)
        *i = 0;

    std::vector<int>::iterator  s_it = svec.begin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5;
    *s_it = 5;
    s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    *s_it = 5;
    if (s_it != svec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::vector<int>::iterator  f_it = fvec.begin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5;
    *f_it = 5;
    f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    *f_it = 5;
    if (f_it != fvec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_iterators_2_1(void)
{
    std::cout << YELLOW "2.1) const_iterators [empty]:" DEFAULT << std::endl;

    std::vector<int>    svec;
    ft::vector<int>     fvec;

    for (std::vector<int>::const_iterator i = svec.begin(); i != svec.end(); ++i)
        *i;

    for (ft::vector<int>::const_iterator i = fvec.begin(); i != fvec.end(); ++i)
        *i;

    std::vector<int>::const_iterator  s_it = svec.begin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5; s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != svec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::vector<int>::const_iterator  f_it = fvec.begin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5; f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != fvec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_iterators_2_2(void)
{
    std::cout << YELLOW "2.2) const_iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 8);
    ft::vector<int>     fvec(10, 8);

    for (std::vector<int>::const_iterator i = svec.begin(); i != svec.end(); ++i)
        *i;

    for (ft::vector<int>::const_iterator i = fvec.begin(); i != fvec.end(); ++i)
        *i;

    std::vector<int>::const_iterator  s_it = svec.begin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5;
    s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != svec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::vector<int>::const_iterator  f_it = fvec.begin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5;
    f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != fvec.begin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_iterators_3(void)
{
    std::cout << YELLOW "3) iterators order: " DEFAULT << std::endl;

    std::vector<int>    svec(10);
    ft::vector<int>     fvec(10);

    for (std::vector<int>::iterator i = svec.begin(); i != svec.end(); ++i)
        *i = (int)std::distance(svec.begin(), i);

    for (ft::vector<int>::iterator i = fvec.begin(); i != fvec.end(); ++i)
        *i = (int)ft::distance(fvec.begin(), i);

    compare_vectors(svec, fvec);
}

void    test_vector_rev_iterators_1_1(void)
{
    std::cout << YELLOW "1.1) reverse iterators [empty]:" DEFAULT << std::endl;

    std::vector<int>    svec;
    ft::vector<int>     fvec;

    for (std::vector<int>::reverse_iterator i = svec.rbegin(); i != svec.rend(); ++i)
        *i = 0;

    for (ft::vector<int>::reverse_iterator i = fvec.rbegin(); i != fvec.rend(); ++i)
        *i = 0;

    std::vector<int>::reverse_iterator  s_it = svec.rbegin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5; s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != svec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    std::cout << " | KO is ok :)" << std::endl;

    ft::vector<int>::reverse_iterator  f_it = fvec.rbegin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5; f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != fvec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_rev_iterators_1_2(void)
{
    std::cout << YELLOW "1.2) reverse iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 8);
    ft::vector<int>     fvec(10, 8);

    for (std::vector<int>::reverse_iterator i = svec.rbegin(); i != svec.rend(); ++i)
        *i = 0;

    for (ft::vector<int>::reverse_iterator i = fvec.rbegin(); i != fvec.rend(); ++i)
        *i = 0;

    std::vector<int>::reverse_iterator  s_it = svec.rbegin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5;
    *s_it = 5;
    s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    *s_it = 5;
    if (s_it != svec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::vector<int>::reverse_iterator  f_it = fvec.rbegin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5;
    *f_it = 5;
    f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    *f_it = 5;
    if (f_it != fvec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_rev_iterators_2_1(void)
{
    std::cout << YELLOW "2.1) const_reverse_iterators [empty]:" DEFAULT << std::endl;

    std::vector<int>    svec;
    ft::vector<int>     fvec;

    for (std::vector<int>::const_reverse_iterator i = svec.rbegin(); i != svec.rend(); ++i)
        *i;

    for (ft::vector<int>::const_reverse_iterator i = fvec.rbegin(); i != fvec.rend(); ++i)
        *i;

    std::vector<int>::const_reverse_iterator  s_it = svec.rbegin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5; s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != svec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    std::cout << " | KO is ok :)" << std::endl;

    ft::vector<int>::const_reverse_iterator  f_it = fvec.rbegin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5; f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != fvec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_rev_iterators_2_2(void)
{
    std::cout << YELLOW "2.2) const_reverse_iterators [non-empty]:" DEFAULT << std::endl;

    std::vector<int>    svec(10, 8);
    ft::vector<int>     fvec(10, 8);

    for (std::vector<int>::const_reverse_iterator i = svec.rbegin(); i != svec.rend(); ++i)
        *i;

    for (ft::vector<int>::const_reverse_iterator i = fvec.rbegin(); i != fvec.rend(); ++i)
        *i;

    std::vector<int>::const_reverse_iterator  s_it = svec.rbegin();
    s_it++; ++s_it; s_it--; --s_it; s_it += 2; s_it -= 2;
    s_it = s_it + 5;
    s_it = s_it - 5;
    std::cout << "std: ";
    if (s_it < s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it > s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it <= s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it >= s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(s_it == s_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != s_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (s_it != svec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    ft::vector<int>::const_reverse_iterator  f_it = fvec.rbegin();
    f_it++; ++f_it; f_it--; --f_it; f_it += 2; f_it -= 2;
    f_it = f_it + 5;
    f_it = f_it - 5;
    std::cout << "ft:  ";
    if (f_it < f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it > f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it <= f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it >= f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (!(f_it == f_it + 5))
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != f_it + 5)
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
    else
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;

    if (f_it != fvec.rbegin())
        std::cout << RED "KO" DEFAULT << ' ' << std::endl;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::endl;

    compare_vectors(svec, fvec);
}

void    test_vector_rev_iterators_3(void)
{
    std::cout << YELLOW "3) reverse_iterators order:" DEFAULT << std::endl;

    std::vector<int>    svec(10);
    ft::vector<int>     fvec(10);

    for (std::vector<int>::reverse_iterator i = svec.rbegin(); i != svec.rend(); ++i)
        *i = (int)std::distance(svec.rbegin(), i);

    for (ft::vector<int>::reverse_iterator i = fvec.rbegin(); i != fvec.rend(); ++i)
        *i = (int)ft::distance(fvec.rbegin(), i);

    compare_vectors(svec, fvec);
}

void    test_vector_capacity_1(void)
{
    std::cout << YELLOW "1) Empty:" DEFAULT << std::endl;

    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        if (svec.empty() == fvec.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        if (svec.empty() == fvec.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>    svec(1, 5);
        ft::vector<int>     fvec(1, 5);

        if (svec.empty() == fvec.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>    sample(10, 50);
        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        if (svec.empty() == fvec.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_vector_capacity_2(void)
{
    std::cout << YELLOW "2) Size:" DEFAULT << std::endl;

    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>    svec(1, 5);
        ft::vector<int>     fvec(1, 5);

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::vector<int>    sample(10, 50);
        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_vector_capacity_3(void)
{
    std::cout << YELLOW "3) max_size:" DEFAULT << std::endl;

    {
        std::allocator<int> alloc;
        std::vector<int>    svec(alloc);
        ft::vector<int>     fvec(alloc);

        if (svec.max_size() == fvec.max_size())
            std::cout << GREEN "SAME" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "DIFF" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_vector_capacity_4(void)
{
    std::cout << YELLOW "4) reserve + capacity:" DEFAULT << std::endl;

    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.reserve(50);
        fvec.reserve(50);

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        if (svec.capacity() == fvec.capacity())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(1, 5);
        ft::vector<int>     fvec(1, 5);

        svec.reserve(50);
        fvec.reserve(50);

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        if (svec.capacity() == fvec.capacity())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        svec.reserve(50);
        fvec.reserve(50);

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        if (svec.capacity() == fvec.capacity())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(10, 50);
        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        svec.reserve(50);
        fvec.reserve(50);

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        if (svec.capacity() == fvec.capacity())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_clear(void)
{
    std::cout << YELLOW "1) clear:" DEFAULT << std::endl;

    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.clear();
        fvec.clear();

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(1, 5);
        ft::vector<int>     fvec(1, 5);

        svec.clear();
        fvec.clear();

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        svec.clear();
        fvec.clear();

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(10, 50);
        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        svec.clear();
        fvec.clear();

        if (svec.size() == fvec.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
        std::cout << std::endl;
        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_insert_erase(void)
{
    std::cout << YELLOW "2) insert:" DEFAULT << std::endl;

    std::vector<int>    svec;
    ft::vector<int>     fvec;

    compare_vectors(svec, fvec);

    svec.insert(svec.begin(), 10);
    fvec.insert(fvec.begin(), 10);

    svec.insert(svec.end(), 3);
    fvec.insert(fvec.end(), 3);

    svec.insert(svec.begin(), 5);
    fvec.insert(fvec.begin(), 5);

    svec.insert(svec.end(), 6);
    fvec.insert(fvec.end(), 6);

    compare_vectors(svec, fvec);

    svec.insert(svec.begin() + 1, 2, 7);
    fvec.insert(fvec.begin() + 1, 2, 7);

    svec.insert(svec.end() - 3, 3, 1);
    fvec.insert(fvec.end() - 3, 3, 1);

    svec.insert(svec.begin() + 5, 2, 2);
    fvec.insert(fvec.begin() + 5, 2, 2);

    svec.insert(svec.begin(), 0);
    fvec.insert(fvec.begin(), 0);

    svec.insert(svec.end(), 0);
    fvec.insert(fvec.end(), 0);

    compare_vectors(svec, fvec);


    std::vector<int>    sample(3, 4);
    svec.insert(svec.begin(), sample.begin(), sample.end());
    fvec.insert(fvec.begin(), sample.begin(), sample.end());

    sample.assign(5, 9);
    svec.insert(svec.end() - 10, sample.begin(), sample.end());
    fvec.insert(fvec.end() - 10, sample.begin(), sample.end());

    compare_vectors(svec, fvec);

    sample.assign(5, 7);
    svec.insert(svec.end() - 1, sample.begin(), sample.end());
    fvec.insert(fvec.end() - 1, sample.begin(), sample.end());

    svec.insert(svec.begin() + 9, 3, 1);
    fvec.insert(fvec.begin() + 9, 3, 1);

    compare_vectors(svec, fvec);

    svec.insert(svec.end(), 111111);
    fvec.insert(fvec.end(), 111111);

    svec.insert(svec.begin(), 111111);
    fvec.insert(fvec.begin(), 111111);

    svec.insert(svec.end(), 111111);
    fvec.insert(fvec.end(), 111111);

    svec.insert(svec.begin(), 111111);
    fvec.insert(fvec.begin(), 111111);

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);

    std::cout << YELLOW "3) erase:" DEFAULT << std::endl;

    compare_vectors(svec, fvec);

    svec.erase(svec.begin());
    fvec.erase(fvec.begin());

    svec.erase(svec.end() - 1);
    fvec.erase(fvec.end() - 1);

    svec.erase(svec.begin());
    fvec.erase(fvec.begin());

    svec.erase(svec.end() - 1);
    fvec.erase(fvec.end() - 1);

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);

    svec.erase(svec.begin() + 2, svec.begin() + 5);
    fvec.erase(fvec.begin() + 2, fvec.begin() + 5);

    svec.erase(svec.end() - 5, svec.end() - 2);
    fvec.erase(fvec.end() - 5, fvec.end() - 2);

    svec.erase(svec.begin());
    fvec.erase(fvec.begin());

    svec.erase(svec.end() - 1);
    fvec.erase(fvec.end() - 1);

    compare_vectors(svec, fvec);

    svec.erase(svec.begin(), svec.end());
    fvec.erase(fvec.begin(), fvec.end());

    stress_test(svec, fvec);
    compare_vectors(svec, fvec);
}

void    test_vector_push_pop(void)
{
    std::cout << YELLOW "4) push_back:" DEFAULT << std::endl;

    std::vector<int>    svec;
    ft::vector<int>     fvec;

    svec.push_back(11);
    fvec.push_back(11);
    compare_vectors(svec, fvec);

    for (int i = 0; i < 25; i++)
    {
        svec.push_back(i);
        fvec.push_back(i);
    }
    compare_vectors(svec, fvec);

    for (int i = 0; i < 25; i++)
    {
        svec.push_back(i);
        fvec.push_back(i);
    }
    compare_vectors(svec, fvec);

    std::cout << YELLOW "5) pop_back:" DEFAULT << std::endl;

    compare_vectors(svec, fvec);
    svec.pop_back();
    fvec.pop_back();
    compare_vectors(svec, fvec);

    for (int i = 0; i < 25; i++)
    {
        svec.pop_back();
        fvec.pop_back();
    }
    compare_vectors(svec, fvec);

    for (int i = 0; i < 25; i++)
    {
        svec.pop_back();
        fvec.pop_back();
    }
    compare_vectors(svec, fvec);
}

void    test_vector_resize(void)
{
    std::cout << YELLOW "6) resize:" DEFAULT << std::endl;

    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.resize(0);
        fvec.resize(0);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec;
        ft::vector<int>     fvec;

        svec.resize(10);
        fvec.resize(10);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        svec.resize(0);
        fvec.resize(0);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        svec.resize(15, 5);
        fvec.resize(15, 5);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(10);
        ft::vector<int>     fvec(10);

        svec.resize(10, 5);
        fvec.resize(10, 5);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(1, 5);
        ft::vector<int>     fvec(1, 5);

        svec.resize(0);
        fvec.resize(0);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    svec(1, 5);
        ft::vector<int>     fvec(1, 5);

        svec.resize(5, 3);
        fvec.resize(5, 3);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(10, 50);
        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        svec.resize(0);
        fvec.resize(0);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
    {
        std::vector<int>    sample(10, 50);
        std::vector<int>    svec(sample.begin(), sample.end());
        ft::vector<int>     fvec(sample.begin(), sample.end());

        svec.resize(15, 30);
        fvec.resize(15, 30);

        stress_test(svec, fvec);
        compare_vectors(svec, fvec);
    }
}

void    test_vector_swap(void)
{
    std::cout << YELLOW "7) swap:" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    svec1.assign(10, 5);
    fvec1.assign(10, 5);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.swap(svec2);
    fvec1.swap(fvec2);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.assign(2, 3);
    fvec1.assign(2, 3);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.swap(svec2);
    fvec1.swap(fvec2);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.clear();
    fvec1.clear();

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.swap(svec2);
    fvec1.swap(fvec2);

    stress_test(svec1, fvec1);
    stress_test(svec2, fvec2);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
}

void    test_vector_compare_1(void)
{
    std::cout << YELLOW "1) == :" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    svec1.assign(10, 5);
    fvec1.assign(10, 5);

    print_stack(fvec1);
    print_stack(fvec2);
    std::cout << std::boolalpha << (fvec1 == fvec2) << " : ";
    if ((fvec1 == fvec2) == (svec1 == svec2))
        std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
    else
        std::cout << RED "KO" DEFAULT << '\n' << std::endl;

    fvec2 = fvec1;
    svec2 = svec1;

    print_stack(fvec1);
    print_stack(fvec2);
    std::cout << std::boolalpha << (fvec1 == fvec2) << " : ";
    if ((fvec1 == fvec2) == (svec1 == svec2))
        std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
    else
        std::cout << RED "KO" DEFAULT << '\n' << std::endl;
}

void    test_vector_compare_2(void)
{
    std::cout << YELLOW "2) != :" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    {
        svec1.assign(3, 5);
        fvec1.assign(3, 5);

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 != fvec2) << " : ";
        if ((fvec1 != fvec2) == (svec1 != svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec2 = svec1;
        fvec2 = fvec1;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 != fvec2) << " : ";
        if ((fvec1 != fvec2) == (svec1 != svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec2.pop_back();
        fvec2.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 != fvec2) << " : ";
        if ((fvec1 != fvec2) == (svec1 != svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_vector_compare_3(void)
{
    std::cout << YELLOW "3) > :" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    {
        svec1.assign(3, 5);
        fvec1.assign(3, 5);

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 > fvec2) << " : ";
        if ((fvec1 > fvec2) == (svec1 > svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec2 = svec1;
        svec2.pop_back();
        fvec2 = fvec1;
        fvec2.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 > fvec2) << " : ";
        if ((fvec1 > fvec2) == (svec1 > svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1.pop_back();
        fvec1.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 > fvec2) << " : ";
        if ((fvec1 > fvec2) == (svec1 > svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 10;
        svec2[svec2.size() - 1] = 5;
        fvec1[fvec1.size() - 1] = 10;
        fvec2[fvec2.size() - 1] = 5;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 > fvec2) << " : ";
        if ((fvec1 > fvec2) == (svec1 > svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 1;
        svec2[svec2.size() - 1] = 50;
        fvec1[fvec1.size() - 1] = 1;
        fvec2[fvec2.size() - 1] = 50;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 > fvec2) << " : ";
        if ((fvec1 > fvec2) == (svec1 > svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_vector_compare_4(void)
{
    std::cout << YELLOW "4) < :" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    {
        svec1.assign(3, 5);
        fvec1.assign(3, 5);

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 < fvec2) << " : ";
        if ((fvec1 < fvec2) == (svec1 < svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec2 = svec1;
        svec2.pop_back();
        fvec2 = fvec1;
        fvec2.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 < fvec2) << " : ";
        if ((fvec1 < fvec2) == (svec1 < svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1.pop_back();
        fvec1.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 < fvec2) << " : ";
        if ((fvec1 < fvec2) == (svec1 < svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 10;
        svec2[svec2.size() - 1] = 5;
        fvec1[fvec1.size() - 1] = 10;
        fvec2[fvec2.size() - 1] = 5;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 < fvec2) << " : ";
        if ((fvec1 < fvec2) == (svec1 < svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 1;
        svec2[svec2.size() - 1] = 50;
        fvec1[fvec1.size() - 1] = 1;
        fvec2[fvec2.size() - 1] = 50;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 < fvec2) << " : ";
        if ((fvec1 < fvec2) == (svec1 < svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_vector_compare_5(void)
{
    std::cout << YELLOW "5) >= :" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    {
        svec1.assign(3, 5);
        fvec1.assign(3, 5);

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 >= fvec2) << " : ";
        if ((fvec1 >= fvec2) == (svec1 >= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec2 = svec1;
        svec2.pop_back();
        fvec2 = fvec1;
        fvec2.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 >= fvec2) << " : ";
        if ((fvec1 >= fvec2) == (svec1 >= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1.pop_back();
        fvec1.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 >= fvec2) << " : ";
        if ((fvec1 >= fvec2) == (svec1 >= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 10;
        svec2[svec2.size() - 1] = 5;
        fvec1[fvec1.size() - 1] = 10;
        fvec2[fvec2.size() - 1] = 5;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 >= fvec2) << " : ";
        if ((fvec1 >= fvec2) == (svec1 >= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 1;
        svec2[svec2.size() - 1] = 50;
        fvec1[fvec1.size() - 1] = 1;
        fvec2[fvec2.size() - 1] = 50;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 >= fvec2) << " : ";
        if ((fvec1 >= fvec2) == (svec1 >= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_vector_compare_6(void)
{
    std::cout << YELLOW "6) <= :" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    {
        svec1.assign(3, 5);
        fvec1.assign(3, 5);

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 <= fvec2) << " : ";
        if ((fvec1 <= fvec2) == (svec1 <= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec2 = svec1;
        svec2.pop_back();
        fvec2 = fvec1;
        fvec2.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 <= fvec2) << " : ";
        if ((fvec1 <= fvec2) == (svec1 <= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1.pop_back();
        fvec1.pop_back();

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 <= fvec2) << " : ";
        if ((fvec1 <= fvec2) == (svec1 <= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 10;
        svec2[svec2.size() - 1] = 5;
        fvec1[fvec1.size() - 1] = 10;
        fvec2[fvec2.size() - 1] = 5;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 <= fvec2) << " : ";
        if ((fvec1 <= fvec2) == (svec1 <= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        svec1[svec1.size() - 1] = 1;
        svec2[svec2.size() - 1] = 50;
        fvec1[fvec1.size() - 1] = 1;
        fvec2[fvec2.size() - 1] = 50;

        print_stack(fvec1);
        print_stack(fvec2);
        std::cout << std::boolalpha << (fvec1 <= fvec2) << " : ";
        if ((fvec1 <= fvec2) == (svec1 <= svec2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_vector_swap_nn(void)
{
    std::cout << YELLOW "1) swap:" DEFAULT << std::endl;

    std::vector<int>    svec1, svec2;
    ft::vector<int>     fvec1, fvec2;

    svec1.assign(10, 5);
    fvec1.assign(10, 5);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    std::swap(svec1, svec2);
    ft::swap(fvec1, fvec2);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.assign(2, 3);
    fvec1.assign(2, 3);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    std::swap(svec1, svec2);
    ft::swap(fvec1, fvec2);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    svec1.clear();
    fvec1.clear();

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
    std::cout << "----------" << std::endl;

    std::swap(svec1, svec2);
    ft::swap(fvec1, fvec2);

    stress_test(svec1, fvec1);
    stress_test(svec2, fvec2);

    compare_vectors(svec1, fvec1);
    compare_vectors(svec2, fvec2);
}

void    ft_vector_tests()
{
    std::cout << B_RED "[   FT_VECTOR   ]" DEFAULT << '\n' << std::endl;
    std::cout << B_CYAN "   Constructors   " DEFAULT << std::endl;
    test_vector_constructor_1_1();
    test_vector_constructor_1_2();

    test_vector_constructor_2_1();
    test_vector_constructor_2_2();

    test_vector_constructor_3_1();
    test_vector_constructor_3_2();
    test_vector_constructor_3_3();
    test_vector_constructor_3_4();

    test_vector_constructor_4_1();
    test_vector_constructor_4_2();
    test_vector_constructor_4_3();
    test_vector_constructor_4_4();

    test_vector_constructor_5_1();
    test_vector_constructor_5_2();
    test_vector_constructor_5_3();
    test_vector_constructor_5_4();

    std::cout << B_CYAN "   Assignments   " DEFAULT << std::endl;
    test_vector_assignment_1_1();
    test_vector_assignment_1_2();

    test_vector_assignment_2_1();
    test_vector_assignment_2_2();

    test_vector_assignment_3_1();
    test_vector_assignment_3_2();

    std::cout << B_CYAN "   Get allocator   " DEFAULT << std::endl;
    test_vector_get_allocator();

    std::cout << B_CYAN "   Element access   " DEFAULT << std::endl;
    test_vector_access_1_1();
    test_vector_access_1_2();
    test_vector_access_2();
    test_vector_access_3();
    test_vector_access_4();
    test_vector_access_5();

    std::cout << B_CYAN "   Iterators   " DEFAULT << std::endl;
    test_vector_iterators_1_1();
    test_vector_iterators_1_2();
    test_vector_iterators_2_1();
    test_vector_iterators_2_2();
    test_vector_iterators_3();

    std::cout << B_CYAN "   Reverse iterators   " DEFAULT << std::endl;
    test_vector_rev_iterators_1_1();
    test_vector_rev_iterators_1_2();
    test_vector_rev_iterators_2_1();
    test_vector_rev_iterators_2_2();
    test_vector_rev_iterators_3();

    std::cout << B_CYAN "   Capacity   " DEFAULT << std::endl;
    test_vector_capacity_1();
    test_vector_capacity_2();
    test_vector_capacity_3();
    test_vector_capacity_4();

    std::cout << B_CYAN "   Modifiers   " DEFAULT << std::endl;
    test_vector_clear();
    test_vector_insert_erase();
    test_vector_push_pop();
    test_vector_resize();
    test_vector_swap();

    std::cout << B_CYAN "   Non-member/compares   " DEFAULT << std::endl;
    test_vector_compare_1();
    test_vector_compare_2();
    test_vector_compare_3();
    test_vector_compare_4();
    test_vector_compare_5();
    test_vector_compare_6();

    std::cout << B_CYAN "   Non-member/swap   " DEFAULT << std::endl;
    test_vector_swap_nn();
}
