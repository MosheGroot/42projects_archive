#include <utility>
#include "../data_structs/ft_pair.hpp"
#include "tests.hpp"

template<class T1, class T2>
bool    operator==(const std::pair<T1, T2>& sp, const ft::pair<T1,T2>& fp)
{
    return ((sp.first == fp.first) && (sp.second == fp.second));
}

template<class T1, class T2>
bool    operator==(const ft::pair<T1, T2>& sp, const std::pair<T1,T2>& fp)
{
    return ((sp.first == fp.first) && (sp.second == fp.second));
}

template<class T1, class T2>
std::ostream&   operator<<(std::ostream& os, const std::pair<T1, T2>& sp)
{
    os << "< " << sp.first << " , " << sp.second << " >";
    return os;
}

template<class T1, class T2>
std::ostream&   operator<<(std::ostream& os, const ft::pair<T1, T2>& fp)
{
    os << "< " << fp.first << " , " << fp.second << " >";
    return os;
}

template<class T1, class T2>
void    compare_pairs(const std::pair<T1, T2>& sp, const ft::pair<T1,T2>& fp)
{
    std::cout << sp << std::endl;
    std::cout << fp << std::endl;

    if (sp == fp)
        std::cout << GREEN "OK" DEFAULT << '\n';
    else
        std::cout << RED "KO" DEFAULT << '\n';
    std::cout << std::endl;
}

void    test_pair_constructor_1(void)
{
    std::cout << YELLOW "1) Default constructor:" DEFAULT << std::endl;

    std::pair<char, int>    sp;
    ft::pair<char, int>     fp;

    compare_pairs(sp, fp);
}

void    test_pair_constructor_2(void)
{
    std::cout << YELLOW "2) 2 params constructor:" DEFAULT << std::endl;

    std::pair<char, int>    sp('a', 134);
    ft::pair<char, int>     fp('a', 134);

    compare_pairs(sp, fp);
}

void    test_pair_constructor_3(void)
{
    std::cout << YELLOW "3) Copy constructor:" DEFAULT << std::endl;
    
    std::pair<char, char>   ssample('b','b');
    ft::pair<char, char>    fsample('b','b');

    std::pair<char, int>    sp(ssample);
    ft::pair<char, int>     fp(fsample);

    compare_pairs(sp, fp);
}

void    test_pair_assignment(void)
{
    std::cout << YELLOW "1) Assignment operator:" DEFAULT << std::endl;
    
    std::pair<char, int>   ssample('b',123);
    ft::pair<char, int>    fsample('b',123);

    std::pair<char, int>    sp;
    ft::pair<char, int>     fp;

    sp = ssample;
    fp = fsample;

    compare_pairs(sp, fp);
}

void    test_make_pair(void)
{
    std::cout << YELLOW "1) make_pair:" DEFAULT << std::endl;
    
    std::pair<char, int>    sp = std::make_pair('A', -12);
    ft::pair<char, int>     fp = ft::make_pair('A', -12);
    
    compare_pairs(sp, fp);
}

