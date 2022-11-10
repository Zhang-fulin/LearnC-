#include <initializer_list>
#include <vector>
#include <map>

class FooVector
{
    std::vector<int> content_;

public:
    FooVector(std::initializer_list<int> list)
    {
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            content_.push_back(*it);
        }
    }
};

class FooMap
{
    std::map<int, int> content_;
    using pair_t = std::map<int, int>::value_type;

public:
    FooMap(std::initializer_list<pair_t> list)
    {
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            content_.insert(*it);
        }
    }
};