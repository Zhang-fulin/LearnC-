#include <string>
struct Sales_data
{
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);

public:
    // Sales_data() = default;
    Sales_data(std::string s = "") : bookNo(s) {}
    explicit Sales_data(const std::string &s) : Sales_data(s, 0, 0){};
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n){};
    Sales_data(std::istream &);
    std::string isbn() const { return bookNo; }
    Sales_data &combine(const Sales_data &);
    Sales_data &operator=(const Sales_data &rhs)
    {
        bookNo = rhs.bookNo;
        units_sold = rhs.units_sold;
        revenue = rhs.revenue;
        return *this;
    }
    ~Sales_data() = default;
    double avg_price() const;

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, const Sales_data &);