void    test_pair_compare_1(void)
{
    std::cout << YELLOW "1) == :" DEFAULT << std::endl;
    
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = sp1;
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = fp1;
        
        if ((sp1 == sp2) == (fp1 == fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('B', -12);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('B', -12);
        
        if ((sp1 == sp2) == (fp1 == fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('A', -13);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('A', -13);
        
        if ((sp1 == sp2) == (fp1 == fp2))
            std::cout << GREEN "OK" DEFAULT << '\n';
        else
            std::cout << RED "KO" DEFAULT << '\n';
    }
    std::cout << std::endl;
}

void    test_pair_compare_2(void)
{
    std::cout << YELLOW "2) != :" DEFAULT << std::endl;
    
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = sp1;
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = fp1;
        
        if ((sp1 != sp2) == (fp1 != fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('B', -12);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('B', -12);
        
        if ((sp1 != sp2) == (fp1 != fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('A', -13);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('A', -13);
        
        if ((sp1 != sp2) == (fp1 != fp2))
            std::cout << GREEN "OK" DEFAULT << '\n';
        else
            std::cout << RED "KO" DEFAULT << '\n';
    }
    std::cout << std::endl;
}

void    test_pair_compare_3(void)
{
    std::cout << YELLOW "3) > :" DEFAULT << std::endl;
    
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = sp1;
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = fp1;
        
        if ((sp1 > sp2) == (fp1 > fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('B', -12);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('B', -12);
        
        if ((sp1 > sp2) == (fp1 > fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('A', -13);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('A', -13);
        
        if ((sp1 > sp2) == (fp1 > fp2))
            std::cout << GREEN "OK" DEFAULT << '\n';
        else
            std::cout << RED "KO" DEFAULT << '\n';
    }
    std::cout << std::endl;
}

void    test_pair_compare_4(void)
{
    std::cout << YELLOW "4) <= :" DEFAULT << std::endl;
    
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = sp1;
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = fp1;
        
        if ((sp1 <= sp2) == (fp1 <= fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('B', -12);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('B', -12);
        
        if ((sp1 <= sp2) == (fp1 <= fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('A', -13);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('A', -13);
        
        if ((sp1 <= sp2) == (fp1 <= fp2))
            std::cout << GREEN "OK" DEFAULT << '\n';
        else
            std::cout << RED "KO" DEFAULT << '\n';
    }
    std::cout << std::endl;
}

void    test_pair_compare_5(void)
{
    std::cout << YELLOW "5) < :" DEFAULT << std::endl;
    
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = sp1;
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = fp1;
        
        if ((sp1 < sp2) == (fp1 < fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('B', -12);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('B', -12);
        
        if ((sp1 < sp2) == (fp1 < fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('A', -13);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('A', -13);
        
        if ((sp1 < sp2) == (fp1 < fp2))
            std::cout << GREEN "OK" DEFAULT << '\n';
        else
            std::cout << RED "KO" DEFAULT << '\n';
    }
    std::cout << std::endl;
}

void    test_pair_compare_6(void)
{
    std::cout << YELLOW "6) >= :" DEFAULT << std::endl;
    
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = sp1;
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = fp1;
        
        if ((sp1 >= sp2) == (fp1 >= fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('B', -12);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('B', -12);
        
        if ((sp1 >= sp2) == (fp1 >= fp2))
            std::cout << GREEN "OK" DEFAULT << ' ' << std::flush;
        else
            std::cout << RED "KO" DEFAULT << ' ' << std::flush;
    }
    {
        std::pair<char, int>    sp1 = std::make_pair('A', -12);
        std::pair<char, int>    sp2 = std::make_pair('A', -13);
        ft::pair<char, int>     fp1 = ft::make_pair('A', -12);
        ft::pair<char, int>     fp2 = ft::make_pair('A', -13);
        
        if ((sp1 >= sp2) == (fp1 >= fp2))
            std::cout << GREEN "OK" DEFAULT << '\n';
        else
            std::cout << RED "KO" DEFAULT << '\n';
    }
    std::cout << std::endl;
}

void    ft_pair_tests(void)
{
    std::cout << B_RED "[   FT_PAIR   ]" DEFAULT << '\n' << std::endl;
    std::cout << B_CYAN "   Constructors   " DEFAULT << std::endl;
    test_pair_constructor_1();
    test_pair_constructor_2();
    test_pair_constructor_3();

    std::cout << B_CYAN "   Assignment   " DEFAULT << std::endl;
    test_pair_assignment();

    std::cout << B_CYAN "   Make_pair   " DEFAULT << std::endl;
    test_make_pair();

    std::cout << B_CYAN "   compares   " DEFAULT << std::endl;
    test_pair_compare_1();
    test_pair_compare_2();
    test_pair_compare_3();
    test_pair_compare_4();
    test_pair_compare_5();
    test_pair_compare_6();
}