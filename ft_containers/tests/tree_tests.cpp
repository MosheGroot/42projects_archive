#include "../data_structs/ft_rb_tree.hpp"
#include "tests.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>

template<class T>
void    print_tree(const T& tree)
{
    ft::less<typename T::value_type> cmp;

    std::cout << "[ ";
    for (typename T::const_iterator i = tree.begin(); i != tree.end(); i++)
        std::cout << *i << ' ';
    std::cout << "] " << std::endl;
}

void    test_tree_constructor_1(void)
{
    std::cout << YELLOW "1) Default constructor:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m;

    m.push(1);
    m.push(2);
    m.push(3);
    m.erase(1);
    m.erase(2);
    m.erase(3);

    print_tree(m);

    if (m.size() == 0)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';
    std::cout << "| " << GREEN "OK" DEFAULT << '\n' << std::endl;
}

void    test_tree_constructor_2(void)
{
    std::cout << YELLOW "2) Copy constructor:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m1;
    m1.push(1);
    m1.push(2);
    m1.push(3);

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m2 = m1;
    m1.erase(1);
    m1.erase(2);
    m1.erase(3);

    std::cout << "(empty->)     ";
    print_tree(m1);
    std::cout << "(not empty->) ";
    print_tree(m2);
    if (m1.size() == 0)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';

    if (m2.size() == 3)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';

    std::cout << "| " << GREEN "OK" DEFAULT << '\n' << std::endl;
}

void    test_tree_assignment_1(void)
{
    std::cout << YELLOW "1) Assignment [empty]:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m1;
    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m2;
    m2 = m1;

    std::cout << "(empty->) ";
    print_tree(m1);
    std::cout << "(empty->) ";
    print_tree(m2);
    if (m1.size() == 0)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';

    if (m2.size() == 0)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';

    std::cout << "| " << GREEN "OK" DEFAULT << '\n' << std::endl;
}

void    test_tree_assignment_2(void)
{
    std::cout << YELLOW "2) Assignment [non-empty]:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m1;
    m1.push(1);
    m1.push(2);
    m1.push(3);
    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m2;
    m2 = m1;
    m1.erase(1);
    m1.erase(2);
    m1.erase(3);

    std::cout << "(empty->)     ";
    print_tree(m1);
    std::cout << "(not empty->) ";
    print_tree(m2);
    if (m1.size() == 0)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';

    if (m2.size() == 3)
        std::cout << GREEN "OK" DEFAULT << ' ';
    else
        std::cout << RED "KO" DEFAULT << ' ';

    std::cout << "| " << GREEN "OK" DEFAULT << '\n' << std::endl;
}

void    test_tree_stress_test(void)
{
    std::cout << YELLOW "1) Stress-test:" DEFAULT << std::endl;

    const size_t    tests_number = 10;
    const size_t    values_number = 25;
    const int       mod = values_number * values_number;

    std::srand(std::time(0));
    for (size_t i = 0; i < tests_number; i++)
    {
        std::vector<int>   values;
        int                tmp;

        ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m;
        for (size_t i = 0; i < values_number; i++)
        {
            tmp = std::rand() % mod;
            m.push(tmp);
            values.push_back(tmp);
        }
        std::cout << "pushing order : { ";
        for (std::vector<int>::iterator i = values.begin(); i != values.end(); i++)
            std::cout << *i << ' ';
        std::cout << "}\n";

        std::cout << "after push:  ";
        print_tree(m);

        for (std::vector<int>::iterator i = values.begin(); i != values.end(); i++)
            m.erase(*i);

        std::cout << "after erase: ";
        print_tree(m);

        if (m.size() == 0)
            std::cout << GREEN "OK" DEFAULT << std::endl;
        else
            std::cout << RED "KO" DEFAULT << std::endl;
    }
    std::cout << '\n';
}

void    test_tree_sandbox1(void)
{
    std::cout << YELLOW "1) Sandbox:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m;

    m.push(3);
    m.push(2);
    m.push(1);
    m.push(0);

    print_tree(m);

    m.erase(3);
    m.erase(2);
    m.erase(1);
    m.erase(0);

    print_tree(m);

    if (m.size() == 0)
        std::cout << GREEN "OK" DEFAULT << std::endl;
    else
        std::cout << RED "KO" DEFAULT << std::endl;
    std::cout << '\n';
}

