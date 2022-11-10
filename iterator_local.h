#include <stdexcept>
#include <iostream>
namespace detail_range
{
    template <typename T>
    class itertor
    {
    public:
        using value_type = T;
        using size_type = size_t;

    private:
        size_type cursor_;
        const value_type step_;
        value_type value_;

    public:
        itertor(size_type cur_start, value_type begin_val, value_type step_val) : cursor_(cur_start), value_(begin_val), step_(step_val)
        {
            std::cout << "gou zao" <<std::endl;
            value_ += (step_ * cursor_);
        }
        value_type operator*() const { return value_; }
        bool operator!=(const itertor &rhs) const
        {
            std::cout << "*" ;
            return cursor_ != rhs.cursor_;
        }

        itertor &operator++(void)
        {
            value_ += step_;
            ++cursor_;
            std::cout << "++" ;
            return *this;
        }
    };
}

namespace detail_range
{
    template <typename T>
    class impl
    {
    public:
        using value_type = T;
        using reference = const value_type &;
        using const_reference = const value_type &;
        using itertor = const detail_range::itertor<value_type>;
        using const_itertor = const detail_range::itertor<value_type>;
        using size_type = typename itertor::size_type; // typename 后面跟的是类型

    private:
        const value_type begin_;
        const value_type end_;
        const value_type step_;
        const size_type max_count_;
        size_type get_adjuested_cout() const
        {
            if (step_ > 0 && begin_ > end_)
                throw std::logic_error("end value must be greater than begin value");
            else if (step_ < 0 && begin_ < end_)
            {
                throw std::logic_error("end value must be less than begin value");
            }
            size_type x = static_cast<size_type>((end_ - begin_) / step_);
            if (begin_ + (step_ * x) != end_)
            {
                ++x;
            }
            return x;
        }

    public:
        impl(value_type begin_val, value_type end_val, value_type step_val) : begin_(begin_val), end_(end_val), step_(step_val), max_count_(get_adjuested_cout()) {}
        size_type size() const
        {
            return max_count_;
        }
        const_itertor begin() const
        {
            return {0, begin_, step_};
        }
        const_itertor end() const
        {
            return {max_count_, begin_, step_};
        }
    };

    template <typename T>
    detail_range::impl<T> range(T end)
    {
        return {{}, end, 1};
    }

    template <typename T>
    detail_range::impl<T> range(T begin, T end)
    {
        return {begin, end, 1};
    }

    template <typename T, typename U>
    auto range(T begin, T end, U step) -> detail_range::impl<decltype(begin + step)>     // 有返回值的函数写法
    {
        using r_t = detail_range::impl<decltype(begin + step)>;
        return r_t(begin, end, step);
    }
}