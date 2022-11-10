#include "./account.h"
void Account::rate(double newRate){
    interestRate = newRate;
}
double Account::interestRate = initRate();