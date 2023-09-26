#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Account.h"

using namespace std;

class Bank
{
private:
    Account* a_ptrb;
    Account* u_ptrb;
    vector<Account*> av;
    int myindex; // 내 Account* 갖는 vector의 index
    int urindex; // 타인 Account* 갖는 vector의 index
    int BankMoney = 15000000;
public:
    Bank() {}
    void moneyForATM(int cash1, int cash2) { BankMoney -= (((20 - cash1) * 10000) + ((20 - cash2) * 50000)); }
    void save(Account* a) { av.push_back(a); }
    void Mychange(Account* a) { av.erase(av.begin() + myindex); av.insert(av.begin() + myindex, a); }
    void Urchange(Account* a) { av.erase(av.begin() + urindex); av.insert(av.begin() + urindex, a); }
    vector<Account*> getList() { return av; }
    bool check(long long cnum)
    {
        //1. Card 있는건지 인식 -> 2. Admin or User -> 3. Pincheck
        //User authorization
        vector<int> vi;
        for (int i = 0; i < av.size(); i++)
        {
            if (cnum == av[i]->getC())
            {
                vi.push_back(1);
            }
            else { vi.push_back(0); }
        }
        vector<int>::iterator it = find(vi.begin(), vi.end(), 1);
        int index;
        index = distance(vi.begin(), it);
        if (index == vi.size()) { return false; }
        else { myindex = index; a_ptrb = av[index]; return true; }
    }
    bool check2(long long anum)
    {
        vector<int> vi;
        for (int i = 0; i < av.size(); i++)
        {
            if (anum == av[i]->getA())
            {
                vi.push_back(1);
            }
            else { vi.push_back(0); }
        }
        vector<int>::iterator it = find(vi.begin(), vi.end(), 1);
        int index;
        index = distance(vi.begin(), it);

        if (index == vi.size()) { return false; }
        else { urindex = index; u_ptrb = av[index]; return true; }
    }
    bool pinCheck(int pw)
    {
        if (pw == av[myindex]->getPin())
        {
            return true;
        }
        else { return false; }
    }
    int getIndex() { return myindex; }
    int getUrIndex() { return urindex; }
    Account* getAccountInfo() { a_ptrb = av[myindex]; return a_ptrb; }
    Account* getUrAccountInfo() { u_ptrb = av[urindex]; return u_ptrb; }

    string getUserName() { return a_ptrb->getUser(); }
    int getAccountNumber() { return a_ptrb->getC(); }
    int getBalance() { return a_ptrb->getBal(); }

};