#include <unordered_map>
#include <string>

struct Key
{
    std::string first;
    std::string second;
};

struct KeyHash
{
    std::size_t operator()(const Key &k) const
    {
        return std::hash<std::string>()(k.first) ^ std::hash<std::string>()(k.second) << 1;
    }
};

struct KeyEqual
{
    bool operator()(const Key &lhs, const Key &rhs) const
    {
        return lhs.first == rhs.second && lhs.second == rhs.second;
    }
};

std::unordered_map<Key, std::string, KeyHash, KeyEqual> mmmmmm6 = {{{"john", "doe"}, "example"}, {{"mary", "sue"}, "another"}};
