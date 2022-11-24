#include <string>

class HasPtr
{
    friend class HasPtrRef;
    friend void swap(HasPtr &lhs, HasPtr &right);

public:
    HasPtr(const std::string &s, int n) : ps(new std::string(s)), i(n) {}
    HasPtr(const HasPtr &p) : ps(new std::string(*p.ps)), i(p.i) {}
    HasPtr(HasPtr &&p):ps(p.ps), i(p.i)
    {
        p.ps = nullptr;
    }
    // HasPtr &operator=(const HasPtr &rhs)
    // {
    //     auto newp = new std::string(*rhs.ps);
    //     delete ps;
    //     ps = newp;
    //     i = rhs.i;
    //     return *this;
    // }
    HasPtr &operator=(HasPtr rhs)
    {
        swap(*this, rhs);
        return *this;
    }

private:
    std::string *ps;
    int i;
};
void swap(HasPtr &lhs, HasPtr &rhs)
{
    std::swap(lhs.i, rhs.i);
    std::swap(lhs.ps, rhs.ps);
}

class HasPtrRef
{
    friend void swap(HasPtrRef &lhs, HasPtrRef &right);

public:
    HasPtrRef(const std::string &s = std::string(), int n = 5) : ps(new std::string(s)), i(n), use(new std::size_t(1)) {}
    HasPtrRef(const HasPtrRef &p) : ps(p.ps), i(p.i), use(p.use)
    {
        ++*use;
    }
    ~HasPtrRef()
    {
        if (*use == 1)
        {
            delete use;
            delete ps;
        }
    }
    // HasPtrRef &operator=(const HasPtrRef &rhs)
    // {
    //     ++*rhs.use;
    //     if (*use == 1)
    //     {
    //         delete use;
    //         delete ps;
    //     }
    //     ps = rhs.ps;
    //     i = rhs.i;
    //     use = rhs.use;
    //     return *this;
    // }
    HasPtrRef &operator=(HasPtrRef lhs)
    {
        swap(*this, lhs);
        return *this;
    }

private:
    std::string *ps;
    int i;
    std::size_t *use;
};

void swap(HasPtrRef &lhs, HasPtrRef &rhs)
{
    std::swap(lhs.i, rhs.i);
    std::swap(lhs.ps, rhs.ps);
    std::swap(lhs.use, rhs.use);
}