#ifndef DBETCUSTOMER_H
#define DBETCUSTOMER_H

using namespace std;

class DBetCustomer {
    private:
    string problem;
    float dailySugarLimit;
    float mealSugarLimit;
    float itemSugarLimit;
    float sugarIntake;

    public:
    DBetCustomer(unsigned int bal, unsigned int accNum) : Customer(bal, accNum);
    bool override buyOne(string name, Vendor vendor);
    bool override buy(Vendor vendor);
    void newDay();

};

#endif