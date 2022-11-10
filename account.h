#include <string>
class Account
{
public:
    void calculate() {}
    static double rate() { return interestRate; }
    static void rate(double);
    Account & test(Account temp = staticvar);

private:
    static Account staticvar;
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
};