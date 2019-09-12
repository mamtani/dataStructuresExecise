/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: mohitmamtani
 *
 * Created on November 30, 2018, 5:09 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <sstream> 
#include <list>
#include <cmath>
#include <iomanip>
using namespace std;

/*
 * 
 */




class Call {
private:
    int phoneNumber;
    int duration;
public:

    Call() {
    };

    Call(int phoneNumber, int duration) {
        this->phoneNumber = phoneNumber;
        this->duration = duration;
    }

    int GetDuration() {
        return duration;
    }

    void SetDuration(int duration) {
        this->duration = duration;
    }

    int GetPhoneNumber() {
        return phoneNumber;
    }

    void SetPhoneNumber(int phoneNumber) {
        this->phoneNumber = phoneNumber;
    }

};

class Customer {
private:
    string customersName;
    double balance;
    vector<Call> vectorOfCalls;
public:

    double getBalance() const {
        return balance;
    }

    void setBalance(double balance) {
        this->balance = balance;
    }

    string getCustomersName() const {
        return customersName;
    }

    void setCustomersName(string customersName) {
        this->customersName = customersName;
    }

    void addCall(int phoneNumber, int duration) {
        Call call = Call(phoneNumber, duration);
        vectorOfCalls.push_back(call);
    }

    vector<Call> getVectorOfCalls() {
        return vectorOfCalls;
    }

    void setVectorOfCalls(vector<Call> vectorOfCalls) {
        this->vectorOfCalls = vectorOfCalls;
    }

    virtual void computeBalance() {
    }
};

class regularCustomer : public Customer {
private:
    int monthlyfee = 5;
    int percall = 1;
    int num_calls;


public:

    regularCustomer() {
    };

    void computeBalance() {
        setBalance(monthlyfee + percall * getVectorOfCalls().size());
    }


};

class premiumCustomer : public Customer {
private:
    int monthlyfee = 30;
    float permin = 0.05;
    int num_mins;
    int seconds;
public:

    premiumCustomer() {
    };

    void computeBalance() {
        for (int i = 0; i < getVectorOfCalls().size(); i = i + 1) {
            Call call = getVectorOfCalls()[i];
            int seconds = seconds + call.GetDuration();
        }
        num_mins = (int) seconds / 60;
        int round = seconds % 60;
        if (round != 0) {
            num_mins++;
        };
        setBalance(monthlyfee + permin * num_mins);
    }

};

class Simulation {
public:
    list<Customer*> regularCustomers;
    list<Customer*> premiumCustomers;

public:

    Customer* generateCustomers(Customer* c) {
        c->setCustomersName(generateName());
        for (int i = 0; i < (rand() % 290) + 10; i++) {
            c->addCall(generateNumber(), generateDuration());
        }

        c->computeBalance();

        return c;
    }

    string generateName() {
        int lenth = (rand() % 3) + 4;
        string str = "abcdefghijklmnopqrstuvwxyz";
        string fName;
        string lName;
        int pos, pos1;
        while (fName.size() != lenth) {
            pos = ((rand() % (str.size() - 1)));
            pos1 = ((rand() % (str.size() - 1)));
            fName += str.substr(pos, 1);
            lName += str.substr(pos1, 1);
            fName[0] = toupper(fName[0]);
            lName[0] = toupper(lName[0]);
        }
        return fName + " " + lName;
    }

    int generateNumberOfCalls() {
        int number = rand() % (300 - 10) + 10;
        return number;
    }

    int generateNumber() {
        int len = 10;
        string str = "0123456789";
        string number;
        int pos;
        int x = 0;
        while (number.size() != len) {
            pos = ((rand() % (str.size() - 1)));
            number += str.substr(pos, 1);
            stringstream geek(number);
            geek >> x;
        }
        return x;
    }

    int generateDuration() {
        int number = rand() % (7200 - 20) + 20;
        return number;
    }

