#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <stdexcept>
using namespace std;
class StrBlob
{
    friend class StrBlobPtr;

public:
    typedef vector<string>::size_type size_type;
    StrBlob() : data(make_shared<vector<string>>()){};
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)){};
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back()
    {
        check(0, "pop back on empty strblob");
        data->pop_back();
    };
    std::string &front()
    {
        check(0, "front on empty strblob");
        return data->front();
    };
    std::string &back()
    {
        check(0, "end on empty strblob");
        return data->back();
    };

private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const
    {
        if (i >= data->size())
        {
            throw out_of_range(msg);
        }
    };
};

class StrBlobPtr
{
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    string &deref() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    };
    StrBlobPtr &incr()
    {
        check(curr, "increment past end of strblobptr");
        ++curr;
        return *this;
    };

private:
    shared_ptr<vector<string>> check(std::size_t i, const string &msg) const
    {
        auto ret = wptr.lock();
        if (!ret)
            throw runtime_error("unbound strblobptr");
        if (i >= ret->size())
            throw out_of_range(msg);
        return ret;
    };
    std::size_t curr;
    weak_ptr<vector<string>> wptr;
};