void    test_tree_sandbox2(void)
{
    std::cout << YELLOW "2) Sandbox:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m;

    m.push(1);
    m.push(2);
    m.push(3);
    m.push(4);
    m.push(5);
    m.push(6);
    m.push(7);
    m.push(8);
    m.push(0);
    m.push(0);

    print_tree(m);
#if _FT_RB_TREE_DEBUG
    std::cout << '\n' << m;
#endif
    std::cout << '\n';

    m.erase(1);
    m.erase(2);
    m.erase(3);
    m.erase(4);
    m.erase(5);

    std::cout << "Erase 1 2 3 4 5\n";
#if _FT_RB_TREE_DEBUG
    std::cout <<  '\n' << m;
#endif
    m.erase(6);
    m.erase(7);
    m.erase(8);
    m.erase(0);
    std::cout << "Erase 6 7 8 0\n";

    print_tree(m);
#if _FT_RB_TREE_DEBUG
    std::cout << m;
#endif
    std::cout << '\n';

    if (m.size() == 0)
        std::cout << GREEN "OK" DEFAULT << std::endl;
    else
        std::cout << RED "KO" DEFAULT << std::endl;
    std::cout << '\n';
}

void    test_tree_sandbox3(void)
{
    std::cout << YELLOW "3) Sandbox:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m;

    m.push(1);
    m.push(2);
    m.push(3);
    m.push(4);
    m.push(5);
    m.push(-1);
    m.push(-2);
    m.push(-3);
    m.push(-10);
    m.push(-11);
    m.push(-12);
    m.push(-6);
    m.push(-7);
    m.push(-8);

    print_tree(m);
#if _FT_RB_TREE_DEBUG
    std::cout << '\n' << m;
#endif
    std::cout << '\n';

    m.erase(1);
    m.erase(2);
    m.erase(3);
    m.erase(4);
    m.erase(5);

    std::cout << "Erase 1 2 3 4 5\n";
#if _FT_RB_TREE_DEBUG
    std::cout <<  '\n' << m;
#endif
    
    m.erase(-10);
    m.erase(-3);
    m.erase(-11);
    m.erase(-6);
    m.erase(-12);
    m.erase(-8);
    std::cout << "Erase -10 -3 -11 -6 -12 -8 \n";
#if _FT_RB_TREE_DEBUG
    std::cout <<  '\n' << m;
#endif

    m.erase(-1);
    m.erase(-2);
    m.erase(-12);
    m.erase(-7);
    std::cout << "Erase -1 -2 -12 -7 \n";
#if _FT_RB_TREE_DEBUG
    std::cout <<  '\n' << m;
#endif

    print_tree(m);
#if _FT_RB_TREE_DEBUG
    std::cout << m;
#endif
    std::cout << '\n';

    if (m.size() == 0)
        std::cout << GREEN "OK" DEFAULT << std::endl;
    else
        std::cout << RED "KO" DEFAULT << std::endl;
    std::cout << '\n';
}

void    test_tree_sandbox4(void)
{
    std::cout << YELLOW "4) Sandbox:" DEFAULT << std::endl;

    ft::_RB_tree<int, ft::less<int>, std::allocator<int> >   m;

    m.push(0);
    m.push(-100);
    m.push(-99);


    print_tree(m);
#if _FT_RB_TREE_DEBUG
    std::cout << '\n' << m;
#endif
    std::cout << '\n';

    m.erase(-100);
    m.erase(-99);
    m.erase(0);

    print_tree(m);
#if _FT_RB_TREE_DEBUG
    std::cout << m;
#endif
    std::cout << '\n';

    if (m.size() == 0)
        std::cout << GREEN "OK" DEFAULT << std::endl;
    else
        std::cout << RED "KO" DEFAULT << std::endl;
    std::cout << '\n';
}

void    ft_tree_tests(void)
{
    std::cout << B_RED "[   FT_RB_TREE   ]" DEFAULT << '\n' << std::endl;
    std::cout << B_CYAN "   Constructors   " DEFAULT << std::endl;
    test_tree_constructor_1();
    test_tree_constructor_2();
    
    std::cout << B_CYAN "   Assignment   " DEFAULT << std::endl;
    test_tree_assignment_1();
    test_tree_assignment_2();
    
    std::cout << B_CYAN "   Push and erase   " DEFAULT << std::endl;
    test_tree_stress_test();

    std::cout << B_CYAN "   Sandbox   " DEFAULT << std::endl;
    test_tree_sandbox1();
    test_tree_sandbox2();
    test_tree_sandbox3();
    test_tree_sandbox4();

}