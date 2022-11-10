// auto func(int i) -> int;
#include <iostream>
#include <string>
int a[10] = {0};
int (*b)[10] = &a;
auto func(int i) -> int (*&)[10]
{
    return b;
}

inline auto func1(int j) -> int (*&)[10]
{
    std::cerr << __FILE__ << std::endl;
    std::cerr << __func__ << std::endl;
    std::cerr << __LINE__ << std::endl;
    std::cerr << __TIME__ << std::endl;
    return b;
}
bool lengthcompare(const std::string &, const std::string &);
typedef bool Func(const std::string &, const std::string &);
typedef decltype(lengthcompare) Func2;
typedef bool (*FuncP)(const std::string &, const std::string &);
typedef decltype(lengthcompare) *FuncP2;

// auto lengthcompare_sample(const std::string &, const std::string &) -> bool
// {
//     return true;
// }

auto lengthcompare_sample1 (FuncP2 P1,  Func2 P2) -> bool {
    return true;
}

auto lengthcompare_sample2 (FuncP2 P1,  Func2 P2) -> FuncP2 {
    return P1;
}

auto lengthcompare_sample3 (FuncP2 P1,  Func2 P2) -> int(*)(int *, int);

