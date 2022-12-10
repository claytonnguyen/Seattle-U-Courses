#ifndef CARBCUSTOMER_H
#define CARBCUSTOMER_H

using namespace std;

class CarbCustomer {
    private:
    string problem;
    float carbLimit;
    float carbIntake;

    public:
    CarbCustomer(unsigned int bal, unsigned int accNum) : Customer(bal, accNum);
    bool override buyOne(string name, Vendor vendor);
    bool override buy(Vendor vendor);
    void newDay();
    float carbCheck();

};

#endif