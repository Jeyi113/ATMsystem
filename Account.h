#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Account // Entity class
{
private:
	string user;
	string bank;
	long long CNum;
	long long ANum;
	int pin;
	int balance;
public:
	Account() {}
	Account(string name, long long card, int pw) { user = "Admin " + name; bank = ""; CNum = card; ANum = 0; pin = pw; }
	Account(string name, string b, long long card, long long account, int pw, int money) { user = name; bank = b; CNum = card; ANum = account; pin = pw; balance = money; }
	string getUser() { return user; }
	string getBank() { return bank; }
	long long getC() { return CNum; }
	long long getA() { return ANum; }
	int getPin() { return pin; }
	int getBal() { return balance; }
	void deposit(int money) { balance += money; }
	void withdraw(int money) { balance -= money; }
};

