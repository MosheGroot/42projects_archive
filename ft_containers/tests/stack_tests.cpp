#include <iostream>
#include <deque>
#include <stack>
#include "../ft_stack.hpp"
#include "tests.hpp"

# define STRESS_PUSH    5
# define STRESS_POP     5

void    stress_test(std::stack<int>& lhs, ft::stack<int>& rhs)
{
    for (int i = 0; i < STRESS_PUSH; i++)
        { lhs.push(i); rhs.push(i); }

    for (int i = 0; i < STRESS_POP; i++)
        { lhs.pop(); rhs.pop(); }
}

void    stress_test(std::stack<int, std::deque<int> >& lhs,
                    ft::stack<int, std::deque<int> >& rhs)
{
    for (int i = 0; i < STRESS_PUSH; i++)
        { lhs.push(i); rhs.push(i); }

    for (int i = 0; i < STRESS_POP; i++)
        { lhs.pop(); rhs.pop(); }
}

template< class T>
void    print_stack(T stack)
{
    std::cout << "[ ";
    while (stack.size())
    {
        std::cout << stack.top() << ' ';
        stack.pop();
    }
    std::cout << "]" << std::endl;
}

void    compare_stacks(const std::stack<int>& lhs, const ft::stack<int>& rhs)
{
    print_stack(lhs);
    print_stack(rhs);

    std::stack<int> stmp = lhs;
    ft::stack<int> ftmp = rhs;
    while (stmp.size() && ftmp.size())
    {
        if (stmp.top() != ftmp.top())
        {
            std::cout << RED "KO" DEFAULT << std::endl;
            return;
        }
        stmp.pop();
        ftmp.pop();
    }
    if (stmp.size() || ftmp.size())
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
    if (lhs.size() && lhs.top() != rhs.top())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    std::cout << '\n' << std::endl;
}

void    compare_stacks( const std::stack<int, std::deque<int> >& lhs,
                        const ft::stack<int, std::deque<int> >& rhs)
{
    print_stack(lhs);
    print_stack(rhs);

    std::stack<int, std::deque<int> > stmp = lhs;
    ft::stack<int, std::deque<int> > ftmp = rhs;
    while (stmp.size() && ftmp.size())
    {
        if (stmp.top() != ftmp.top())
        {
            std::cout << RED "KO" DEFAULT << std::endl;
            return;
        }
        stmp.pop();
        ftmp.pop();
    }
    if (stmp.size() || ftmp.size())
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
    if (lhs.size() && lhs.top() != rhs.top())
        std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    else
        std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;

    std::cout << '\n' << std::endl;
}

void    test_stack_constructor_1_1(void)
{
    std::cout << YELLOW "1.1) Default constructor:" DEFAULT << std::endl;
    std::stack<int>    sstack;
    ft::stack<int>     fstack;

    compare_stacks(sstack, fstack);
}

void    test_stack_constructor_1_2(void)
{
    std::cout << YELLOW "1.2) Default constructor [+ push + pop]:" DEFAULT << std::endl;
    std::stack<int>    sstack;
    ft::stack<int>     fstack;

    stress_test(sstack, fstack);
    compare_stacks(sstack, fstack);
}

void    test_stack_constructor_2_1(void)
{
    std::cout << YELLOW "2.1) Copy constructor [empty]:" DEFAULT << std::endl;

    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        std::stack<int>    sstack(ssample);
        ft::stack<int>     fstack(fsample);

        compare_stacks(sstack, fstack);
    }
}

void    test_stack_constructor_2_2(void)
{
    std::cout << YELLOW "2.2) Copy constructor [empty + push + pop]:" DEFAULT << std::endl;

    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        std::stack<int>    sstack(ssample);
        ft::stack<int>     fstack(fsample);

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
}

void    test_stack_constructor_2_3(void)
{
    std::cout << YELLOW "2.3) Copy constructor [non-empty]:" DEFAULT << std::endl;

    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        ssample.push(5);
        fsample.push(5);

        ssample.push(15);
        fsample.push(15);

        ssample.push(-5);
        fsample.push(-5);

        std::stack<int>    sstack(ssample);
        ft::stack<int>     fstack(fsample);

        compare_stacks(sstack, fstack);
    }
}