    int printResult() {
        srand(time(NULL));
        for (int i = 0; i < (rand() % (300)) + 100; i++) {
            regularCustomer *r = new regularCustomer();
            regularCustomers.push_back(generateCustomers(r));
        }

        for (int i = 0; i < (rand() % (300)) + 100; i++) {
            premiumCustomer *p = new premiumCustomer();
            premiumCustomers.push_back(generateCustomers(p));
        }

        double regularTotalCustomers = regularCustomers.size();
        double regularAvgCalls = 0;
        double regularAvgDuration = 0;
        double regularAvgBalance = 0;


        double maxBalance = 0;
        double minBalance = 999999999;
        string maxName;
        string minName;

        Call call;
        list<Customer*>::iterator myIt = regularCustomers.begin();

        while (myIt != regularCustomers.end()) {
            Customer *cust = *myIt;
            double totalCalls = cust->getVectorOfCalls().size();
            double duration = 0;
            for (int i = 0; i < totalCalls; i++) {
                Call call = cust->getVectorOfCalls()[i];
                duration += call.GetDuration();
            }

            regularAvgBalance += cust->getBalance();

            if (cust->getBalance() > maxBalance) {
                maxBalance = cust->getBalance();
                maxName = cust->getCustomersName();
            }
            if (cust->getBalance() < minBalance) {
                minBalance = cust->getBalance();
                minName = cust->getCustomersName();
            }

            regularAvgCalls += totalCalls;
            regularAvgDuration += duration / totalCalls;
            myIt++;
        }

        regularAvgCalls = round(regularAvgCalls / regularTotalCustomers);

        regularAvgDuration = regularAvgDuration / regularTotalCustomers;
        regularAvgDuration = round(regularAvgDuration / 60);

        regularAvgBalance = regularAvgBalance / regularTotalCustomers;

        cout << "Simulation run: " << endl;
        cout << "---------------" << endl;
        cout << "Regular Customers:" << endl << endl;
        cout << setprecision(0) << fixed << "\tNumber of customers in the group: " << regularTotalCustomers << endl;
        cout << setprecision(0) << fixed << "\tAverage number of calls/per customer: " << regularAvgCalls << endl;
        cout << setprecision(0) << fixed << "\tAverage duration of the call/per customer: " << regularAvgDuration << " mins" << endl;
        cout << setprecision(2) << fixed << "\tAverage balance/per customer: $" << regularAvgBalance << endl;
        cout << setprecision(2) << fixed << "\tCustomer with largest balance: " << maxName << "($" << maxBalance << ")" << endl;
        cout << setprecision(2) << fixed << "\tCustomer with smallest balance: " << minName << "($" << minBalance << ")" << endl;
        cout << endl;

        double premiumTotalCustomers = premiumCustomers.size();
        double premiumAvgCalls = 0;
        double premiumAvgDuration = 0;
        double premiumAvgBalance = 0;

        double pmaxBalance = 0;

        double pminBalance = 999999999;

        string pmaxName;
        string pminName;


        list<Customer*>::iterator myIt2 = premiumCustomers.begin();

        while (myIt2 != premiumCustomers.end()) {
            Customer *cust = *myIt2;
            double totalCalls = cust->getVectorOfCalls().size();
            double duration = 0;
            for (int i = 0; i < totalCalls; i++) {
                Call call = cust->getVectorOfCalls()[i];
                duration += call.GetDuration();
            }

            premiumAvgBalance += cust->getBalance();

            if (cust->getBalance() > pmaxBalance) {
                pmaxBalance = cust->getBalance();
                pmaxName = cust->getCustomersName();
            }
            if (cust->getBalance() < pminBalance) {
                pminBalance = cust->getBalance();
                pminName = cust->getCustomersName();

            }

            premiumAvgCalls += totalCalls;
            premiumAvgDuration += duration / totalCalls;
            myIt2++;
        }

        premiumAvgCalls = round(premiumAvgCalls / premiumTotalCustomers);

        premiumAvgDuration = premiumAvgDuration / premiumTotalCustomers;
        premiumAvgDuration = round(premiumAvgDuration / 60);

        premiumAvgBalance = premiumAvgBalance / premiumTotalCustomers;

        cout << "Simulation run: " << endl;
        cout << "---------------" << endl;
        cout << "Premium Customers:" << endl << endl;
        cout << setprecision(0) << fixed << "\tNumber of customers in the group: " << premiumTotalCustomers << endl;
        cout << setprecision(0) << fixed << "\tAverage number of calls/per customer: " << premiumAvgCalls << endl;
        cout << setprecision(0) << fixed << "\tAverage duration of the call/per customer: " << premiumAvgDuration << " mins" << endl;
        cout << setprecision(2) << fixed << "\tAverage balance/per customer: $" << premiumAvgBalance << endl;
        cout << setprecision(2) << fixed << "\tCustomer with largest balance: " << pmaxName << "($" << pmaxBalance << ")" << endl;
        cout << setprecision(2) << fixed << "\tCustomer with smallest balance: " << pminName << "($" << pminBalance << ")" << endl;
        cout << endl;

        if (premiumAvgBalance > regularAvgBalance)
            cout << setprecision(2) << fixed << "Regular customers on average save $" << premiumAvgBalance - regularAvgBalance << " compared to Premium customers" << endl;
        else
            cout << setprecision(2) << fixed << "Premium customers on average save $" << regularAvgBalance - premiumAvgBalance << " compared to Regular customers" << endl;
    }


};

int main() {
    Simulation *sim = new Simulation();
    sim->printResult();
    delete sim;
    return 0;
}