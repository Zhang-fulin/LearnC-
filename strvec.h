#include <memory>
#include <string>
#include <utility>
class Strvec
{
public:
    Strvec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Strvec(const Strvec &s)
    {
        auto new_data = alloc_n_copy(s.begin(), s.end());
        elements = new_data.first;
        first_free = cap = new_data.second;
    }
    Strvec(Strvec &ss) : elements(ss.elements), cap(ss.cap), first_free(ss.first_free)
    {
        ss.first_free = ss.elements = ss.cap = nullptr;
    }
    Strvec &operator=(const Strvec &rhs)
    {
        auto data = alloc_n_copy(rhs.begin(), rhs.end());
        free();
        elements = data.first;
        first_free = cap = data.second;
        return *this;
    }
    Strvec &operator=(Strvec &&rhs)
    {
        if (this != &rhs)
        {
            free();
            this->elements = rhs.elements;
            this->cap = rhs.cap;
            this->first_free = rhs.first_free;
            rhs.first_free = rhs.cap = rhs.elements = nullptr;
        }
        return *this;
    }
    void push_back(const std::string &s)
    {
        chk_n_alloc();
        alloc.construct(first_free++, s);
    }
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return cap; }

private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *b, const std::string *e)
    {
        auto data = alloc.allocate(e - b);
        return {data, std::uninitialized_copy(b, e, data)};
    }
    void free()
    {
        if (elements)
        {
            for (auto p = first_free; p != elements;)
            {
                alloc.destroy(--p);
            }
            alloc.deallocate(elements, cap - elements);
        }
    }
    void reallocate()
    {
        auto newcapacity = size() ? 2 * size() : 1;
        auto newdata = alloc.allocate(newcapacity);
        auto desk = newdata;
        auto elem = elements;

        for (size_t i = 0; i != size(); i++)
        {
            alloc.construct(desk++, std::move(*elem++));
        }
        free();
        elements = newdata;
        first_free = desk;
        cap = elements + newcapacity;
    }
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};