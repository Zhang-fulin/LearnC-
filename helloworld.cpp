#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <functional>

#include "./Singleton.h"
//#include "./initializerlist.h"
#include "./iterator_local.h"
#include "./demo_local.h"
#include "./Scene.h"
#include "./account.h"
using namespace std;
using namespace detail_range;

template <typename T>
void print(const T &t)
{
    for (auto &i : t)
    {
        cout << i << " ";
    }
    cout << endl;
}

void endl()
{
    cout << std::endl;
}

void print(const int *beg, const int *end)
{
    while (beg != end)
    {
        cout << *beg++ << " ";
    }
    cout << endl;
}

void print(const int *);
void print(const int[]);
void print(const int[10]);

void print(int (&a)[10])
{
    for (auto &i : a)
    {
        cout << i << " ";
    }
    endl();
}

struct C
{
    int m_x;
    double m_y;
    C(int x, double y) : m_x(x), m_y(y) {}
    void Fun() { cout << "test" << endl; }
};

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}
// auto g = bind(f, a, b, _2, c, _1);
// g(x, y) = f(a,b,y,c,x);
bool chek_size(const string &a, vector<string>::size_type z)
{
    return a.size() > z;
}
ostream &printfsss(std::ostream &os, const string &s, char c)
{
    return os << s << c;
}
void bigges(std::vector<std::string> &words, vector<string>::size_type sz, ostream& os = cout, char c = ' ')
{
    print(words);
    elimDups(words);
    print(words);
    stable_sort(words.begin(), words.end(), [](const string &a, const string &b) -> bool
                { return a.size() < b.size(); });
                
    auto wc = find_if(words.begin(), words.end(), std::bind(chek_size, std::placeholders::_1, std::ref(sz)));
    auto count = words.end() - wc;
    for_each(wc, words.end(), std::bind(printfsss, ref(os), std::placeholders::_1, c));
    std::cout << std::endl;
}

void fcn3()
{
    size_t v1 = 42;
    auto f = [v1]() mutable -> int
    { return ++v1; };
    v1 = 0;
    auto j = f();
}

int main()
{
    string str("some string");
    for (auto c : str)
    {
        cout << c << " ";
    }
    endl();
    for (auto &c : str)
    {
        c = toupper(c);
    }
    cout << str;
    endl();

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : v)
    {
        i *= i;
    }

    print(v);

    int sought = 49;
    auto vbegin = v.begin(), vend = v.end();
    auto mid = vbegin + (vend - vbegin) / 2;
    while (mid != vend && *mid != sought)
    {
        if (sought < *mid)
        {
            vend = mid;
        }
        else
        {
            vbegin = mid + 1;
        }
        mid = vbegin + (vend - vbegin) / 2;
    }
    cout << *mid << endl;

    int ja[][3] = {{3, 4, 5}, {7, 8, 9}, {10, 11, 12}};
    for (auto &row : ja)
    {
        print(row);
    }
    endl();

    for (auto &row : ja)
    {
        print(row);
    }
    endl();

    // for (auto row: ja) {
    //     for (auto col: row) {
    //         cout << col << " ";
    //     }
    //     endl();
    // }
    // endl();     error
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iabeg = begin(ia);
    auto iaed = end(ia);
    print(iabeg, iaed);

    int j[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    auto &jj = j;
    print(jj);
    Singleton<C>::Instance(1, 3.14);
    Singleton<C>::GetInstance()->Fun();

    for (auto i : range(15))
    {
        std::cout << i << " ";
    }
    endl();

    for (auto i : range('a', 'g'))
    {
        std::cout << i << " ";
    }
    endl();
    // FooVector foo_1 = {1, 2, 3, 4, 5, 6, 7, 8};
    // FooMap foo_2 = {{1, 2}, {3, 4}, {4, 5}};

    (*(func(2)))[5] = 10;
    (*(func1(2)))[5] = 10;
    (*((*func1)(2)))[5] = 100;
    for (auto i : a)
    {
        std::cout << i << " ";
    }
    endl();

    vector<string> msg = {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    string summsg = accumulate(msg.begin(), msg.end(), string(""));
    cout << summsg;
    endl();
    print(msg);
    fill(msg.begin(), msg.end(), "kunkun");
    print(msg);
    fill_n(msg.begin(), 3, "love");
    print(msg);

    vector<int> vec;
    auto it = back_inserter(vec);
    *it = 42;
    print(vec);

    fill_n(back_inserter(vec), 10, 0);
    print(vec);

    int a1[] = {0, 2, 2, 5, 4, 5, 7, 7, 8, 12};
    int a22[sizeof(a1) / sizeof(*a1)];
    auto ret = copy(begin(a1), end(a1), begin(a22));
    print(a22);

    replace(msg.begin(), msg.end(), "love", "wori");
    // print(msg);
    std::vector<std::string> msgreplace;
    replace_copy(msg.cbegin(), msg.cend(), back_inserter(msgreplace), string("kunkun"), string("kun1"));
    print(msgreplace);
    cout << endl;

    fcn3();

    std::vector<std::string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    bigges(words, 4);
    endl();
    return 0;
}