void    test_stack_constructor_2_4(void)
{
    std::cout << YELLOW "2.4) Copy constructor [+ non-empty + push + pop]:" DEFAULT << std::endl;

    {
        std::stack<int, std::deque<int> >    ssample;
        ft::stack<int, std::deque<int> >     fsample;

        ssample.push(5);
        fsample.push(5);

        ssample.push(15);
        fsample.push(15);

        ssample.push(-5);
        fsample.push(-5);

        std::stack<int, std::deque<int> >    sstack(ssample);
        ft::stack<int, std::deque<int> >     fstack(fsample);

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
}

void    test_stack_assignment_1(void)
{
    std::cout << YELLOW "1) operator= [to empty]:" DEFAULT << std::endl;

    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack = ssample;
        fstack = fsample;

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        ssample.push(5);
        fsample.push(5);

        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack = ssample;
        fstack = fsample;

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        ssample.push(5);
        fsample.push(5);

        ssample.push(15);
        fsample.push(15);

        ssample.push(-5);
        fsample.push(-5);

        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack = ssample;
        fstack = fsample;

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
}

void    test_stack_assignment_2(void)
{
    std::cout << YELLOW "2) operator= [to non-empty]:" DEFAULT << std::endl;

    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack.push(100);
        fstack.push(100);

        sstack.push(1000);
        fstack.push(1000);

        sstack = ssample;
        fstack = fsample;

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        ssample.push(5);
        fsample.push(5);

        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack.push(100);
        fstack.push(100);

        sstack.push(1000);
        fstack.push(1000);

        sstack = ssample;
        fstack = fsample;

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
    {
        std::stack<int>    ssample;
        ft::stack<int>     fsample;

        ssample.push(5);
        fsample.push(5);

        ssample.push(15);
        fsample.push(15);

        ssample.push(-5);
        fsample.push(-5);

        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack.push(100);
        fstack.push(100);

        sstack.push(1000);
        fstack.push(1000);

        sstack = ssample;
        fstack = fsample;

        stress_test(sstack, fstack);
        compare_stacks(sstack, fstack);
    }
}

void    test_stack_access(void)
{
    std::cout << YELLOW "3) top [non-empty]:" DEFAULT << std::endl;

    std::stack<int>    sstack;
    ft::stack<int>     fstack;
    sstack.push(100);
    fstack.push(100);

    sstack.push(1000);
    fstack.push(1000);

    {
        std::stack<int>    const_sstack(sstack);
        ft::stack<int>     const_fstack(fstack);

        if (const_sstack.top() != const_fstack.top())
        {
            std::cout << "const ref:\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
        std::cout << "const ref:\t" << GREEN "OK" DEFAULT << std::endl;
    }
    {
        sstack.top() = 7;
        fstack.top() = 7;
        if (sstack.top() != fstack.top())
        {
            std::cout << "ref:\t\t" << RED "KO" DEFAULT << std::flush;
            return;
        }
        std::cout << "ref:\t\t" << GREEN "OK" DEFAULT << std::endl;
    }
    compare_stacks(sstack, fstack);
}

void    test_stack_capacity_1(void)
{
    std::cout << YELLOW "1) Empty:" DEFAULT << std::endl;

    {
        std::stack<int, std::deque<int> >    sstack;
        ft::stack<int, std::deque<int> >     fstack;

        if (sstack.empty() == fstack.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::stack<int>    sstack;
        ft::stack<int>     fstack;
        sstack.push(100);
        fstack.push(100);

        if (sstack.empty() == fstack.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack.push(100);
        fstack.push(100);

        sstack.push(1000);
        fstack.push(1000);

        if (sstack.empty() == fstack.empty())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
}

void    test_stack_capacity_2(void)
{
    std::cout << YELLOW "2) Size:" DEFAULT << std::endl;

    {
        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        if (sstack.size() == fstack.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::stack<int>    sstack;
        ft::stack<int>     fstack;
        sstack.push(100);
        fstack.push(100);

        if (sstack.size() == fstack.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::stack<int>    sstack;
        ft::stack<int>     fstack;

        sstack.push(100);
        fstack.push(100);

        sstack.push(1000);
        fstack.push(1000);

        if (sstack.size() == fstack.size())
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    std::cout << '\n' << std::endl;
    std::cout << '\n' << std::endl;
}

void    test_stack_push_pop(void)
{
    std::cout << YELLOW "4) push:" DEFAULT << std::endl;

    std::stack<int, std::deque<int> >    sstack;
    ft::stack<int, std::deque<int> >     fstack;

    sstack.push(11);
    fstack.push(11);
    compare_stacks(sstack, fstack);

    for (int i = 0; i < 25; i++)
    {
        sstack.push(i);
        fstack.push(i);
    }
    compare_stacks(sstack, fstack);

    for (int i = 0; i < 25; i++)
    {
        sstack.push(i);
        fstack.push(i);
    }
    compare_stacks(sstack, fstack);

    std::cout << YELLOW "5) pop:" DEFAULT << std::endl;

    compare_stacks(sstack, fstack);
    sstack.pop();
    fstack.pop();
    compare_stacks(sstack, fstack);

    for (int i = 0; i < 25; i++)
    {
        sstack.pop();
        fstack.pop();
    }
    compare_stacks(sstack, fstack);

    for (int i = 0; i < 25; i++)
    {
        sstack.pop();
        fstack.pop();
    }
    compare_stacks(sstack, fstack);
}

void    test_stack_compare_1(void)
{
    std::cout << YELLOW "1) == :" DEFAULT << std::endl;

    std::stack<int>    sstack1, sstack2;
    ft::stack<int>     fstack1, fstack2;

    sstack1.push(100);
    fstack1.push(100);

    sstack1.push(1000);
    fstack1.push(1000);

    print_stack(fstack1);
    print_stack(fstack2);
    std::cout << std::boolalpha << (fstack1 == fstack2) << " : ";
    if ((fstack1 == fstack2) == (sstack1 == sstack2))
        std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
    else
        std::cout << RED "KO" DEFAULT << '\n' << std::endl;

    fstack2 = fstack1;
    sstack2 = sstack1;

    print_stack(fstack1);
    print_stack(fstack2);
    std::cout << std::boolalpha << (fstack1 == fstack2) << " : ";
    if ((fstack1 == fstack2) == (sstack1 == sstack2))
        std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
    else
        std::cout << RED "KO" DEFAULT << '\n' << std::endl;
}

void    test_stack_compare_2(void)
{
    std::cout << YELLOW "2) != :" DEFAULT << std::endl;

    std::stack<int>    sstack1, sstack2;
    ft::stack<int>     fstack1, fstack2;

    {
        sstack1.push(100);
        fstack1.push(100);

        sstack1.push(1000);
        fstack1.push(1000);

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 != fstack2) << " : ";
        if ((fstack1 != fstack2) == (sstack1 != sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack2 = sstack1;
        fstack2 = fstack1;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 != fstack2) << " : ";
        if ((fstack1 != fstack2) == (sstack1 != sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack2.pop();
        fstack2.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 != fstack2) << " : ";
        if ((fstack1 != fstack2) == (sstack1 != sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_stack_compare_3(void)
{
    std::cout << YELLOW "3) > :" DEFAULT << std::endl;

    std::stack<int>    sstack1, sstack2;
    ft::stack<int>     fstack1, fstack2;

    {
        sstack1.push(100);
        fstack1.push(100);

        sstack1.push(1000);
        fstack1.push(1000);

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 > fstack2) << " : ";
        if ((fstack1 > fstack2) == (sstack1 > sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack2 = sstack1;
        sstack2.pop();
        fstack2 = fstack1;
        fstack2.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 > fstack2) << " : ";
        if ((fstack1 > fstack2) == (sstack1 > sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.pop();
        fstack1.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 > fstack2) << " : ";
        if ((fstack1 > fstack2) == (sstack1 > sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 10;
        sstack2.top() = 5;
        fstack1.top() = 10;
        fstack2.top() = 5;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 > fstack2) << " : ";
        if ((fstack1 > fstack2) == (sstack1 > sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 1;
        sstack2.top() = 50;
        fstack1.top() = 1;
        fstack2.top() = 50;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 > fstack2) << " : ";
        if ((fstack1 > fstack2) == (sstack1 > sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_stack_compare_4(void)
{
    std::cout << YELLOW "4) < :" DEFAULT << std::endl;

    std::stack<int>    sstack1, sstack2;
    ft::stack<int>     fstack1, fstack2;

    {
        sstack1.push(100);
        fstack1.push(100);

        sstack1.push(1000);
        fstack1.push(1000);

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 < fstack2) << " : ";
        if ((fstack1 < fstack2) == (sstack1 < sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack2 = sstack1;
        sstack2.pop();
        fstack2 = fstack1;
        fstack2.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 < fstack2) << " : ";
        if ((fstack1 < fstack2) == (sstack1 < sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.pop();
        fstack1.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 < fstack2) << " : ";
        if ((fstack1 < fstack2) == (sstack1 < sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 10;
        sstack2.top() = 5;
        fstack1.top() = 10;
        fstack2.top() = 5;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 < fstack2) << " : ";
        if ((fstack1 < fstack2) == (sstack1 < sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 1;
        sstack2.top() = 50;
        fstack1.top() = 1;
        fstack2.top() = 50;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 < fstack2) << " : ";
        if ((fstack1 < fstack2) == (sstack1 < sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_stack_compare_5(void)
{
    std::cout << YELLOW "5) >= :" DEFAULT << std::endl;

    std::stack<int>    sstack1, sstack2;
    ft::stack<int>     fstack1, fstack2;

    {
        sstack1.push(100);
        fstack1.push(100);

        sstack1.push(1000);
        fstack1.push(1000);

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 >= fstack2) << " : ";
        if ((fstack1 >= fstack2) == (sstack1 >= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack2 = sstack1;
        sstack2.pop();
        fstack2 = fstack1;
        fstack2.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 >= fstack2) << " : ";
        if ((fstack1 >= fstack2) == (sstack1 >= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.pop();
        fstack1.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 >= fstack2) << " : ";
        if ((fstack1 >= fstack2) == (sstack1 >= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 10;
        sstack2.top() = 5;
        fstack1.top() = 10;
        fstack2.top() = 5;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 >= fstack2) << " : ";
        if ((fstack1 >= fstack2) == (sstack1 >= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 1;
        sstack2.top() = 50;
        fstack1.top() = 1;
        fstack2.top() = 50;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 >= fstack2) << " : ";
        if ((fstack1 >= fstack2) == (sstack1 >= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    test_stack_compare_6(void)
{
    std::cout << YELLOW "6) <= :" DEFAULT << std::endl;

    std::stack<int, std::deque<int> >    sstack1, sstack2;
    ft::stack<int, std::deque<int> >     fstack1, fstack2;

    {
        sstack1.push(100);
        fstack1.push(100);

        sstack1.push(1000);
        fstack1.push(1000);

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 <= fstack2) << " : ";
        if ((fstack1 <= fstack2) == (sstack1 <= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack2 = sstack1;
        sstack2.pop();
        fstack2 = fstack1;
        fstack2.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 <= fstack2) << " : ";
        if ((fstack1 <= fstack2) == (sstack1 <= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.pop();
        fstack1.pop();

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 <= fstack2) << " : ";
        if ((fstack1 <= fstack2) == (sstack1 <= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 10;
        sstack2.top() = 5;
        fstack1.top() = 10;
        fstack2.top() = 5;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 <= fstack2) << " : ";
        if ((fstack1 <= fstack2) == (sstack1 <= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
    {
        sstack1.top() = 1;
        sstack2.top() = 50;
        fstack1.top() = 1;
        fstack2.top() = 50;

        print_stack(fstack1);
        print_stack(fstack2);
        std::cout << std::boolalpha << (fstack1 <= fstack2) << " : ";
        if ((fstack1 <= fstack2) == (sstack1 <= sstack2))
            std::cout << GREEN "OK" DEFAULT << '\n' << std::endl;
        else
            std::cout << RED "KO" DEFAULT << '\n' << std::endl;
    }
}

void    ft_stack_tests()
{
    std::cout << B_RED "[   FT_STACK   ]" DEFAULT << std::endl;
    std::cout << GREEN "Info: output of stack is in order \'from top to bottom'   " DEFAULT << '\n' << std::endl;

    std::cout << B_CYAN "   Constructors   " DEFAULT << std::endl;
    test_stack_constructor_1_1();
    test_stack_constructor_1_2();

    test_stack_constructor_2_1();
    test_stack_constructor_2_2();

    std::cout << B_CYAN "   Assignments   " DEFAULT << std::endl;
    test_stack_assignment_1();
    test_stack_assignment_2();

    std::cout << B_CYAN "   Element access   " DEFAULT << std::endl;
    test_stack_access();

    std::cout << B_CYAN "   Capacity   " DEFAULT << std::endl;
    test_stack_capacity_1();
    test_stack_capacity_2();

    std::cout << B_CYAN "   Modifiers   " DEFAULT << std::endl;
    test_stack_push_pop();

    std::cout << B_CYAN "   Non-member/compares   " DEFAULT << std::endl;
    test_stack_compare_1();
    test_stack_compare_2();
    test_stack_compare_3();
    test_stack_compare_4();
    test_stack_compare_5();
    test_stack_compare_6();
}
